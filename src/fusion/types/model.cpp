#include <libgen.h>
#include <unistd.h>
#include <linux/limits.h>

#include "../flex.hpp"
#include "../fusion_internal.hpp"

#include "model.hpp"

namespace StardustXRFusion {

Model::Model(std::string relativePath, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale) {
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	const char *path;
	if (count != -1) {
		path = dirname(result);
	}

	nodePath = "/model";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/model",
		"createFromFile",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(std::string(path) + "/" + relativePath)
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(scale)
		)
	);
}

Model::~Model() {}

} // namespace StardustXRFusion
