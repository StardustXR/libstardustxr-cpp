#pragma once

#include "../spatial/spatial.hpp"
#include "../fields/field.hpp"

#include <vector>

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class ItemAcceptor : public Spatial {
public:
	ItemAcceptor(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation, std::string createMethod);
protected:
	virtual std::vector<uint8_t> acceptorCallback(flexbuffers::Reference data, bool) = 0;
};

}
