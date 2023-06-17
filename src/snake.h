#ifndef SNAKE_H
#define SNAKE_H

#include "drawable.h"
#include <queue>

enum Direction {
    up = -1, down = 1, left = -2, right = 2
};

class SnakePiece : public Drawable {
public:
    SnakePiece() {
        this -> x = 0;
        this -> y = 0;
        this -> ch = ' ' | A_REVERSE;
    }

    SnakePiece(int y, int x) {
        this -> x = x;
        this -> y = y;
        this -> ch = ' ' | A_REVERSE;
    }
};


class Snake : public Drawable {
    std::queue<SnakePiece> prePieces;
    Direction currDirection;
    
public:
    Snake() {
        currDirection = down;
    }

    void addPiece(SnakePiece piece) {
        prePieces.push(piece);
    }

    void removePiece() {
        prePieces.pop();
    }

    SnakePiece tail() {
        return prePieces.front();
    }

    SnakePiece head() {
        return prePieces.back();
    }

    Direction getDirection() {
        return currDirection;
    }

    void setDirection(Direction direction) {
        if(currDirection + direction != 0) {
            currDirection = direction; // 반대 방향이 아니면, 바꿈
        }
    }

    SnakePiece nextHead() {
        int row = head().getY();
        int col = head().getX();

        switch (currDirection) {
            case up:
                row--;
                break;
            case down:
                row++;
                break;
            case left:
                col--;
                break;
            case right:
                col++;
                break;
        }

        return SnakePiece(row, col);
    }
};

#endif // SNAKE_H