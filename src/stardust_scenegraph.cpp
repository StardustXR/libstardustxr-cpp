#include "stardust_scenegraph/stardust_scenegraph.hpp"

namespace StardustXR {

void StardustScenegraph::sendSignal(std::string path, std::string method, flexbuffers::Reference data) {}

std::vector<uint8_t> StardustScenegraph::executeMethod(std::string path, std::string method, flexbuffers::Reference args) {
	//Find the node referenced by the path string

	Node *currentNode = &root;
	this->onPathStep(path, [&](std::string pathStep) {
		currentNode = currentNode->children[pathStep];
		if(currentNode == nullptr) {
			printf("Node %s not found", pathStep.c_str());
			return;
		}
	});

	if(currentNode->methods[method] == nullptr) {
		printf("Method %s on node %s not found", method.c_str(), pathStep.c_str());
		return std::vector<uint8_t>();
	}
	Method nodeMethod = currentNode->methods[method];
	return (currentNode->*nodeMethod)(args, true);
}

void StardustScenegraph::onPathStep(std::string path, void (*pathStepFunction)(std::string pathStep)) {
	std::istringstream stream(path);
	stream.get(); //Remove beginning slash

	std::string pathStep;
	while(std::getline(stream, pathStep, '/')) {
		(*pathStepFunction)(pathStep);
	}
}

}
