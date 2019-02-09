#include <iostream>

#include "PrintVector.hpp"

void printVec3(glm::vec3 vec)
{
    std::cout << "Vec3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")"
        << std::endl;
}
