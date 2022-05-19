#include "GameEngine.h"
#include <vector>
using namespace std;

GameEngine::GameEngine(int _width, int _height, int _foodNumber) {
    this->width = _width;
    this->height = _height;
    this->map = new Map(width, height);
    this->foodNumber = _foodNumber;

    snakeA = new Snake(3, 1, {1,0});
    snakeB = new Snake(width - 6, height  - 2, {-1,0});

    for (int i = 0; i < 2; i++) {
        snakeA->grow();
        snakeB->grow();
    }

    generateWall();
    generateFood();
    power = nullptr;

    status = Status::RUNNING;
    countStep = 0;
    isAwin = false;
    isBwin = false;
}


int GameEngine::getStatus() const {
    return this->status;
}
int GameEngine::getKey() const {
    return KeyPress::RIGHT;
}
bool GameEngine::isAwinner() {
    return isAwin;
}
bool GameEngine::isBwinner() {
    return isBwin;
}

Coordinate GameEngine::getSnakeDirection(int key) {
    switch (key) {
        case KeyPress::UP:      return {0, -1}; break;
        case KeyPress::DOWN:    return {0, 1}; break;
        case KeyPress::LEFT:    return {-1, 0}; break;
        case KeyPress::RIGHT:   return {1, 0}; break;
    }
}

void GameEngine::generateWall() {
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                GameObject* wall = new GameObject (i, j, Types::WALL);
                walls.push_back(*wall);
            }
}

Coordinate GameEngine::makeNewGameObject() {
    int x = rand() % width;
    int y = rand() % height;
    Coordinate newPos{x, y};

    if (power != nullptr && power->getPosition() == newPos) makeNewGameObject();
    if (isPositionOnSnake(newPos)) makeNewGameObject();
    if (isPositionOnWall(newPos)) makeNewGameObject();
    if (isPositionOnFood(newPos)) makeNewGameObject();
    if (isPositionOnBomb(newPos)) makeNewGameObject();
    return newPos;
}

void GameEngine::generatePower() {
    int x = rand() % width;
    int y = rand() % height;
    Coordinate powerPos{x, y};
    //Power is also a type of food
    if (!isPositionOnSnake(powerPos) && !isPositionOnWall(powerPos) && !isPositionOnFood(powerPos)) {
        power = new Power(powerPos);
        cout << "New Power " << power->getPowerType() << " Position: " << endl;
    } else generatePower();
}

void GameEngine::deletePower() {
    power = nullptr;
    cout << "Deleted Power" << endl;
}

void GameEngine::generateFood() {
    for (int i = 0; i < this->foodNumber; i++)
        makeFood();
}
void GameEngine::makeFood() {
    int x = rand() % width;
    int y = rand() % height;
    Coordinate foodPos{x, y};
    if (power != nullptr) {
        if (power->getPosition() == foodPos) makeFood();
    }
    if (!isPositionOnSnake(foodPos) && !isPositionOnWall(foodPos) && !isPositionOnFood(foodPos)) {
        GameObject* newfood = new GameObject (x, y, Types::FOOD);
        food.push_back(*newfood);
    } else makeFood();
}

void GameEngine::deleteFood(Coordinate nextHead) {
    for (int i = 0; i < food.size();i++)
        if (nextHead == food[i].getPosition()) {
            food.erase(food.begin() + i);
            cout << "Delete Food" << endl;
            break;
        }
}

bool GameEngine::isPositionOnSnake(Coordinate foodPos) {
    for (auto node:snakeA->getNodes())
        if (node.getPosition() + snakeA->getDirection() == foodPos) return true;
    for (auto node:snakeB->getNodes())
        if (node.getPosition() + snakeB->getDirection() == foodPos) return true;
    return false;
}
bool GameEngine::isPositionOnWall(Coordinate Pos) {
    for (auto wall: walls)
        if (Pos == wall.getPosition()) return true;
    return false;
}
bool GameEngine::isPositionOnFood(Coordinate foodPos) {
    for (auto foodPlace: food)
        if (foodPos == foodPlace.getPosition()) return true;
    return false;
}
bool GameEngine::isPositionOnBomb(Coordinate Pos) {
    if (bombs.size() == 0) return false;
    else {
        for (auto bomb:bombs)
            if (bomb.getPosition() == Pos) return true;
        return false;
    }
}
bool GameEngine::isCellEmpty(Coordinate position) {
    if (isPositionOnWall(position)) return false;
    if (isPositionOnSnake(position)) return false;
    if (isPositionOnBomb(position)) return false;
    if (isPositionOnFood(position)) return false;
    if (power != nullptr && power->getPosition() == position) return false;
    return true;
}
void GameEngine::generateMap() {
    //Empty Cells
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            map->setCell(x, y, Types::EMPTY);

    //SnakeA Cells
    for (auto node: snakeA->getNodes())
        map->setCell(node.getPosition().x, node.getPosition().y, node.getSymbol());
    //SnakeB Cells
    for (auto node: snakeB->getNodes())
        map->setCell(node.getPosition().x, node.getPosition().y, node.getSymbol());

    //Wall Cells
    for (auto wall: walls)
        map->setCell(wall.getPosition().x, wall.getPosition().y, Types::WALL);

    //Food Cells
    for (auto foodPlace : food)
        map->setCell(foodPlace.getPosition().x, foodPlace.getPosition().y, Types::FOOD);
    //Power Cells
    if (power != nullptr) {
        map->setCell(power->getPosition().x, power->getPosition().y, Types::POWER);
    }
    //Bomb Cells
    for (auto bomb: bombs)
        map->setCell(bomb.getPosition().x, bomb.getPosition().y, Types::BOMB);
}

bool GameEngine::eatFood(Snake* snake,Coordinate direct) {
    auto nextHead = snake->getHead()->getPosition() + direct;
//    for (auto foodPlace : food)
//        if (nextHead == foodPlace.getPosition()) {
//                return true;
//        }
    if (map->getCell(nextHead) == Types::FOOD) return true;
    return false;
}

bool GameEngine::collideWithWall(Coordinate nextHead) {
    for (auto wall: walls)
        if (wall.getPosition() == nextHead) return true;
    return false;
}

bool GameEngine::collideOther(Coordinate nextHead, Snake* snake) {
    for (auto node: snake->getNodes())
        if (node.getPosition() == nextHead) return true;
    return false;
}

bool GameEngine::eatPower(Coordinate nextHead) {
    return (nextHead == power->getPosition());
}

void GameEngine::activateDropBomb(Snake *snake, Coordinate nextHead) {
    Coordinate position = nextHead + snake->getDirection();

    if (isCellEmpty(position)) {
            GameObject* bomb = new GameObject (position, Types::BOMB);
            bombs.push_back(*bomb);
    }
    Coordinate secondPos = position + Coordinate {0, 1};
    if (isCellEmpty(secondPos) && (secondPos) != nextHead) {
            GameObject* bomb = new GameObject (secondPos, Types::BOMB);
            bombs.push_back(*bomb);
    }
    Coordinate thirdPos = position + Coordinate {0, -1};
    if (isCellEmpty(thirdPos) && (thirdPos) != nextHead) {
            GameObject* bomb = new GameObject (thirdPos, Types::BOMB);
            bombs.push_back(*bomb);
    }
    if (isCellEmpty(position + Coordinate {1, 0}) && (position + Coordinate {1, 0}) != nextHead) {
            GameObject* bomb = new GameObject (position + Coordinate {1, 0}, Types::BOMB);
            bombs.push_back(*bomb);
    }
    if (isCellEmpty(position + Coordinate {-1, 0}) && (position + Coordinate {-1, 0}) != nextHead) {
            GameObject* bomb = new GameObject (position + Coordinate {-1, 0}, Types::BOMB);
            bombs.push_back(*bomb);
    }
    cout << "Activate Drop Bomb" << endl;
}


bool GameEngine::eatBomb(Snake* snake, Coordinate direct) {
    auto nextHead = snake->getHead()->getPosition() + direct;
    for (auto bomb : bombs)
        if (nextHead == bomb.getPosition()) {
                return true;
        }
    return false;
}

void GameEngine::deleteBomb(Coordinate nextHead) {
    for (int i = 0; i < bombs.size(); i++)
        if (nextHead == bombs[i].getPosition()) {
                bombs.erase(bombs.begin() + i);
                break;
        }
}

void GameEngine::step(int keyA, int keyB, Sound& gameSound, bool playSound) {
    //get direction for each snake
    if (keyA != KeyPress::USINGPOWER) {
        Coordinate direction = getSnakeDirection(keyA);
        snakeA->setDirection(direction);
    }
    if (keyB != KeyPress::USINGPOWER) {
        Coordinate direction = getSnakeDirection(keyB);
        snakeB->setDirection(direction);
    }

    auto nextHeadA = snakeA->getHead()->getPosition() + snakeA->getDirection();
    auto nextHeadB = snakeB->getHead()->getPosition() + snakeB->getDirection();

    //check status
    if (snakeA->collideItself()) {status = Status::EXITING; isBwin = true;}
    if (snakeB->collideItself()) {status = Status::EXITING; isAwin = true;}

    if (collideWithWall(nextHeadA) && !collideWithWall(nextHeadB)) {status = Status::EXITING; isAwin = false; isBwin = true;}
    if (collideWithWall(nextHeadB) && !collideWithWall(nextHeadA)) {status = Status::EXITING; isBwin = false; isAwin = true;}

//    if (collideOther(nextHeadA, snakeB)) {status = Status::EXITING; isAwin = false; isBwin = true;}
//    if (collideOther(nextHeadB, snakeA)) {status = Status::EXITING; isBwin = false; isAwin = true;}
//    if (nextHeadA == nextHeadB) {isAwin = false; isBwin = false;}

    if (snakeA->length < 2) {status = Status::EXITING;  isAwin = false;}
    if (snakeB->length < 2) {status = Status::EXITING;  isBwin = false;}

    //if snake has power and uses it, then delete it
    if (snakeA->power != nullptr && keyA == KeyPress::USINGPOWER) {
        if (snakeA->getPower() == PowerType::dropBomb) activateDropBomb(snakeB, nextHeadB);
        snakeA->power = nullptr;
    }
    if (snakeB->power != nullptr && keyB == KeyPress::USINGPOWER) {
        if (snakeB->getPower() == PowerType::dropBomb) activateDropBomb(snakeA, nextHeadA);
        snakeB->power = nullptr;
    }
    //update Power
    countStep++;
    if (countStep % 50 == 0 && power == nullptr) generatePower();
    if (power != nullptr) {
        power->gainTime();
        if (power->isFullTime()) deletePower();
    }

    //eat Bomb
    if (eatBomb(snakeA, snakeA->getDirection())) {
            snakeA->decrease();
            if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatBombSound(), 0);
            deleteBomb(nextHeadA);
       }
    if (eatBomb(snakeB, snakeB->getDirection())) {
            snakeB->decrease();
            if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatBombSound(), 0);
            deleteBomb(nextHeadB);
    }

    //eat Power
    if (power!= nullptr && eatPower(nextHeadA)) {
        cout << "Eat Power" << endl;
        snakeA->setPower(power->getPowerType());
        deletePower();
        if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatPowerSound(), 0);
    }

    if (power!= nullptr && eatPower(nextHeadB)) {
        cout << "Eat Power" << endl;
        snakeB->setPower(power->getPowerType());
        deletePower();
        if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatPowerSound(), 0);
    }


    //eat Food
    if  (eatFood(snakeA, snakeA->getDirection())) {
            deleteFood(nextHeadA);
            makeFood();
            snakeA->grow();
            if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatFoodSound(), 0);
    } else snakeA->move();

    if  (eatFood(snakeB, snakeB->getDirection())) {
            deleteFood(nextHeadB);
            makeFood();
            snakeB->grow();
            if (playSound == true) Mix_PlayChannel(-1, gameSound.getEatFoodSound(), 0);
    } else snakeB->move();
}
