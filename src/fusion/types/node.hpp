#pragma once

#include <string>

namespace StardustXRFusion {

class Node {
public:
	bool operator==(const Node& other) const;
	bool operator!=(const Node& other) const;

	bool operator<(const Node& other) const;

	const std::string getNodePath() const;
	const std::string getNodeName() const;

	void setEnabled(bool enabled);
	void setBackend(const std::string nodePath, const std::string nodeName);

protected:
	Node(bool destroyable);
	Node(const Node &original);
	~Node();

	std::string nodeName = "";
	std::string nodePath = "";
	bool destroyable = true;
};

} // namespace StardustXRFusion
