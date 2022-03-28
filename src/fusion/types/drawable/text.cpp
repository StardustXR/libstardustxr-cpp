#include "text.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

using namespace SKMath;

namespace StardustXRFusion {

Text::Text(Spatial *parent, std::string text, float characterHeight, SKMath::vec3 origin, SKMath::quat orientation, std::string fontPath, Align textAlign, SKMath::vec2 bounds, Fit fit, Align boundsAlign, SKMath::color color) : Spatial(parent, origin, orientation, vec3_one) {
//	if(!FileExists(relativePath))
//		return;
	nodePath = "/drawable/text";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/drawable",
		"createText",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(text)
			FLEX_STRING(fontPath != "" ? ConvertExeRelativePath(fontPath) : std::string(""))
			FLEX_FLOAT(characterHeight)
			FLEX_UINT(textAlign)
			FLEX_VEC2(bounds)
			FLEX_UINT(fit)
			FLEX_UINT(boundsAlign)
			FLEX_COLOR(color)
		)
	);
}

} // namespace StardustXRFusion
