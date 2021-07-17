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

}