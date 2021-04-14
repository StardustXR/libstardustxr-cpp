#include <chrono>
#include <iostream>
#include <thread>
#include "fusion/flex.hpp"

#include "fusion/fusion.hpp"
#include "fusion/types/fields/boxfield.hpp"
#include "fusion/types/input/inputhandler.hpp"
#include "fusion/types/input/flatbuffers/Input_generated.h"

using namespace SKMath;
using namespace StardustXR;
using namespace StardustXRFusion;

void PrintInputData(const InputData *inputMethod) {
	printf("Input event:\n");
	printf("\tdistance:    %f\n", inputMethod->distance());
	switch (inputMethod->input_type()) {
		case InputDataRaw_Pointer: {
			const Pointer *pointer = inputMethod->input_as_Pointer();
			printf("\tPointer:\n");
			const StardustXR::vec3 *origin = pointer->origin();
			printf("\t\torigin:      (%f, %f, %f)\n", origin->x(), origin->y(), origin->z());
			const StardustXR::vec3 *direction = pointer->direction();
			printf("\t\tdirection:   (%f, %f, %f)\n", direction->x(), direction->y(), direction->z());
			const float tilt = pointer->tilt();
			printf("\t\ttilt:        %f\n", tilt);
		} break;
		case InputDataRaw_Hand: {
			const Hand *hand = inputMethod->input_as_Hand();
			printf("\tHand:\n");
			const StardustXR::vec3 palmPosition = hand->palm()->position();
			const StardustXR::quat palmRotation = hand->palm()->rotation();
			printf("\t\tpalm:  (%f, %f, %f), (%f, %f, %f, %f)\n", palmPosition.x(), palmPosition.y(), palmPosition.z(), palmRotation.w(), palmRotation.x(), palmRotation.y(), palmRotation.z());
		} break;
		default:
			break;
	}

	const flexbuffers::Reference		datamapRoot		= inputMethod->datamap_flexbuffer_root();
	const flexbuffers::Map			datamap			= datamapRoot.AsMap();
	const flexbuffers::TypedVector	datamapKeys		= datamap.Keys();
	const flexbuffers::Vector		datamapValues	= datamap.Values();

	printf("\tDatamap:\n");
	for(size_t i=0; i<datamap.size(); ++i) {
		printf("\t\t%s: ", datamapKeys[i].AsString().c_str());
		flexbuffers::Reference datamapValue = datamapValues[i];
		if(datamapValue.IsBool())
			printf(datamapValue.AsBool() ? "true\n" : "false\n");
		else if(datamapValue.IsIntOrUint())
			printf("%d\n", datamapValue.AsInt32());
		else if(datamapValue.IsFloat())
			printf("%f\n", datamapValue.AsFloat());
		else if(datamapValue.IsTypedVector()) {
			flexbuffers::TypedVector datamapValueVector = datamapValue.AsTypedVector();
			printf("(");
			for(size_t i=0; i<datamapValueVector.size(); i++) {
				printf("%f", datamapValueVector[i].AsFloat());
				if(i < datamapValueVector.size()-1)
					printf(", ");
			}
			printf(")\n");
		}
	}
}

int main(int, char *[]) {
	StardustXRFusion::Setup();

	BoxField field(SKMath::vec3_zero, SKMath::quat_identity, SKMath::vec3_one);
	InputHandler handler(nullptr, &field, SKMath::vec3_zero, SKMath::quat_identity, [](const InputData *data) {
		PrintInputData(data);
		return true;
	});

	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
