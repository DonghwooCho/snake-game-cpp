#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdlib.h>
#include "empty.h"
#include "apple.h"
#include "map.h"
#include "snake.h"
#include "scoreBoard.h"
#include "drawable.h"

class Game {
private:
    Map map;
    bool gameOver;
    Apple *apple;
    Snake snake;
    ScoreBoard scoreBoard;
    int score;

    void handleNextPiece(SnakePiece next) {

        if(apple != NULL) {
            switch(map.getChar(next.getY(), next.getX())) {
                case 'A':
                    eatApple();
                    break;
                case ' ':
                {
                    int emptyRow = snake.tail().getY();
                    int emptyCol = snake.tail().getX();
                    map.add(Empty(emptyRow, emptyCol));
                    snake.removePiece();
                    break;
                }
                default:
                    gameOver = true;
                    break;
            }
        }

        map.add(next);
        snake.addPiece(next);
    }

    void createApple() {
        int y, x;
        map.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        map.add(*apple);
    }

    void destroyApple() {
        delete apple;
        apple = NULL;
    }

    void eatApple() {
        destroyApple();
        score += 100;
        scoreBoard.updateScore(score);
    }

public:
    Game(int height, int width, int speed = 500) : map(height, width, speed) {
        int sbRow = map.getStartRow() + height;
        int sbCol = map.getStartCol();
        scoreBoard = ScoreBoard(width, sbRow, sbCol);
        init();
    }

    ~Game() {
        delete apple;
    }

    void init() {
        apple = NULL;
        map.init();
        score = 0;
        scoreBoard.init(score);
        gameOver = false;
        srand(time(NULL));
        snake.setDirection(down);

        handleNextPiece(SnakePiece(1, 1));
        handleNextPiece(snake.nextHead());
        handleNextPiece(snake.nextHead());
        snake.setDirection(right);
        handleNextPiece(snake.nextHead());

        if(apple == NULL) {
            createApple();
        }
    }

    void processInput() {
        chtype input = map.input();

        switch(input) {
            case KEY_UP:
            case 'W':
            case 'w':
                snake.setDirection(up);
                break;
            case KEY_DOWN:
            case 'S':
            case 's':
                snake.setDirection(down);
                break;
            case KEY_LEFT:
            case 'A':
            case 'a':
                snake.setDirection(left);
                break;
            case KEY_RIGHT:
            case 'D':
            case 'd':
                snake.setDirection(right);
                break;
            case 'P':
            case 'p': // 다시 p 누를 때까지 일시 정지
                map.setTimeout(-1);
                while(map.input() != 'P' && map.input() != 'p') {
                }
                map.setTimeout(1000); // 1초 뒤 다시 시작
                break;
            default:
                break;
        }
    }

    void updateState() {

        handleNextPiece(snake.nextHead());

        if(apple == NULL) {
            createApple();
        }
    }

    void refresh() {
        map.refresh();
        scoreBoard.refresh();
    }

    bool isOver() {
        return gameOver;
    }

    int getScore() {
        return score;
    }
};

#endif // GAME_H