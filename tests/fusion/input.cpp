#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>

#include "fusion/fusion.hpp"
#include "fusion/types/fields/boxfield.hpp"
#include "fusion/types/input/inputhandler.hpp"
#include "fusion/types/input/types/handinput.hpp"
#include "fusion/types/input/types/pointerinput.hpp"
#include "values.hpp"


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

	BoxField field(Root(), Vec3::Zero, Quat::Identity, Vec3::One);
	InputHandler handler(Root(), field, Vec3::Zero, Quat::Identity);

	handler.pointerHandlerMethod = [&](const std::string uuid, const StardustXRFusion::PointerInput &pointer, const Datamap &datamap) {
		printf("Input event:\n");
		printf("\tdistance:    %f\n", pointer.distance);
		printf("\tPointer:\n");
		printf("\t\torigin:      (%f, %f, %f)\n", pointer.origin.x, pointer.origin.y, pointer.origin.z);
		printf("\t\tdirection:   (%f, %f, %f)\n", pointer.direction.x, pointer.direction.y, pointer.direction.z);
		printf("\t\ttilt:        %f\n", pointer.tilt);
		PrintDatamap(datamap);
		return false;
	};
	handler.handHandlerMethod = [](const std::string uuid, const StardustXRFusion::HandInput &hand, const Datamap &datamap) {
		printf("Input event:\n");
		printf("\tdistance:    %f\n", hand.distance);
		printf("\tHand:\n");
		const Vec3 palmPosition = hand.palm.pose.position;
		const Quat palmRotation = hand.palm.pose.rotation;
		printf("\t\tpalm:  (%f, %f, %f), (%f, %f, %f, %f)\n", palmPosition.x, palmPosition.y, palmPosition.z, palmRotation.w, palmRotation.x, palmRotation.y, palmRotation.z);
		PrintDatamap(datamap);
		return false;
	};
	StardustXRFusion::RunEventLoop();
}
