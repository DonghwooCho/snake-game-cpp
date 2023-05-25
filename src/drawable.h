#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
public:
    Drawable() {
        y = 0;
        x = 0;
        ch = ' ';
    }

    Drawable(int y, int x, chtype ch) {
        this -> y = y;
        this -> x = x;
        this -> ch = ch;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    chtype getChar() {
        return ch;
    }

protected:
    int y, x;
    chtype ch; 
};

#endif // DRAWABLE_H