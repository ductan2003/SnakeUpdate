#ifndef HANDLEEVENT_H_INCLUDED
#define HANDLEEVENT_H_INCLUDED
#include "SDL.h"

class Button {
    SDL_Rect buttonPosition;
public:
    Button() {
        buttonPosition.x = 0;
        buttonPosition.y = 0;
    }
    //~Button();

    void setButtonPosition(int x, int y, int w, int h) {
        buttonPosition.x = x;
        buttonPosition.y = y;
        buttonPosition.w = w;
        buttonPosition.h = h;
    }

    SDL_Rect getRect() {
        return buttonPosition;
    }

    bool isMouseIn(SDL_Event e) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX < buttonPosition.x) return false;
        if (mouseY < buttonPosition.y) return false;
        if (mouseX > buttonPosition.x + buttonPosition.w) return false;
        if (mouseY > buttonPosition.y + buttonPosition.h) return false;
        return true;
    }
};
#endif // HANDLEEVENT_H_INCLUDED
