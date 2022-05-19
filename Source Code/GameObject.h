#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include <iostream>
using namespace std;

enum Types {
    HEAD, TAIL, BODY, WALL, EMPTY, FOOD, POWER, BOMB
};

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coordinate &other) const {
        return x != other.x || y != other.y;
    }

    Coordinate operator+(const Coordinate &other) const {
        return {x + other.x, y + other.y};
    }

    Coordinate operator-(const Coordinate &other) const {
        return {x - other.x, y - other.y};
    }

    void print() const {
        cout << x << " " << y << endl;
    }
};

class GameObject {
    Coordinate position;
    int symbol;
    Coordinate direction;

public:
    GameObject(Coordinate position, int symbol) : position(position), symbol(symbol) {
//        this->direction = nullptr;
    }
    GameObject(int x,int y, int symbol) : position(Coordinate{x,y}), symbol(symbol) {
//        this->direction = nullptr;
    }

    Coordinate getPosition() const {
        return position;
    }

    int getSymbol() const {
        return symbol;
    }

    Coordinate getDirection() {
        return direction;
    }

    void setDirection(Coordinate direct) {
        this->direction = direct;
    }
    void setPosition(Coordinate pos) {
        this->position = pos;
    }

    void setSymbol(int sym) {
        this->symbol = sym;
    }

    bool operator==(const GameObject &other) const {
        return position == other.position && symbol == other.symbol;
    }

    bool isCollision(const GameObject &other) const {
        return position == other.position;
    }

    void move(Coordinate distance) {
        position = position + distance;
    }

    void moveTo(Coordinate position) {
        this->position = position;
    }

};


#endif // GAMEOBJECT_H_INCLUDED
