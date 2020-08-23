#include "stardust_scenegraph/stardust_scenegraph.hpp"

namespace StardustXR {

void StardustScenegraph::onPathStep(std::string path, std::function<void(std::string)> pathStepFunction) {
	std::istringstream stream(path);
	stream.get(); //Remove beginning slash

	std::string pathStep;
	while(std::getline(stream, pathStep, '/')) {
		pathStepFunction(pathStep);
	}
}

void StardustScenegraph::sendSignal(std::string path, std::string method, flexbuffers::Reference data) {
	this->executeMethod(path, method, data, false);
}
std::vector<uint8_t> StardustScenegraph::executeMethod(std::string path, std::string method, flexbuffers::Reference args) {
	return this->executeMethod(path, method, args, true);
}

std::vector<uint8_t> StardustScenegraph::executeMethod(std::string path, std::string method, flexbuffers::Reference args, bool returnValue) {
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
		printf("Method %s on node %s not found", method.c_str(), path.c_str());
		return std::vector<uint8_t>();
	}
	return (currentNode->methods[method])(args, returnValue);
}

void StardustScenegraph::addNode(std::string path, Node *node) {
	//Get the name of the node to create
	std::string lastNodeName = path.substr(path.find_last_of("/")+1);
	Node *currentNode = &root;
	this->onPathStep(path, [&](std::string pathStep) {
		if(pathStep == lastNodeName)
			currentNode->children[pathStep] = node;
		else if(currentNode->children[pathStep] == nullptr)
			currentNode->children[pathStep] = new Node();
		currentNode = currentNode->children[pathStep];
	});
}

}
