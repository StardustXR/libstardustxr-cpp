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
	explicit ItemAcceptor(Spatial *parent, Field &field, Vec3 origin, Quat rotation, std::string itemType);
	virtual ~ItemAcceptor();
protected:
	virtual std::vector<uint8_t> acceptorCallback(flexbuffers::Reference data, bool) = 0;
};

}
