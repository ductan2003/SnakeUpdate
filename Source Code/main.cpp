#include <iostream>
#include "GameEngine.h"
#include "Setting.h"
using namespace std;

extern SDL_Renderer* renderer;
extern SDL_Window* window;

int main(int argv, char* args[])
{
    int width = 19;
    int height = 15;
    bool newGame = false;
    bool playSound = true;
    init(width, height);
    Sound gameSound;
    gameSound.loadSound();
    loadSnake();
    startGame(newGame, gameSound);
    while (newGame == true) {
        SDL_RenderClear(renderer);
        cout << "Get into new game" << endl;
        runGame(width, height, newGame, gameSound, playSound);
        cout << "End Game" << endl;
    }
    quitImage();
    gameSound.destroySound();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
