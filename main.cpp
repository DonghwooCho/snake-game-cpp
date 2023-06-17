#include <iostream>
#include <ncurses.h>
#include "src/map.h"
#include "src/game.h"
#include "src/drawable.h"

#define MAP_COLOR    1
#define SCORE_COLOR  2
#define MAP_HEIGHT   25
#define MAP_WIDTH    MAP_HEIGHT * 2

using namespace std;

int main() {
    
    // 초기 라이브러리 설정
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    refresh();

    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_BLUE, 150, 370, 750);

    init_pair(MAP_COLOR, COLOR_RED, COLOR_GREEN);
    init_pair(SCORE_COLOR, COLOR_CYAN, COLOR_YELLOW);
    init_pair(3, COLOR_MAGENTA, COLOR_BLUE);
    init_pair(4, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_WHITE);
    init_pair(7, COLOR_BLUE, COLOR_WHITE);


    
    wbkgd(stdscr, COLOR_PAIR(3));

    attron(COLOR_PAIR(SCORE_COLOR));
    refresh();

    Game game(MAP_HEIGHT, MAP_WIDTH, 300);
    
    attroff(COLOR_PAIR(SCORE_COLOR));

    while (!game.isOver()) {
        game.processInput();
        
        game.updateState();

        game.refresh();
    }

    getch();
    endwin();

    cout << "Your Score: " << game.getScore() << " points" << endl;
    // cout << "Game Over" << endl;

    return 0;
}