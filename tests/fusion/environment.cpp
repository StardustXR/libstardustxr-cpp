#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Environment()->visible(true);
	Environment()->setSkytex("../../../res/zhengyang_gate_4k.hdr");
	// Environment()->setSkytex("../../../res/wide_street_01_1k.hdr");
	Environment()->setLighting("../../../res/zhengyang_gate_4k.hdr");
	// Environment()->setLighting("../../../res/wide_street_01_1k.hdr");
	return 0;
}
