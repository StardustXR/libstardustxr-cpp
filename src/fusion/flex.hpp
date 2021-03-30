#include <../client/messenger.hpp>
#include <unistd.h>
#include "sk_math.hpp"

#pragma once

using namespace std;
using namespace SKMath;

namespace StardustXR::Fusion {
	///////////////////////////////////////////
	// Core Flexbuffer macros

	#define FLEX_ARG(arg) \
		[&](flexbuffers::Builder &fbb) {\
			arg\
		}
	#define FLEX_ARGS(args) \
		[&](flexbuffers::Builder &fbb) {\
			FLEX_VEC(args)\
		}
	#define FLEX_SINGLE(arg) StardustXR::FlexbufferFromArguments(FLEX_ARG(arg))
	#define FLEX(args) StardustXR::FlexbufferFromArguments(FLEX_ARGS(args))

	///////////////////////////////////////////
	// Core Flexbuffer type macros

	#define FLEX_VEC(args) \
		fbb.Vector([&]() {\
			args\
		});
	#define FLEX_STRING(str) \
		fbb.String(str.c_str());
	#define FLEX_FLOAT(flt) \
		fbb.Float(flt);

	///////////////////////////////////////////
	// Special Flexbuffer type macros

	#define FLEX_VEC3(vec) \
		fbb.TypedVector([&]() {\
			fbb.Float(vec.x);\
			fbb.Float(vec.y);\
			fbb.Float(vec.z);\
		});
	#define FLEX_QUAT(quat) \
		fbb.TypedVector([&]() {\
			fbb.Float(quat.w);\
			fbb.Float(quat.x);\
			fbb.Float(quat.y);\
			fbb.Float(quat.z);\
		});

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
