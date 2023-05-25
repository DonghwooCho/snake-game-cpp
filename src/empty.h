#ifndef EMPTY_H
#define EMPTY_H

#include "drawable.h"

class Empty : public Drawable {
public:
    Empty(int y, int x) {
        this -> y = y;
        this -> x = x;
        this -> ch = ' ';
    }
};

#endif // EMPTY_H