#include "Map.h"

Map::Map(int _width, int _height) {
    this->width = _width;
    this->height = _height;
    this->map = new int* [height];
    for (int y = 0; y < height; y++) {
        this->map[y] = new int [width];
        for (int x = 0; x < width; x++)
            this->map[y][x] = Types::EMPTY;
    }
}

Map::~Map() {
    for (int i = 0; i < this->width; i++)
        delete[] this->map[i];
    delete[] this->map;
}

int Map::getWidth() const {
    return this->width;
}

int Map::getHeight() const {
    return this->height;
}

int Map::getCell(int x, int y) {
    return this->map[y][x];
}

int Map::getCell(Coordinate position) {
    return this->map[position.y][position.x];
}

void Map::setCell(int x, int y, int c) {
    this->map[y][x] = c;
}

void Map::print() {
    //use for console screen
    for (int i = 0; i < 20; i++) cout << endl;
    for (int y = 0; y < height; y++) {
        cout << y % 10;
        for (int x = 0; x < width; x++) {
            if (this->getCell(x, y) == Types::EMPTY) cout << "  ";
            if (this->getCell(x, y) == Types::HEAD) cout << "H ";
            if (this->getCell(x, y) == Types::TAIL) cout << "T ";
            if (this->getCell(x, y) == Types::BODY) cout << "B ";
            if (this->getCell(x, y) == Types::FOOD) cout << "F ";
            if (this->getCell(x, y) == Types::WALL) cout << "W ";
            if (this->getCell(x, y) == Types::POWER) cout << "P ";
            if (this->getCell(x, y) == Types::BOMB) cout << "X ";

        }
        cout << endl;
    }
//    std::this_thread::sleep_for(std::chrono::milliseconds(400));
}
