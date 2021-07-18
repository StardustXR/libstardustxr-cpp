#include "../flex.hpp"
#include "sk_math.hpp"

#pragma once

using namespace SKMath;

namespace StardustXRFusion {

	///////////////////////////////////////////
	// Conversion from flex to SKMath

	#define SK_VEC3(vec) {\
		vec[0].AsFloat(),\
		vec[1].AsFloat(),\
		vec[2].AsFloat()\
	}
	#define SK_QUAT(quat) {\
		quat[0].AsFloat(),\
		quat[1].AsFloat(),\
		quat[2].AsFloat(),\
		quat[3].AsFloat()\
	}
}
