#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED
#include "SDL_Mixer.h"
class Sound {
private:
    Mix_Music* backgroundMusic;

    Mix_Chunk* eatFoodSound;
    Mix_Chunk* eatPowerSound;
    Mix_Chunk* eatBombSound;
    Mix_Chunk* clickSound;
    Mix_Chunk* dropBombSound;
    Mix_Chunk* endGameSound;
public:
    Sound() {
        backgroundMusic = nullptr;
        eatFoodSound = nullptr;
        eatPowerSound = nullptr;
        eatBombSound = nullptr;
        clickSound = nullptr;
        dropBombSound = nullptr;
        endGameSound = nullptr;
    }
    void destroySound() {
        Mix_FreeMusic(backgroundMusic);
        Mix_FreeChunk(eatFoodSound);
        Mix_FreeChunk(eatPowerSound);
        Mix_FreeChunk(eatBombSound);
        Mix_FreeChunk(clickSound);
        Mix_FreeChunk(dropBombSound);
        Mix_FreeChunk(endGameSound);

        Mix_Quit();
    }

    void loadSound() {
        backgroundMusic = Mix_LoadMUS("Sound/backgroundMusic.mp3");

        eatFoodSound = Mix_LoadWAV("Sound/eatFoodSound.wav");
        eatPowerSound = Mix_LoadWAV("Sound/eatPowerSound.wav");
        eatBombSound = Mix_LoadWAV("Sound/eatBombSound.wav");
        clickSound = Mix_LoadWAV("Sound/clickSound.wav");
        dropBombSound = Mix_LoadWAV("Sound/dropBombSound.wav");
        endGameSound = Mix_LoadWAV("Sound/endGameSound.wav");
    }
    Mix_Music* getBackgroundMusic() {
        return backgroundMusic;
    }
    Mix_Chunk* getEatFoodSound() {
        return eatFoodSound;
    }
    Mix_Chunk* getEatPowerSound() {
        return eatPowerSound;
    }
    Mix_Chunk* getEatBombSound() {
        return eatBombSound;
    }
    Mix_Chunk* getClickSound() {
        return clickSound;
    }
    Mix_Chunk* getDropBombSound() {
        return dropBombSound;
    }
    Mix_Chunk* getEndGameSound() {
        return endGameSound;
    }
};


#endif // SOUND_H_INCLUDED
