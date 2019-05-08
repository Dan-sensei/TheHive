#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox{
    BoundingBox();
    BoundingBox(glm::vec3 _AABB[8]);
    BoundingBox(const BoundingBox &origin);

    glm::vec3 AABB[8];

};

#endif
