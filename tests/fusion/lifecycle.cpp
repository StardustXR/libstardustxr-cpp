#include <chrono>
#include <iostream>
#include <thread>

#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	LifeCycle()->onLogicStep([&](double delta, double timeToRender) {
		printf("Frame delta is %f ms\n", delta);
	});
	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
