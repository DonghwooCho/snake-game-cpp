#ifndef GROWTHITEM_H
#define GROWTHITEM_H

#include "drawable.h"

class GrowthItem : public Drawable {
public:
    GrowthItem(int y, int x) {
        this -> y = y;
        this -> x = x;
        this -> ch = ACS_DIAMOND;
    }
};

#endif // GROWTHITEM_H