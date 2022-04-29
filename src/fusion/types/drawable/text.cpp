#include "text.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"



namespace StardustXRFusion {

Text::Text(Spatial *parent, std::string text, float characterHeight, Vec3 origin, Quat rotation, std::string fontPath, Align textAlign, Vec2 bounds, Fit fit, Align boundsAlign, Color color) : Spatial(true) {
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
			FLEX_QUAT(rotation)
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

void Text::setText(std::string text) {
	messenger->sendSignal(
		getNodePath(),
		"setText",
		FLEX_ARG(FLEX_STRING(text))
	);
}

void Text::setColor(Color color) {
	messenger->sendSignal(
		getNodePath(),
		"setText",
		FLEX_ARG(FLEX_COLOR(color))
	);
}

} // namespace StardustXRFusion
