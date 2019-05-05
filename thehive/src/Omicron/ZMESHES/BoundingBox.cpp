#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
:BoundingBox(
    glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3(),
    glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3()
)
{}

BoundingBox::BoundingBox(
    glm::vec3 _ULF, glm::vec3 _URF, glm::vec3 _BLF, glm::vec3 _BRF,
    glm::vec3 _ULB, glm::vec3 _URB, glm::vec3 _BLB, glm::vec3 _BRB
)
:ULF(_ULF), URF(_URF), BLF(_BLF), BRF(_BRF),
 ULB(_ULB), URB(_URB), BLB(_BLB), BRB(_BRB)
{}

BoundingBox::BoundingBox(const BoundingBox &origin)
:BoundingBox(origin.ULF, origin.URF, origin.BLF, origin.BRF,
             origin.ULB, origin.URB, origin.BLB, origin.BRB)
{}
