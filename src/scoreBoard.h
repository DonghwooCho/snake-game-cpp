#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard {
    WINDOW *container;
public:
    ScoreBoard() {

    }
    ScoreBoard(int width, int y, int x) {
        container = newwin(6, width, y, x);
        wbkgd(container, COLOR_PAIR(4));
    }

    void init(int initScore) {
        clear();
        mvwprintw(container, 1, 1, "<Score Board>");
        mvwprintw(container, 3, 1, "Score: ");
        mvwprintw(container, 4, 1, "Item: ");
        updateScore(initScore);
        refresh();
    }

    void updateScore(int score) {
        mvwprintw(container, 3, container->_maxx - 10, "%10llu", score);
        mvwprintw(container, 4, container->_maxx - 10, "%10llu", score / 100);
    }

    void clear() {
        wclear(container);
    }

    void refresh() {
        wrefresh(container);
    }
};

#endif // SCOREBOARD_H