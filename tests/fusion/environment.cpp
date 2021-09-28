#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	// SetSkytex(std::string(getenv("HOME"))+"/.config/stardust/skytex_earth.hdr");
	SetSkytex(std::string(getenv("HOME"))+"/.config/stardust/skytex_space.hdr");
	SetSkylight(std::string(getenv("HOME"))+"/.config/stardust/skytex_earth.hdr");
	// SetSkylight(std::string(getenv("HOME"))+"/.config/stardust/skytex_space.hdr");
	return 0;
}
