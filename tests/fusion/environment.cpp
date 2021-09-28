#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	// Environment()->setSkytex(std::string(getenv("HOME"))+"/.config/stardust/skytex_earth.hdr");
	Environment()->setSkytex(std::string(getenv("HOME"))+"/.config/stardust/skytex_space.hdr");
	Environment()->setSkylight(std::string(getenv("HOME"))+"/.config/stardust/skytex_earth.hdr");
	// Environment()->setSkylight(std::string(getenv("HOME"))+"/.config/stardust/skytex_space.hdr");
	return 0;
}
