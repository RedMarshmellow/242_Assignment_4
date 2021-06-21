#include "resource.h"


int resource::Resupply() {
    return replenish;
}

resource::resource(int size, char representingChar, int replenish, resource::Types type) : entity(size,
                                                                                                  representingChar),
                                                                                           replenish(replenish),
                                                                                           type(type) {}

medkit::medkit(int size, char representingChar, int replenish, resource::Types type) : resource(
        size, representingChar, replenish, type) { size = (this->getRepresentingChar() == '+') ? S : L; }

medkit::Sizes medkit::returnsize() {
    return this->size;
}

ammo::ammo(int size, char representingChar, int replenish, resource::Types type) : resource(size, representingChar,
                                                                                            replenish, type) {}
