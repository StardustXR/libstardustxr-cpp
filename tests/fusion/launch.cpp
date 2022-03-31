#include "fusion/fusion.hpp"
#include "fusion/types/spatial/spatial.hpp"

#include <condition_variable>
#include <mutex>
#include <unistd.h>

using namespace StardustXRFusion;

int main() {
	if(!StardustXRFusion::Setup())
		return 0;

	std::mutex m;
	bool ready = false;
	std::condition_variable cv;

	Spatial spawnPos(Root());
	spawnPos.setOrigin(SKMath::vec3_up);
	spawnPos.createLaunchAnchor([&](uint32_t anchorCode) {
		m.lock();
		setenv("STARDUST_LAUNCH_ANCHOR", std::to_string(anchorCode).c_str(), true);
		printf("Launch anchor code is %ul\n", anchorCode);
//		exit(0);
		ready = true;
		m.unlock();
		cv.notify_one();
	});

	std::unique_lock<std::mutex> lock(m);
	while(!ready) cv.wait(lock);

	std::string spatialPath = ConvertExeRelativePath("spatial");
//	char ** test = environ;
	int pid = fork();
	if(pid == 0)
		execl(spatialPath.c_str(), "", nullptr);

	pause();
	return 0;
}
