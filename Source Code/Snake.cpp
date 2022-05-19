#include "Snake.h"

Snake::Snake(int x, int y, Coordinate direct) {
    this->direction = direct;
    auto head = new GameObject (x, y, Types::HEAD);
    auto tailPos = head->getPosition() - direction;
    auto tail = new GameObject (tailPos, Types::TAIL);
    nodes.push_back(*head);
    nodes.push_back(*tail);
    nodes[0].setDirection(direct);
    nodes[1].setDirection(direct);
    length = nodes.size();
    power = nullptr;

}

int Snake::getLength() const {
    return nodes.size();
}

Coordinate Snake::getDirection() const {
    return direction;
}

GameObject* Snake::getHead() {
    return &nodes[0];
}

GameObject* Snake::getTail() {
    return &nodes[nodes.size() - 1];
}

std::vector<GameObject> Snake::getNodes() {
    return nodes;
}

int Snake::getPower() {
    return *power;
}

void Snake::setDirection(Coordinate direct) {
    if (this->direction.x * direct.x < 0 || this->direction.y * direct.y < 0)
        return;
    this->direction = direct;
    nodes[0].setDirection(direct);
}

void Snake::setPower(int powerName) {
    power = new int (powerName);
}

void Snake::deletePower() {
    power = nullptr;
}
void Snake::move() {
    auto nextHead = nodes[0].getPosition() + direction;
    for (int i = nodes.size() - 1; i > 0; i--) {
        nodes[i].moveTo(nodes[i - 1].getPosition());
        nodes[i].setDirection(nodes[i - 1].getDirection());
    }
    nodes[0].setPosition(nextHead);
    nodes[0].setDirection(direction);
}

void Snake::grow() {
    auto headPosition = nodes[0].getPosition() + direction;
    nodes[0].setSymbol(Types::BODY);
    nodes.insert(nodes.begin(), GameObject(headPosition, Types::HEAD));
    nodes[0].setDirection(direction);
}

void Snake::decrease() {
    nodes[nodes.size() - 2].setSymbol(Types::TAIL);
    nodes.pop_back();
}

bool Snake::collideItself() {
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (nodes[0].getPosition() + direction == nodes[i].getPosition())
            return true;
    }
    if (nodes[0].getPosition() + direction == nodes[nodes.size() - 1].getPosition() + nodes[nodes.size() - 1].getDirection())
        return true;
    return false;
}

void Snake::snakePrint() {
    for (auto node: nodes)
        node.getDirection().print();
}
