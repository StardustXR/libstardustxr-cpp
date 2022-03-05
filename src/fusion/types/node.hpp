#pragma once

#include <string>

namespace StardustXRFusion {

class Node {
public:
	explicit Node();
	Node(const Node &original);
	~Node();

	bool operator==(const Node& other) const;
	bool operator!=(const Node& other) const;

	bool operator<(const Node& other) const;

	std::string getNodePath() const;
	std::string getNodeName() const;

	void setEnabled(bool enabled);

	static uint32_t generateUUID();

protected:
	std::string nodeName = "";
	std::string nodePath = "";
	bool destroyable = true;
};

} // namespace StardustXRFusion
