#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "GameObject.h"
#include <chrono>
#include <thread>

using namespace std;
struct Map {
    int width;
    int height;
    int **map;

public:
    Map(int _width, int _height);

    ~Map();

    int getWidth() const;
    int getHeight() const;

    int getCell(int x, int y);
    int getCell(Coordinate position);
    void setCell(int x, int y, int c);

    void print();
};

#endif // MAP_H_INCLUDED
