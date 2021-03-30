#pragma once

#include <string>
#include "../../client/node.hpp"

namespace StardustXRFusion {

class Node : public StardustXR::ClientNode {
public:
	explicit Node();
	~Node();

	std::string getNodePath();
protected:
	std::string nodeName;
	std::string nodePath;
};

} // namespace StardustXRFusion
