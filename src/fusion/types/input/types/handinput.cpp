#include "handinput.hpp"
#include "../../../../common/flatbuffers/Input.hpp"

namespace StardustXRFusion {

const joint_t convertJoint(const StardustXR::joint *joint) {
	return joint_t{
		joint->radius(),
		Pose{
			Vec3{
				joint->position().x(),
				joint->position().y(),
				joint->position().z()
			},
			Quat{
				joint->rotation().x(),
				joint->rotation().y(),
				joint->rotation().z(),
				joint->rotation().w()
			}
		}
	};
}

const Finger convertFinger(const flatbuffers::Vector<const StardustXR::joint *> &fingerJoints, int startIndex) {
	return Finger{
		.bones = {
			convertJoint(fingerJoints[startIndex]),
			convertJoint(fingerJoints[startIndex+1]),
			convertJoint(fingerJoints[startIndex+2]),
			convertJoint(fingerJoints[startIndex+3]),
			convertJoint(fingerJoints[startIndex+4])
		}
	};
}

const std::array<const Finger, 5> convertFingers(const flatbuffers::Vector<const StardustXR::joint *> &joints) {
	return {
		convertFinger(joints, 0),
		convertFinger(joints, 5),
		convertFinger(joints, 10),
		convertFinger(joints, 15),
		convertFinger(joints, 20)
	};
}

HandInput::HandInput(const StardustXR::InputData *hand) :
	distance(hand->distance()),
	fingers(convertFingers(*hand->input_as_Hand()->finger_joints())),
	palm(convertJoint(hand->input_as_Hand()->palm())),
	wrist(convertJoint(hand->input_as_Hand()->wrist())),
	elbow(hand->input_as_Hand()->elbow() ? convertJoint(hand->input_as_Hand()->elbow()) : joint_t{0, Pose::Identity}) {
}

}
