#ifndef GAME_H
#define GAME_H
#define MAP_HEIGHT   25
#define MAP_WIDTH    MAP_HEIGHT * 2

#include <ncurses.h>
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
            chtype element = map.getChar(next.getY(), next.getX());
            switch(element) {
                case 'A':
                    eatApple();
                    break;
                case ' ':
                case 321: // A
                case 288: // 검은색
                case 1312: // 검은색
                {
                    
                    int emptyRow = snake.tail().getY();
                    int emptyCol = snake.tail().getX();
                    // 뒤따라 오는 맵 색깔
                    map.setOnColor(5);
                    map.add(Empty(emptyRow, emptyCol));
                    map.setOffColor(5);

                    snake.removePiece();
                    break;
                }
                // case 291: 내 몸에 부딪힌 경우
                default:
                    gameOver = true;
                    endwin();
                    std::cout << "NUM: " << map.getChar(next.getY(), next.getX()) 
                    << "   |   " << std::endl;
                    break;
            }
        }

        
        // 뱀 몸통 색깔 바꾸기
        map.setOnColor(7);
        map.findSnakeBody();
        map.setOffColor(7);

        // 뱀 머리 색깔  
        map.setOnColor(6);
        map.add(next);
        snake.addPiece(next);
        map.setOffColor(6);

    }
    void createApple() {
        int y, x;
        map.getEmptyCoordinates(y, x);
        // 사과 색깔
        //map.setOnColor(1);
        apple = new Apple(y, x);
        map.add(*apple);
        //map.setOffColor(1);
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

        map.setOnColor(3);
        handleNextPiece(snake.nextHead());
        map.setOffColor(3);

        if(apple == NULL) {
            createApple();
        }
    }

    void processInput() {
        chtype input = map.input();

        map.setOnColor(2);
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
        map.setOffColor(2);
    }

    void updateState() {
        
        // 뒤따라 오는 흔적 색깔
        map.setOnColor(3);
        handleNextPiece(snake.nextHead());
        map.setOffColor(3);

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