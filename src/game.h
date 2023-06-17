#ifndef GAME_H
#define GAME_H
#define MAP_HEIGHT   25
#define MAP_WIDTH    MAP_HEIGHT * 2

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "empty.h"
#include "growthItem.h"
#include "poisonItem.h"
#include "map.h"
#include "snake.h"
#include "scoreBoard.h"
#include "drawable.h"
#include <cstdlib>
#include <ctime>


class Game {
private:
    Map map;
    bool gameOver;
    GrowthItem *growthItem;
    PoisonItem *poisonItem;
    Snake snake;
    ScoreBoard scoreBoard;
    int score;

    void handleNextPiece(SnakePiece next) {

        if(growthItem != NULL || poisonItem != NULL) {
            chtype element = map.getChar(next.getY(), next.getX());
            switch(element) {
                case 4195168: // 좋은 아이템 먹었을 때
                    eatGrowthItem();
                    break;
                case 4194656: // 나쁜 아이템 먹었을 때
                    eatPoisonItem();

                    map.setOnColor(5);
                    for(int i = 0; i < 2; i++) {
                        map.add(Empty(snake.tail().getY(), snake.tail().getX()));
                        snake.removePiece();
                    }
                    map.setOffColor(5);

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
                default:
                    gameOver = true;
                    endwin();
                    std::cout << "NUM: " << map.getChar(next.getY(), next.getX()) 
                    << "   |   " << std::endl;
                    break;
            }
        }

        
        // 뱀 몸통 색깔 바꾸기
        map.setOnColor(5);
        map.findSnakeBody();
        map.setOffColor(5);

        // 뱀 머리 색깔  
        map.setOnColor(6);
        map.add(next);
        snake.addPiece(next); // 헤드 생성
        map.setOffColor(6);
        
    }
    
    void createPoisonhItem() {
        int y, x;
        map.getEmptyCoordinates(y, x);
        // 나쁜 아이템 색깔
        map.setOnColor(1);
        poisonItem = new PoisonItem(y, x);
        map.add(*poisonItem);
        map.setOffColor(1);
    }

    void createGrowthItem() {
        int y, x;
        map.getEmptyCoordinates(y, x);
        // 좋은 아이템 색깔
        map.setOnColor(3);
        growthItem = new GrowthItem(y, x);
        map.add(*growthItem);
        map.setOffColor(3);
    }

    void destroyPoisonItem() {
        delete poisonItem;
        poisonItem = NULL;
    }

    void destroyGrowthItem() {
        delete growthItem;
        growthItem = NULL;
    }

    void eatPoisonItem() {
        destroyPoisonItem();
        score += 100;
        scoreBoard.updateScore(score);
    }


    void eatGrowthItem() {
        destroyGrowthItem();
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
        delete growthItem;
        delete poisonItem;
    }

    void init() {
        growthItem = NULL;
        poisonItem = NULL;
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

        if(growthItem == NULL && poisonItem == NULL) {
            randomCreateItem();
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

        if(map.countItem() < 3) {
            randomCreateItem();
        }

        int length = map.getSnakeLength();
        if(length < 3) {
            gameOver = true;
            endwin();
            std::cout << "Game Over: Your snake length shorter than 3!" << std::endl;
        }
    }

    void randomCreateItem() {
        srand(time(nullptr));
        int choice = rand() % 2;

        if(choice == 0) {
            createGrowthItem();
        } else {
            createPoisonhItem();
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