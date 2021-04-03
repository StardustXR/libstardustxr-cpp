#pragma once

#include <string>

namespace StardustXRFusion {

class Node {
public:
	explicit Node();
	~Node();

	std::string getNodePath();
protected:
	std::string nodeName;
	std::string nodePath;
};

} // namespace StardustXRFusion
