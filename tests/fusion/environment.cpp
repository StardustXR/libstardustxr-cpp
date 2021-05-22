#include <chrono>
#include <iostream>
#include <thread>

#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Environment()->visible(true);
	Environment()->setSkytex("../../../res/zhengyang_gate_4k.hdr");
	Environment()->setLighting("../../../res/wide_street_01_1k.hdr");
	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
