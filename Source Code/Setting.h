#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include "Renderer.h"
#include "HandleEvent.h"
#include "GameEngine.h"
#include "Sound.h"

void startGame(bool& newGame, Sound& gameSound);
void runGame(int width, int height, bool& newGame, Sound& gameSound, bool& playSound);

int readHighScore();
void updateNewHighScore(int scoreA, int scoreB);
#endif // SETTING_H_INCLUDED
