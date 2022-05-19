#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "GameObject.h"
#include "Power.h"
#include <vector>

struct Snake {
    std::vector<GameObject> nodes;
    Coordinate direction;
    int* power;
    int length;

public:
    Snake(int x, int y, Coordinate direct);

    ~Snake() = default;

    int getLength() const;
    Coordinate getDirection() const ;
    GameObject* getHead();
    GameObject* getTail();
    std::vector<GameObject> getNodes();
    int getPower();

    void setDirection(Coordinate direct);
    void setPower(int powerName);
    void deletePower();

    void move();
    void grow();
    void decrease();

    bool collideItself();

    void snakePrint();
};

#endif // SNAKE_H_INCLUDED
