#pragma once

#include <string>

namespace StardustXRFusion {

class Node {
public:
	explicit Node();
	~Node();

	std::string getNodePath();
	std::string getNodeName();

	void setEnabled(bool enabled);

protected:
	std::string nodeName = "";
	std::string nodePath = "";
};

} // namespace StardustXRFusion
