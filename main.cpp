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
    printw("Hello World!");
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

/*
    // 초기 라이브러리 설정
    initscr();
    start_color();

    // 색깔 설정
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_WHITE);

    // 콘솔 색깔 설정
    box(stdscr, 0, 0);
    wbkgd(stdscr, COLOR_PAIR(1));

    // 콘솔 창 크기 가져오기
    int consoleHeight, consoleWidth;
    getmaxyx(stdscr, consoleHeight, consoleWidth);

    // 맵 크기 및 위치 설정
    int mapHeight = 22;
    int mapWidth = 42;

    // 맵 생성
    WINDOW *map = newwin(mapHeight, mapWidth, 2, 5);
    wattron(map, COLOR_PAIR(1));
    box(map, 0, 0);
    wbkgd(map, COLOR_PAIR(2));

    //wborder(map, '┃', '┃', '━', '━', '┏', '┓', '┗', '┛');
    wborder(stdscr, '1', '1', '1', '1', '2', '2', '2', '2');
    wborder(map, '1', '1', '1', '1', '2', '2', '2', '2');
    wmove(map, 1, 1);

    for(int row = 0; row < mapHeight - 2; row++) {
        for(int col = 0; col < mapWidth - 2; col++) {
             mvwprintw(map, row + 1, col + 1, "0");
        }
    }

    // 점수판 크기 및 위치 설정
    int scoreHeight = 10;
    int scoreWidth = 42;

    // 점수판 생성
    WINDOW *score = newwin(scoreHeight, scoreWidth, 2, 52);
    wbkgd(score, COLOR_PAIR(3));
    box(score, 0, 0);

    wborder(score, '1', '1', '1', '1', '2', '2', '2', '2');
    wmove(score, 1, 1);
    wprintw(score, "Score Board");

    // 점수판 크기 및 위치 설정
    int missionHeight = 10;
    int missionWidth = 42;

    // 점수판 생성
    WINDOW *mission = newwin(missionHeight, missionWidth, 14, 52);
    wbkgd(mission, COLOR_PAIR(3));
    box(mission, 0, 0);

    wborder(mission, '1', '1', '1', '1', '2', '2', '2', '2');
    wmove(mission, 1, 1);
    wprintw(mission, "Mission Board");

    // 화면 리로드
    refresh();
    wrefresh(map);
    wrefresh(score);
    wrefresh(mission);

    // 사용자 입력 대기
    getch();

    delwin(mission);
    delwin(score);
    delwin(map);
    endwin();
    */