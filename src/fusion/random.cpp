#include "random.hpp"

namespace StardustXRFusion {

std::random_device Random::rand_device;
std::mt19937 Random::gen(Random::rand_device());
std::mutex Random::randoMutex;

}
