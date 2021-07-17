#include "model.hpp"

#include "../flex.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {

Model::Model(std::string relativePath, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale) : Spatial() {
	nodePath = "/model";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/model",
		"createFromFile",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(ConvertExeRelativePath(relativePath))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(scale)
		)
	);
}

Model::~Model() {}

} // namespace StardustXRFusion
