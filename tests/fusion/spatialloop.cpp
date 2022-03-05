#include "fusion/fusion.hpp"
#include "fusion/types/spatial/spatial.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	Spatial spatial1 = Spatial::create(StardustXRFusion::Root());
	Spatial spatial2 = Spatial::create(&spatial1);
	Spatial spatial3 = Spatial::create(&spatial2);
	Spatial spatial4 = Spatial::create(&spatial3);

	spatial1.setSpatialParent(&spatial4);

	StardustXRFusion::StallMainThread();
}
