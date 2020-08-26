#ifndef STARDUSTXR_BLANK_SCENEGRAPH_H
#define STARDUSTXR_BLANK_SCENEGRAPH_H

#include "../scenegraph.hpp"
#include <stdio.h>

namespace StardustXR {

class BlankScenegraph : public Scenegraph {
public:
	explicit BlankScenegraph() : Scenegraph() {}

	void sendSignal(std::string path, std::string method, flexbuffers::Reference data) {
		printf("Sending signal with method %s on object with path %s\n", method.c_str(), path.c_str());
		printf("\t");
	}

	std::vector<uint8_t> executeMethod(std::string path, std::string method, flexbuffers::Reference args) {
		printf("Attempting to execute method %s on object with path %s\n", method.c_str(), path.c_str());
		printf("Path matches /test with a value of %i and method with %i\n", path.compare("/test"), method.compare("echo"));

		if (path.compare("/test") == 0) {
			if (method.compare("echo") == 0) {
				printf("Echo method recieved\n");
				if (!args.IsString()) {
					printf("Echo method takes string as argument\n");
					return std::vector<uint8_t>();
				}

				flexbuffers::Builder fbb;
				fbb.String(args.AsString());
				fbb.Finish();

				std::vector<uint8_t> data = fbb.GetBuffer();
				printf("Echoing back \"%s\"\n", args.AsString().c_str());
				return data;
			}
		}
		return std::vector<uint8_t>();
	}
};

} // namespace StardustXR

#endif
