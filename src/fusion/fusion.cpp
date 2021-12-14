#include "fusion.hpp"
#include "fusion_internal.hpp"
#include "../client/connector.hpp"
#include "flex.hpp"
#include "fusion_internal.hpp"

#include "types/spatial.hpp"

#include <csignal>
#include <iostream>
#include <linux/limits.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>
#include "random.hpp"

namespace StardustXRFusion {

std::vector<uint32_t> usedIDs;

StardustXRFusion::FusionScenegraph *scenegraph = nullptr;
StardustXR::Messenger *messenger = nullptr;
Spatial root(nullptr, "", "");

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
	int fd;
	srand(time(nullptr));
	if (!(fd = StardustXR::ConnectClient())) {
		perror("Client failed to connect to server");
		return false;
	}

	scenegraph = new FusionScenegraph();
	messenger = new StardustXR::Messenger(fd, scenegraph);
	messenger->startHandler();
	signal(SIGINT, Shutdown);

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

void StallMainThread() {
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(3600));
	}
}

void Shutdown(int signal) {
	messenger->sendSignal(
		"/",
		"disconnect",
		FLEX_ARG(FLEX_NULL)
	);
	std::exit(0);
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
