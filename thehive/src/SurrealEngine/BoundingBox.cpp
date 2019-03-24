#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
:BoundingBox(
    glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3(),
    glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3()
)
{}

BoundingBox::BoundingBox(
    glm::vec3 _BLF, glm::vec3 _BRF, glm::vec3 _URF, glm::vec3 _ULF,
    glm::vec3 _ULB, glm::vec3 _URB, glm::vec3 _BRB, glm::vec3 _BLB
)
:BLF(_BLF), BRF(_BRF), URF(_URF), ULF(_ULF),
 ULB(_ULB), URB(_URB), BRB(_BRB), BLB(_BLB)
{}

BoundingBox::BoundingBox(const BoundingBox &origin)
:BoundingBox(origin.BLF, origin.BRF, origin.URF, origin.ULF,
             origin.ULB, origin.URB, origin.BRB, origin.BLB)
{}