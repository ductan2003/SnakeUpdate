#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "string"
#include "GameEngine.h"

void init(int width, int height);
void quitImage();

SDL_Texture* loadTexture(const std::string &str);
void waitUntilKeyPressed();

void drawStartBackground();
void drawPlayButton();
void drawHelpButton();
void drawExitButton();
void drawHelpWindow();

void drawPlayBackground();

void drawMuteButton();
void drawUnmuteButton();
void drawPauseButton();
void drawContinueButton();

void drawSnakeAwin();
void drawSnakeBwin();

void drawFood(int xPos, int yPos);
void drawPower(int xPos, int yPos);
void drawBomb(int xPos, int yPos);
void loadSnake();
void drawSnakeHead(GameObject head, bool isA);
void drawSnakeBody(GameObject pre, GameObject current, GameObject next, bool isA);
void drawSnakeTail(GameObject tail, bool isA);

void drawScoreA(int score);
void drawScoreB(int score);
void drawHighScoreMenu();

void render(GameEngine* gameEngine);

#endif // RENDERER_H_INCLUDED
