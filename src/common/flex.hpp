#pragma once

#include <functional>
#include <flatbuffers/flexbuffers.h>

namespace StardustXR {

	typedef std::function<void(flexbuffers::Builder&)> ArgsConstructor;
	typedef std::function<void(flexbuffers::Reference)> Callback;

	static std::vector<uint8_t> FlexbufferFromArguments(ArgsConstructor argsConstructor) {
		flexbuffers::Builder fbb;
		argsConstructor(fbb);
		fbb.Finish();
		return fbb.GetBuffer();
	}

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
	#define FLEX_NULL \
		fbb.Null();
	#define FLEX_BOOL(bol) \
		fbb.Bool(bol);
	#define FLEX_FLOAT(flt) \
		fbb.Float(flt);
	#define FLEX_ADD(var) \
		fbb.Add(var);

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
			fbb.Float(quat.x);\
			fbb.Float(quat.y);\
			fbb.Float(quat.z);\
			fbb.Float(quat.w);\
		});
	#define FLEX_COLOR(color) \
		fbb.TypedVector([&]() {\
			fbb.Float(color.r);\
			fbb.Float(color.g);\
			fbb.Float(color.b);\
			fbb.Float(color.a);\
		});

}