#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{
    AABB[0] = glm::vec3();
    AABB[1] = glm::vec3();
    AABB[2] = glm::vec3();
    AABB[3] = glm::vec3();
    AABB[4] = glm::vec3();
    AABB[5] = glm::vec3();
    AABB[6] = glm::vec3();
    AABB[7] = glm::vec3();
}

BoundingBox::BoundingBox(glm::vec3 _AABB[8]) {
    AABB[0] = _AABB[0];
    AABB[1] = _AABB[1];
    AABB[2] = _AABB[2];
    AABB[3] = _AABB[3];
    AABB[4] = _AABB[4];
    AABB[5] = _AABB[5];
    AABB[6] = _AABB[6];
    AABB[7] = _AABB[7];
}

BoundingBox::BoundingBox(const BoundingBox &origin) {
    AABB[0] = origin.AABB[0];
    AABB[1] = origin.AABB[1];
    AABB[2] = origin.AABB[2];
    AABB[3] = origin.AABB[3];
    AABB[4] = origin.AABB[4];
    AABB[5] = origin.AABB[5];
    AABB[6] = origin.AABB[6];
    AABB[7] = origin.AABB[7];
}
