#include "../common/flex.hpp"
#include "sk_math.hpp"

#pragma once

namespace StardustXRFusion {

	///////////////////////////////////////////
	// Conversion from flex to SKMath

	#define SK_VEC2(vec) SKMath::vec2{\
		vec[0].AsFloat(),\
		vec[1].AsFloat()\
	}
	#define SK_VEC3(vec) SKMath::vec3{\
		vec[0].AsFloat(),\
		vec[1].AsFloat(),\
		vec[2].AsFloat()\
	}
	#define SK_QUAT(quat_) SKMath::quat{\
		quat_[0].AsFloat(),\
		quat_[1].AsFloat(),\
		quat_[2].AsFloat(),\
		quat_[3].AsFloat()\
	}
}
