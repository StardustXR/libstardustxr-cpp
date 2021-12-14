#pragma once

#include <string>

namespace StardustXRFusion {

class Node {
public:
	explicit Node();
	Node(const Node &original);
	~Node();

	std::string getNodePath();
	std::string getNodeName();

	void setEnabled(bool enabled);

	static uint32_t generateUUID();

protected:
	std::string nodeName = "";
	std::string nodePath = "";
	bool destroyable = true;
};

} // namespace StardustXRFusion
