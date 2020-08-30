#pragma once

#include <vector>

namespace DCore {
namespace Utils {
class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    ~PerlinNoise();

    // Get a noise value, for 2D images z can have any value
    double noise(double x, double y, double z);

private:
    std::vector<int32_t> permutationVector;

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
};
}  // namespace Utils
}  // namespace DCore