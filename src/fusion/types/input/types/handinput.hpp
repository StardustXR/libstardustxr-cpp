#pragma once

#include "../../../sk_math.hpp"
#include <array>

namespace StardustXR {
	class InputData;
}

namespace StardustXRFusion {

struct joint_t {
	float radius;
	SKMath::pose_t pose;

	const joint_t& operator=(const joint_t& other)const {
         return other;
    }
};

struct Finger {
	const std::array<const joint_t, 5> bones;
	const joint_t& operator[](int index) {
		return bones[index];
	}

	const joint_t &tip          (){return bones[4];}
	const joint_t &distal       (){return bones[3];}
	const joint_t &intermediate (){return bones[2];}
	const joint_t &proximal     (){return bones[1];}
	const joint_t &metacarpal   (){return bones[0];}
};

class HandInput {
public:
	explicit HandInput(const StardustXR::InputData *hand);

	const float distance;

	const std::array<const Finger, 5> fingers;
	const Finger operator[](int index) {
		return fingers[index];
	}

	const Finger &thumb  (){return fingers[0];}
	const Finger &index  (){return fingers[1];}
	const Finger &middle (){return fingers[2];}
	const Finger &ring   (){return fingers[3];}
	const Finger &pinky  (){return fingers[4];}
	
	const joint_t palm;
	const joint_t wrist;
	const joint_t elbow;
};

} // namespace StardustXRFusion
