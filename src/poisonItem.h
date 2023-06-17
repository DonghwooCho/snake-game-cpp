#ifndef POISONITEM_H
#define POISONITEM_H

#include "drawable.h"

class PoisonItem : public Drawable {
public:
    PoisonItem(int y, int x) {
        this -> y = y;
        this -> x = x;
        this -> ch = ACS_DIAMOND;
    }
};

#endif // POISONITEM_H