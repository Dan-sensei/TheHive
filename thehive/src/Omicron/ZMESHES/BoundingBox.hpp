#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox{
    BoundingBox();
    BoundingBox(
        glm::vec3 _ULF, glm::vec3 _URF, glm::vec3 _BLF, glm::vec3 _BRF,
        glm::vec3 _ULB, glm::vec3 _URB, glm::vec3 _BLB, glm::vec3 _BRB
    );
    BoundingBox(const BoundingBox &origin);

    glm::vec3 ULF;  // Upper Left Front
    glm::vec3 URF;  // Upper Right Front
    glm::vec3 BLF;  // Bottom Left Front
    glm::vec3 BRF;  // Bottom Right Front
    glm::vec3 ULB;  // Upper Left Back
    glm::vec3 URB;  // Upper Right Back
    glm::vec3 BLB;  // Bottom Left Back
    glm::vec3 BRB;  // Bottom Right Back

};

#endif
