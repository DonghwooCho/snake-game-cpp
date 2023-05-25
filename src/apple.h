#ifndef APPLE_H
#define APPLE_H

#include "drawable.h"

class Apple : public Drawable {
public:
    Apple(int y, int x) {
        this -> y = y;
        this -> x = x;
        this -> ch = 'A';
    }
};

#endif // EMPTY_H