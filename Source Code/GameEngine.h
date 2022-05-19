#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "GameObject.h"
#include "Map.h"
#include "Snake.h"
#include "Power.h"
#include "Sound.h"
enum KeyPress {
    UP, DOWN, LEFT, RIGHT, USINGPOWER
};

enum Status {
    EXITING, RUNNING,
};

struct GameEngine {
    Snake* snakeA;
    Snake* snakeB;

    Map* map;
    int width;
    int height;

    std::vector<GameObject> food;
    int foodNumber;
    std::vector<GameObject> walls;
    Power* power;
    std::vector<GameObject> bombs;

    int status;
    int countStep;
    bool isAwin;
    bool isBwin;

public:
    GameEngine(int _width, int _height, int _foodNumber);
    ~GameEngine() = default;

    int getStatus() const;
    int getKey() const;
    Coordinate getSnakeDirection(int key);
    bool isAwinner();
    bool isBwinner();

    void generateWall();
    Coordinate makeNewGameObject();
    void generatePower();
    void deletePower();
    void generateFood();
    void makeFood();
    void deleteFood(Coordinate nextHead);
    bool isPositionOnSnake(Coordinate foodPos);
    bool isPositionOnWall(Coordinate Pos);
    bool isPositionOnFood(Coordinate foodPos);
    bool isPositionOnBomb(Coordinate Pos);
    bool isCellEmpty(Coordinate position);

    void generateMap();
    bool eatFood(Snake* snake, Coordinate direct);
    bool collideWithWall(Coordinate nextHead);
    bool collideOther(Coordinate nextHead, Snake* snake);
    bool eatPower(Coordinate nextHead);
    void activatePower(int key);
    void activateDropBomb(Snake* snake, Coordinate nextHead);
    bool eatBomb(Snake* snake, Coordinate direct);
    void deleteBomb(Coordinate nextHead);

    void step(int keyA, int keyB, Sound& gameSound, bool playSound);

};

#endif // GAMEENGINE_H_INCLUDED
