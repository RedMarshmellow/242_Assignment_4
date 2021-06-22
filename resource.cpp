#include "resource.h"


int resource::resupply() {
    return replenish;
}

resource::resource(int size, char representingChar, int replenish, resourceTypes type) : entity(size,
                                                                                                representingChar,
                                                                                                Resource),
                                                                                         replenish(replenish),
                                                                                         type(type) {}

resourceTypes resource::getType() const {
    return type;
}

medkit::medkit(int size) : resource(
        size, (size==1)?'+':'*', (size==1)?10:20, Health) {}

medkit::Sizes medkit::returnsize() {
    return this->size;
}

ammunition::ammunition(): resource(1,'A',10,Ammo) {}
