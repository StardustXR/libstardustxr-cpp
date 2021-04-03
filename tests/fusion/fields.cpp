#include <chrono>
#include <iostream>
#include <thread>

#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	SphereField sphereField(vec3_zero, 0.5f);
	sphereField.distance(&sphereField, vec3_right*1.0f, [&](float distance) {
		std::cout << "Distance: " << distance << std::endl;
	});
	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
