#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

#include "GameObject.h"
#include "Map.h"

enum PowerType {
    gold, dropBomb
};

class Power {
    GameObject* power;
    int countTime;
    int timeAppear = 30;
    int powerType;

public:
    Power(Coordinate position) {
        power = new GameObject (position, Types::POWER);
        countTime = 0;
        powerType = PowerType::dropBomb;
    }
    ~Power() = default;

    void destroyPower() {
        delete power;
    }

    Coordinate getPosition() {
        return power->getPosition();
    }
    int getCountTime() {
        return countTime;
    }

    int getTimeAppear() {
        return timeAppear;
    }

    int getPowerType() {
        return powerType;
    }
    void gainTime() {
        countTime++;
    }

    bool isFullTime() {
        return timeAppear == countTime;
    }
    void setPosition(Coordinate pos) {
        power->setPosition(pos);
    }
};


#endif // POWER_H_INCLUDED
