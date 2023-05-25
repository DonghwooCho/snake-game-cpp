#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard {
    WINDOW *container;
public:
    ScoreBoard() {

    }
    ScoreBoard(int width, int y, int x) {
        container = newwin(1, width, y, x);
    }

    void init(int initScore) {
        clear();
        mvwprintw(container, 0, 0, "Score: ");
        updateScore(initScore);
        refresh();
    }

    void updateScore(int score) {
        mvwprintw(container, 0, container->_maxx - 10, "%11llu", score);
    }

    void clear() {
        wclear(container);
    }

    void refresh() {
        wrefresh(container);
    }
};

#endif // SCOREBOARD_H