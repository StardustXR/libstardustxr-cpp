#include "pointerinput.hpp"
#include "../../../../common/flatbuffers/Input.hpp"

namespace StardustXRFusion {

const Vec3 convertVec3(const StardustXR::vec3 &vec) {
	return Vec3 {vec.x(), vec.y(), vec.z()};
}

PointerInput::PointerInput(const StardustXR::InputData *pointer) :
	distance(pointer->distance()),
	origin(convertVec3(*pointer->input_as_Pointer()->origin())),
	direction(convertVec3(*pointer->input_as_Pointer()->direction())),
	tilt(pointer->input_as_Pointer()->tilt()),
	deepestPoint(convertVec3(*pointer->input_as_Pointer()->deepest_point())){}

}
