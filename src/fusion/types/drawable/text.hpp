#pragma once

#include <string>

#include "../spatial/spatial.hpp"

namespace StardustXRFusion {

class Text : public Spatial {
public:
	enum Align { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L1066-L1106=)
		XLeft        = 1 << 0,
		YTop         = 1 << 1,
		XCenter      = 1 << 2,
		YCenter      = 1 << 3,
		XRight       = 1 << 4,
		YBottom      = 1 << 5,
		Center       = XCenter | YCenter,
		CenterLeft   = XLeft   | YCenter,
		CenterRight  = XRight  | YCenter,
		TopCenter    = XCenter | YTop,
		TopLeft      = XLeft   | YTop,
		TopRight     = XRight  | YTop,
		BottomCenter = XCenter | YBottom,
		BottomLeft   = XLeft   | YBottom,
		BottomRight  = XRight  | YBottom,
	};
	enum Fit { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L979-L995=)
		Wrap     = 1 << 0,
		Clip     = 1 << 1,
		Squeeze  = 1 << 2,
		Exact    = 1 << 3,
		Overflow = 1 << 4,
	};

	Text(Spatial *parent, std::string text = "Text", float characterHeight = 1.f, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, std::string fontPath = "", Align textAlign = Align::TopLeft, SKMath::vec2 bounds = SKMath::vec2_zero, Fit fit = Fit::Overflow, Align boundsAlign = Align::TopLeft, SKMath::color color = {1,1,1,1});
};

} // namespace StardustXRFusion
