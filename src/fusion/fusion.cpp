#include "fusion.hpp"
#include "fusion_internal.hpp"
#include "../client/connector.hpp"
#include "flex.hpp"
#include "fusion_internal.hpp"

#include "types/spatial/spatial.hpp"

#include <poll.h>
#include <iostream>
#include <linux/limits.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include "random.hpp"

namespace StardustXRFusion {

std::vector<uint32_t> usedIDs;

StardustXRFusion::FusionScenegraph *scenegraph = nullptr;
StardustXRFusion::Messenger *messenger = nullptr;

Spatial root;

LogicStepMethod logicMethod;

std::vector<uint8_t> FlexDummy(flexbuffers::Reference data, bool) {
	return std::vector<uint8_t>();
}

std::string GenerateID() {
	uint32_t id = 0;
	while(id == 0 || find(usedIDs.begin(), usedIDs.end(), id) != usedIDs.end()) {
		id = Random::generate<uint32_t>();
	}
	usedIDs.push_back(id);
	std::string strID = std::to_string(id);
	strID.reserve(16);
	return strID;
}

bool Setup() {
	printf("Client starting...\n");
	int fd = StardustXR::ConnectClient();
	if (!fd) {
		perror("Client failed to connect to server\n");
		return false;
	}

	scenegraph = new FusionScenegraph();
	messenger = new Messenger(fd, scenegraph);

	const char* launchAnchor = getenv("STARDUST_LAUNCH_ANCHOR");
	if(launchAnchor) {
		messenger->sendSignal(
			"/",
			"applyLaunchAnchor",
			FLEX_ARG(FLEX_UINT(std::stoul(launchAnchor)))
		);
	}

	messenger->sendSignal(
		"/",
		"subscribeLogicStep",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("logicStep"))
		)
	);
	scenegraph->addMethod("logicStep", &FlexDummy);

	return true;
}

void RunEventLoop(int timeout) {
	pollfd poll_fd = {
		.fd = messenger->fd,
		.events = POLLIN,
	};
	while(1) {
		int fdStatus = poll(&poll_fd, 1, timeout);
		if(fdStatus < 0)
			break;
		if(fdStatus == 0)
			continue;

		if(!messenger->dispatch())
			break;
	}
	Shutdown();
}

//void Stop() {
//}

void Shutdown() {
	messenger->sendSignal(
		"/",
		"disconnect",
		FLEX_ARG(FLEX_NULL)
	);
	delete scenegraph;
	delete messenger;
	scenegraph = nullptr;
	messenger  = nullptr;
}

Spatial *Root() {
	return &root;
}

void SetSkytex(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkytex",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

void SetSkylight(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkylight",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

std::vector<uint8_t> LogicStep(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vec = data.AsVector();
	double delta = vec[0].AsDouble();
	double timeToRender = vec[1].AsDouble();
	logicMethod(delta, timeToRender);

	return std::vector<uint8_t>();
}

void OnLogicStep(LogicStepMethod method) {
	scenegraph->addMethod("logicStep", &LogicStep);
	logicMethod = method;
}

bool FileExists(std::string path) {
	std::string convertedPath = ConvertExeRelativePath(path);
	FILE *file = fopen(convertedPath.c_str(), "ro");
	bool exists = file;
	if(exists)
		fclose(file);
	else
		printf("File \"%s\" does not exist\n", convertedPath.c_str());
	fflush(stdout);
	return exists;
}

std::string ConvertExeRelativePath(std::string path) {
	if(*path.begin() == '/')
		return path;
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	std::string exePath;
	if (count != -1) {
		exePath = dirname(result);
	}
	return std::string(exePath) + "/" + path;
}

}
