#include "../common/flex.hpp"
#include "values.hpp"

#pragma once

namespace StardustXRFusion {

	///////////////////////////////////////////
	// Conversion from flex to internal values

	#define STARDUST_VEC2(vec) Vec2{\
		vec[0].AsFloat(),\
		vec[1].AsFloat()\
	}
	#define STARDUST_VEC3(vec) Vec3{\
		vec[0].AsFloat(),\
		vec[1].AsFloat(),\
		vec[2].AsFloat()\
	}
	#define STARDUST_QUAT(vec) Quat{\
		vec[0].AsFloat(),\
		vec[1].AsFloat(),\
		vec[2].AsFloat(),\
		vec[3].AsFloat()\
	}
}
