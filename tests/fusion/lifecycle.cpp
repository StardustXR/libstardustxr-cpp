#include "fusion/fusion.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	LifeCycle()->onLogicStep([&](double delta, double timeToRender) {
		printf("Frame delta is %f ms\n", delta);
	});
	StardustXRFusion::StallMainThread();
}
