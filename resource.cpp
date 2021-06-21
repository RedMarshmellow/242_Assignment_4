#include "resource.h"


int resource::Resupply() {
    return replenish;
}

resource::resource(int size, char representingChar, int replenish, resource::Types type) : entity(size,
                                                                                                  representingChar),
                                                                                           replenish(replenish),
                                                                                           type(type) {}

medkit::medkit(int size) : resource(
        size, (size==1)?'+':'*', (size==1)?10:20, Health) {}

medkit::Sizes medkit::returnsize() {
    return this->size;
}

ammunition::ammunition(): resource(1,'A',10,Ammo) {}
