#include "handinput.hpp"
#include "../../../../common/flatbuffers/Input.hpp"

namespace StardustXRFusion {

const joint_t convertJoint(const StardustXR::joint *joint) {
	return joint_t{
		joint->radius(),
		SKMath::pose_t{
			SKMath::vec3{
				joint->position().x(),
				joint->position().y(),
				joint->position().z()
			},
			SKMath::quat{
				joint->rotation().x(),
				joint->rotation().y(),
				joint->rotation().z(),
				joint->rotation().w()
			}
		}
	};
}

const Finger convertFinger(const StardustXR::joint *startJoint) {
	size_t jointSize = sizeof(StardustXR::joint);
	std::array<const joint_t, 5> bones = {};
	for(uint i=0; i<5; ++i) {
		bones[i] = convertJoint(startJoint+(jointSize*i));
	}
	return Finger{
		.bones = bones
	};
}

const std::array<const Finger, 5> convertFingers(const StardustXR::joint *startJoint) {
	size_t jointSize = sizeof(StardustXR::joint);
	return {
		convertFinger(startJoint+(jointSize)),
		convertFinger(startJoint+(jointSize*5)),
		convertFinger(startJoint+(jointSize*10)),
		convertFinger(startJoint+(jointSize*15)),
		convertFinger(startJoint+(jointSize*20))
	};
}

HandInput::HandInput(const StardustXR::InputData *hand) :
	distance(hand->distance()),
	fingers(convertFingers((*hand->input_as_Hand()->finger_joints())[0])),
	palm(convertJoint(hand->input_as_Hand()->palm())),
	wrist(convertJoint(hand->input_as_Hand()->wrist())),
	elbow(convertJoint(hand->input_as_Hand()->elbow())) {
}

}