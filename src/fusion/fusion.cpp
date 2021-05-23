#include "fusion.hpp"
#include "fusion_internal.hpp"
#include "../client/connector.hpp"
#include <linux/limits.h>
#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

namespace StardustXRFusion {

StardustXRFusion::FusionScenegraph *scenegraph = nullptr;
StardustXR::ClientMessenger *messenger = nullptr;

EnvironmentInterface *environment = nullptr;
LifeCycleInterface *lifeCycle = nullptr;

std::string GenerateID() {
	char id[32];

	int urandom = open("/proc/sys/kernel/random/uuid", O_RDONLY);
	read(urandom, id, sizeof id);
	close(urandom);

	return std::string(id);
}

bool Setup() {
	printf("Client starting...\n");
	int readFD, writeFD;
	if (!StardustXR::ConnectClient("/tmp/stardust.sock", readFD, writeFD)) {
		perror("Client failed to connect to server");
		return false;
	}

	scenegraph = new FusionScenegraph();
	messenger = new StardustXR::ClientMessenger(readFD, writeFD, scenegraph);
	messenger->startHandler();

	return true;
}

LifeCycleInterface *LifeCycle() {
	if(!lifeCycle)
		lifeCycle = new LifeCycleInterface();
	return lifeCycle;
}

EnvironmentInterface *Environment() {
	if(!environment)
		environment = new EnvironmentInterface();
	return environment;
}

std::string ConvertExeRelativePath(std::string exeRelativePath) {
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	const char *exePath;
	if (count != -1) {
		exePath = dirname(result);
	}
	return std::string(exePath) + "/" + exeRelativePath;
}

}
