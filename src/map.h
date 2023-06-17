#ifndef MAP_H
#define MAP_H
#define MAP_COLOR    1
#define SCORE_COLOR  2
#define MAP_HEIGHT   25
#define MAP_WIDTH    MAP_HEIGHT * 2

#include <ncurses.h>
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
    Map(int height, int width, int speed) : height{height}, width{width} {
        int consoleX, consoleY;
        getmaxyx(stdscr, consoleY, consoleX);

        startRow = 2;
        startCol = 5;
        
        container = newwin(height, width, startRow, startCol);
        keypad(container, true);

        wrefresh(container);

        setTimeout(1000);
    }

    void init() {
        clear();
        refresh();

        // wattron(container, COLOR_PAIR(MAP_COLOR));
    }

    void add(Drawable drawable) {
        addChar(drawable.getY(), drawable.getX(), drawable.getChar());
    }

    void addChar(int y, int x, chtype ch) {
        mvwaddch(container, y, x, ch);
    }

    void addBox() {
        wattron(container, COLOR_PAIR(2));
        box(container, 0, 0);
        wattroff(container, COLOR_PAIR(2));

        wattron(container, COLOR_PAIR(1));
        mvwaddch(container, 0, 0, '+');
        mvwaddch(container, 0, MAP_WIDTH - 1, '+');
        mvwaddch(container, MAP_HEIGHT - 1, 0, '+');
        mvwaddch(container, MAP_HEIGHT - 1, MAP_WIDTH - 1, '+');
        wattroff(container, COLOR_PAIR(1));

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

    void setOnColor(int color) {
        wattron(container, COLOR_PAIR(color));
    }

    void setOffColor(int color) {
        wattroff(container, COLOR_PAIR(color));
    }

    void setTimeout(int timeout) {
        wtimeout(container, timeout);
    }

    void findSnakeBody() {
        for (int row = 1; row < MAP_HEIGHT - 1; row++) {
            for (int col = 1; col < MAP_WIDTH - 1; col++) {
                chtype ch = mvwinch(container, row, col);
                if(ch == 263712) {
                    mvwaddch(container, row, col, ' ' | A_REVERSE);
                }
            }
        }
    }

    int getSnakeLength() {
        int length = 0;
        for (int row = 1; row < MAP_HEIGHT - 1; row++) {
            for (int col = 1; col < MAP_WIDTH - 1; col++) {
                chtype ch = mvwinch(container, row, col);
                if(ch == 263456 || ch == 263712) {
                    length += 1;
                }
            }
        }
        return length;
    }

    int countItem() {
        int count = 0;
         for (int row = 1; row < MAP_HEIGHT - 1; row++) {
            for (int col = 1; col < MAP_WIDTH - 1; col++) {
                chtype ch = mvwinch(container, row, col);
                if(ch == 4195168 || ch == 4194656) {
                    count += 1;
                }
            }
        }
        return count;
    }

};

#endif // MAP_H