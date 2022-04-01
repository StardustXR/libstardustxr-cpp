#include "fusion/fusion.hpp"
#include "fusion/types/spatial/spatial.hpp"

#include <unistd.h>

using namespace StardustXRFusion;

int main() {
	if(!StardustXRFusion::Setup())
		return 0;

	Spatial spawnPos(Root(), SKMath::vec3_up * 0.5f);
	spawnPos.createLaunchAnchor([&](uint32_t anchorCode) {
		setenv("STARDUST_LAUNCH_ANCHOR", std::to_string(anchorCode).c_str(), true);
		std::string spatialPath = ConvertExeRelativePath("spatial");
		if(fork() == 0)
			execl(spatialPath.c_str(), "", nullptr);
	});
	pause();
}
