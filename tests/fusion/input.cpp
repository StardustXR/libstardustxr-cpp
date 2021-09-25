#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include "fusion/flex.hpp"

#include "fusion/fusion.hpp"
#include "fusion/types/fields/boxfield.hpp"
#include "fusion/types/input/inputhandler.hpp"
#include "fusion/types/input/types/handinput.hpp"
#include "fusion/types/input/types/pointerinput.hpp"

using namespace SKMath;
using namespace StardustXRFusion;

void PrintDatamap(const Datamap &datamap) {

	printf("\tDatamap:\n");
	std::vector<std::string> keys = datamap.keys();
	for(std::string key : keys) {
		printf("\t\t%s\n", key.c_str());
	}
	// for(size_t i=0; i<datamap.size(); ++i) {
	// 	printf("\t\t%s: ", datamapKeys[i].AsString().c_str());
	// 	flexbuffers::Reference datamapValue = datamapValues[i];
	// 	if(datamapValue.IsBool())
	// 		printf(datamapValue.AsBool() ? "true\n" : "false\n");
	// 	else if(datamapValue.IsIntOrUint())
	// 		printf("%d\n", datamapValue.AsInt32());
	// 	else if(datamapValue.IsFloat())
	// 		printf("%f\n", datamapValue.AsFloat());
	// 	else if(datamapValue.IsTypedVector()) {
	// 		flexbuffers::TypedVector datamapValueVector = datamapValue.AsTypedVector();
	// 		printf("(");
	// 		for(size_t i=0; i<datamapValueVector.size(); i++) {
	// 			printf("%f", datamapValueVector[i].AsFloat());
	// 			if(i < datamapValueVector.size()-1)
	// 				printf(", ");
	// 		}
	// 		printf(")\n");
	// 	}
	// }
}

int main(int, char *[]) {
	StardustXRFusion::Setup();

	BoxField field(SKMath::vec3_zero, SKMath::quat_identity, SKMath::vec3_one);
	InputHandler handler(nullptr, field, SKMath::vec3_zero, SKMath::quat_identity);

	handler.actions["test"] = [&]() {
		printf("Action test successful\n");
	};
	handler.updateActions();

	handler.pointerHandlerMethod = [&](const StardustXRFusion::PointerInput &pointer, const Datamap &datamap) {
		printf("Input event:\n");
		printf("\tdistance:    %f\n", pointer.distance);
		printf("\tPointer:\n");
		printf("\t\torigin:      (%f, %f, %f)\n", pointer.origin.x, pointer.origin.y, pointer.origin.z);
		printf("\t\tdirection:   (%f, %f, %f)\n", pointer.direction.x, pointer.direction.y, pointer.direction.z);
		printf("\t\ttilt:        %f\n", pointer.tilt);
		PrintDatamap(datamap);
		return false;
	};
	handler.handHandlerMethod = [](const StardustXRFusion::HandInput &hand, const Datamap &datamap) {
		printf("Input event:\n");
		printf("\tdistance:    %f\n", hand.distance);
		printf("\tHand:\n");
		const SKMath::vec3 palmPosition = hand.palm.pose.position;
		const SKMath::quat palmRotation = hand.palm.pose.orientation;
		printf("\t\tpalm:  (%f, %f, %f), (%f, %f, %f, %f)\n", palmPosition.x, palmPosition.y, palmPosition.z, palmRotation.w, palmRotation.x, palmRotation.y, palmRotation.z);
		PrintDatamap(datamap);
		return false;
	};

	InputHandler::getInputHandlers(&handler, [&](std::vector<InputActions> &basics) {
		printf("Input Handlers:\n");
		for(InputActions &basic : basics) {
			printf("\t%s: (%f, %f, %f)\n", basic.uuid.c_str(), basic.position.x, basic.position.y, basic.position.z);
			basic.getActions([](std::vector<std::string> &actions) {
				for(std::string &action : actions) {
					printf("\t\t%s", action.c_str());
				}
			});
		}
		handler.runAction("test");
	});
	StardustXRFusion::StallMainThread();
}
