#include "pointerinput.hpp"
#include "../flatbuffers/Input_generated.h"

namespace StardustXRFusion {

const SKMath::vec3 convertVec3(const StardustXR::vec3 &vec) {
	return SKMath::vec3 {vec.x(), vec.y(), vec.z()};
}

PointerInput::PointerInput(const StardustXR::InputData *pointer) :
	distance(pointer->distance()),
	origin(convertVec3(*pointer->input_as_Pointer()->origin())),
	direction(convertVec3(*pointer->input_as_Pointer()->direction())),
	tilt(pointer->input_as_Pointer()->tilt()) {}

}