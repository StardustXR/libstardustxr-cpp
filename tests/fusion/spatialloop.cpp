#include "fusion/fusion.hpp"
#include "fusion/types/spatial/spatial.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	Spatial spatial1(StardustXRFusion::Root());
	Spatial spatial2(&spatial1);
	Spatial spatial3(&spatial2);
	Spatial spatial4(&spatial3);

	spatial1.setSpatialParent(&spatial4);

	StardustXRFusion::StallMainThread();
}
