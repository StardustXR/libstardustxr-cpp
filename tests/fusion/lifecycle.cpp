#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	OnLogicStep([&](double delta, double timeToRender) {
		printf("Frame delta is %f ms\n", delta);
	});
	StardustXRFusion::RunEventLoop();
}
