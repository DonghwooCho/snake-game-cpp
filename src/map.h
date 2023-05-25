#ifndef MAP_H
#define MAP_H

#include <time.h>
#include <stdlib.h>
#include "drawable.h"

class Map{
private:
    WINDOW *container;
    int height;
    int width;
    int startRow;
    int startCol;

public:
    Map(int height, int width, int speed) {
        int consoleX, consoleY;
        getmaxyx(stdscr, consoleY, consoleX);

        startRow = 2;
        startCol = 5;

        container = newwin(height, width, startRow, startCol);
        box(container, 0, 0);
        wrefresh(container);

        this -> height = height;
        this -> width = width;

        wtimeout(container, 1000);

        keypad(container, true);
    }

    void init() {
        clear();
        refresh();
    }

    void add(Drawable drawable) {
        addChar(drawable.getY(), drawable.getX(), drawable.getChar());
    }

    void addChar(int y, int x, chtype ch) {
        mvwaddch(container, y, x, ch);
    }

    void addBox() {
        box(container, 0, 0);
    }

    int getStartRow() {
        return startRow;
    }

    int getStartCol() {
        return startCol;
    }

    chtype input() {
        return wgetch(container);
    }

    chtype getChar (int y, int x) {
        return mvwinch(container, y, x);
    }

    void getEmptyCoordinates(int &y, int &x) {

        while((mvwinch(container, y = rand() % height, x = rand() % width)) != ' ') {
        }
    }

    void clear() {
        wclear(container);
        addBox();
    }

    void refresh() {
        wrefresh(container);
    }

    void setTimeout(int timeout) {
        wtimeout(container, timeout);
    }
};

#endif // MAP_H