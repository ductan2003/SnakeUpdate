#include "Renderer.h"
#include "Setting.h"

const int xMove = 230;
const int yMove = 110;
const int TileSize = 40;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture* snakeHeadA; SDL_Texture* snakeHeadB;
SDL_Texture* snakeBodyA[2]; SDL_Texture* snakeBodyB[2];
SDL_Texture* snakeTailA; SDL_Texture* snakeTailB;

enum bodyType {
    CORNER, NORMAL
};

void init(int width, int height) {
    window = SDL_CreateWindow("Snake Update", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
		cout << "fail" << endl;
	}
}

void quitImage() {
    SDL_DestroyTexture(snakeHeadA);
    snakeHeadA = NULL;
    SDL_DestroyTexture(snakeHeadB);
    snakeHeadB = NULL;
    SDL_DestroyTexture(snakeTailA);
    snakeTailA = NULL;
    SDL_DestroyTexture(snakeTailB);
    snakeTailB = NULL;
    SDL_DestroyTexture(snakeBodyA[0]);
    snakeBodyA[0] = NULL;
    SDL_DestroyTexture(snakeBodyA[1]);
    snakeBodyA[1] = NULL;
    SDL_DestroyTexture(snakeBodyB[0]);
    snakeBodyB[0] = NULL;
    SDL_DestroyTexture(snakeBodyB[1]);
    snakeBodyB[1] = NULL;
}
SDL_Texture* loadTexture(const std::string &str) {
    SDL_Surface* surface = IMG_Load(str.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}


void drawStartBackground() {
    SDL_Texture* startBackground = loadTexture("Image/Background/StartMenu.png");
    SDL_RenderCopy(renderer, startBackground, nullptr, nullptr);
    drawHighScoreMenu();
    SDL_DestroyTexture(startBackground);
}
void drawPlayButton() {
    SDL_Texture* playButton = loadTexture("Image/Background/Play.png");
    SDL_RenderCopy(renderer, playButton, nullptr, nullptr);
    SDL_DestroyTexture(playButton);
}
void drawHelpButton() {
    SDL_Texture* helpButton = loadTexture("Image/Background/help.png");
    SDL_RenderCopy(renderer, helpButton, nullptr, nullptr);
    SDL_DestroyTexture(helpButton);
}
void drawExitButton() {
    SDL_Texture* exitButton = loadTexture("Image/Background/exit.png");
    SDL_RenderCopy(renderer, exitButton, nullptr, nullptr);
    SDL_DestroyTexture(exitButton);
}
void drawHelpWindow() {
    SDL_Texture* helpWindow = loadTexture("Image/Background/HelpWindow.png");
    SDL_RenderCopy(renderer, helpWindow, nullptr, nullptr);
    SDL_DestroyTexture(helpWindow);
}

void drawPlayBackground() {
    SDL_Texture* playBackground = loadTexture("Image/Background/PlayBackground.png");
    SDL_RenderCopy(renderer, playBackground, nullptr, nullptr);
    SDL_DestroyTexture(playBackground);
}
void drawMuteButton() {
    SDL_Texture* mute = loadTexture("Image/Button/Mute.png");
    SDL_Rect rect;
    rect.x = 680;
    rect.y = 720;
    rect.h = 60;
    rect.w = 60;
    SDL_RenderCopy(renderer, mute, nullptr, &rect);
    SDL_DestroyTexture(mute);
}
void drawUnmuteButton() {
    SDL_Texture* Unmute = loadTexture("Image/Button/Unmute.png");
    SDL_Rect rect;
    rect.x = 680;
    rect.y = 720;
    rect.h = 60;
    rect.w = 60;
    SDL_RenderCopy(renderer, Unmute, nullptr, &rect);
    SDL_DestroyTexture(Unmute);
}
void drawPauseButton() {
    SDL_Texture* pause = loadTexture("Image/Button/Pause.png");
    SDL_Rect rect;
    rect.x = 575;
    rect.y = 720;
    rect.h = 60;
    rect.w = 60;
    SDL_RenderCopy(renderer, pause, nullptr, &rect);
    SDL_DestroyTexture(pause);
}
void drawContinueButton() {
    SDL_Texture* continuebutton = loadTexture("Image/Button/Continue.png");
    SDL_Rect rect;
    rect.x = 575;
    rect.y = 720;
    rect.h = 60;
    rect.w = 60;
    SDL_RenderCopy(renderer, continuebutton, nullptr, &rect);
    SDL_DestroyTexture(continuebutton);
}
void drawSnakeAwin() {
    SDL_Texture* result = loadTexture("Image/Background/SnakeAwin.png");
    SDL_RenderCopy(renderer, result, nullptr, nullptr);
    SDL_DestroyTexture(result);
}
void drawSnakeBwin() {
    SDL_Texture* result = loadTexture("Image/Background/SnakeBwin.png");
    SDL_RenderCopy(renderer, result, nullptr, nullptr);
    SDL_DestroyTexture(result);
}

void drawFood(int xPos, int yPos) {
    SDL_Texture* food = loadTexture("Image/Food/apple.png");
    SDL_Rect foodRect;
    foodRect.x = xPos * TileSize + xMove;
    foodRect.y = yPos * TileSize + yMove;
    foodRect.h = TileSize;
    foodRect.w = TileSize;
    SDL_RenderCopy(renderer, food, nullptr, &foodRect);
    SDL_DestroyTexture(food);
}
void drawPower(int xPos, int yPos) {
    SDL_Texture* power = loadTexture("Image/Power/Power.png");
    SDL_Rect powerRect;
    powerRect.x = xPos * TileSize + xMove;
    powerRect.y = yPos * TileSize + yMove;
    powerRect.h = TileSize;
    powerRect.w = TileSize;
    SDL_RenderCopy(renderer, power, nullptr, &powerRect);
    SDL_DestroyTexture(power);
}
void drawBomb(int xPos, int yPos) {
    SDL_Texture* bomb = loadTexture("Image/Bomb/bomb3.png");
    SDL_Rect bombRect;
    bombRect.x = xPos * TileSize + xMove;
    bombRect.y = yPos * TileSize + yMove;
    bombRect.h = TileSize;
    bombRect.w = TileSize;
    SDL_RenderCopy(renderer, bomb, nullptr, &bombRect);
    SDL_DestroyTexture(bomb);
}

void loadSnake() {
    snakeHeadA = loadTexture("Image/Snake/Head/HeadA.png");
    snakeHeadB = loadTexture("Image/Snake/Head/HeadB.png");

    snakeBodyA[bodyType::NORMAL] = loadTexture("Image/Snake/Body/NormalA.png");
    snakeBodyA[bodyType::CORNER] = loadTexture("Image/Snake/Body/CornerA.png");
    snakeBodyB[bodyType::NORMAL] = loadTexture("Image/Snake/Body/NormalB.png");
    snakeBodyB[bodyType::CORNER] = loadTexture("Image/Snake/Body/CornerB.png");

    snakeTailA = loadTexture("Image/Snake/Tail/TailA.png");
    snakeTailB = loadTexture("Image/Snake/Tail/TailB.png");

    cout << "Load Success" << endl;
}

void drawSnakeHead(GameObject head, bool isA) {
    SDL_Rect headRect;
    headRect.x = head.getPosition().x * TileSize + xMove;
    headRect.y = head.getPosition().y * TileSize + yMove;
    headRect.w = TileSize;
    headRect.h = TileSize;

    double degrees = 0;
    Coordinate direct = head.getDirection();
    if (direct == Coordinate{0, -1})  degrees = 0;
    if (direct == Coordinate{0, 1})  degrees = 180;
    if (direct == Coordinate{1, 0})  degrees = 90;
    if (direct == Coordinate{-1, 0})  degrees = -90;

    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    if (isA == true) SDL_RenderCopyEx(renderer, snakeHeadA, nullptr, &headRect, degrees, nullptr, flipType);
    if (isA == false) SDL_RenderCopyEx(renderer, snakeHeadB, nullptr, &headRect, degrees, nullptr, flipType);
}

void drawSnakeBody(GameObject pre, GameObject current, GameObject next, bool isA) {
    SDL_Rect bodyRect;
    bodyRect.x = current.getPosition().x * TileSize + xMove;
    bodyRect.y = current.getPosition().y * TileSize + yMove;
    bodyRect.w = TileSize;
    bodyRect.h = TileSize;

    double degrees = 0;
    Coordinate preDirect = pre.getDirection();
    Coordinate Direct = current.getDirection();
    Coordinate nextDirect = next.getDirection();

    if (preDirect == Coordinate {0, 1} && Direct == Coordinate {0, 1}) degrees = 90;
    if (preDirect == Coordinate {0, -1} && Direct == Coordinate {0, -1}) degrees = 90;
//    if (preDirect == Coordinate {-1, 0} && Direct == Coordinate {-1, 0}) degrees = 0;
//    if (preDirect == Coordinate {1, 0} && Direct == Coordinate {1, 0}) degrees = 0;


    if (preDirect == Coordinate {0, 1} && Direct == Coordinate {-1, 0}) degrees = -90;
    if (preDirect == Coordinate {0, - 1} && Direct == Coordinate {1, 0}) degrees = 90;
    if (preDirect == Coordinate {0, - 1} && Direct == Coordinate {-1, 0}) degrees = 180; // done
    if (preDirect == Coordinate {1, 0} && Direct == Coordinate {0, -1}) degrees = -90;
    if (preDirect == Coordinate {1, 0} && Direct == Coordinate {0, 1}) degrees = 180; //done
    if (preDirect == Coordinate {-1, 0} && Direct == Coordinate {0, 1}) degrees = 90;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    if (isA) {
        if (preDirect == Direct)
            SDL_RenderCopyEx(renderer, snakeBodyA[bodyType::NORMAL], nullptr, &bodyRect, degrees
                             , nullptr, flipType);
        else SDL_RenderCopyEx(renderer, snakeBodyA[bodyType::CORNER], nullptr, &bodyRect, degrees
                             , nullptr, flipType);
    }
    if (!isA) {
        if (preDirect == Direct)
            SDL_RenderCopyEx(renderer, snakeBodyB[bodyType::NORMAL], nullptr, &bodyRect, degrees
                             , nullptr, flipType);
        else SDL_RenderCopyEx(renderer, snakeBodyB[bodyType::CORNER], nullptr, &bodyRect, degrees
                             , nullptr, flipType);
    }

}

void drawSnakeTail(GameObject tail, bool isA) {
    SDL_Rect tailRect;
    tailRect.x = tail.getPosition().x * TileSize + xMove;
    tailRect.y = tail.getPosition().y * TileSize + yMove;
    tailRect.w = TileSize;
    tailRect.h = TileSize;

    double degrees = 0;
    Coordinate direct = tail.getDirection();
    if (direct == Coordinate{0, -1})  degrees = 0;
    if (direct == Coordinate{0, 1})  degrees = 180;
    if (direct == Coordinate{1, 0})  degrees = 90;
    if (direct == Coordinate{-1, 0})  degrees = -90;

    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    if (isA == true) SDL_RenderCopyEx(renderer, snakeTailA, nullptr, &tailRect, degrees, nullptr, flipType);
    if (isA == false) SDL_RenderCopyEx(renderer, snakeTailB, nullptr, &tailRect, degrees, nullptr, flipType);
}

void drawScoreA(int score) {
    SDL_Texture* number = loadTexture("Image/Background/Number.png");
    SDL_Rect numRect[10];
    for (int i = 0; i < 10; i++) {
        numRect[i].x = i * 20;
        numRect[i].y = 0;
        numRect[i].h = 20;
        numRect[i].w = 20;
    }

    SDL_Rect firstNum;
    firstNum.x = 50;
    firstNum.y = 400;
    firstNum.h = 80;
    firstNum.w = 80;

    SDL_Rect secondNum;
    secondNum.x = 130;
    secondNum.y = 400;
    secondNum.h = 80;
    secondNum.w = 80;

    SDL_RenderCopy(renderer, number, &numRect[score / 10], &firstNum);
    SDL_RenderCopy(renderer, number, &numRect[score % 10], &secondNum);
}

void drawScoreB(int score) {
    SDL_Texture* number = loadTexture("Image/Background/Number.png");
    SDL_Rect numRect[10];
    for (int i = 0; i < 10; i++) {
        numRect[i].x = i * 20;
        numRect[i].y = 0;
        numRect[i].h = 20;
        numRect[i].w = 20;
    }

    SDL_Rect firstNum;
    firstNum.x = 1000;
    firstNum.y = 400;
    firstNum.h = 80;
    firstNum.w = 80;

    SDL_Rect secondNum;
    secondNum.x = 1080;
    secondNum.y = 400;
    secondNum.h = 80;
    secondNum.w = 80;

    SDL_RenderCopy(renderer, number, &numRect[score / 10], &firstNum);
    SDL_RenderCopy(renderer, number, &numRect[score % 10], &secondNum);
}

void drawHighScoreMenu() {
    int score = readHighScore();

    SDL_Texture* number = loadTexture("Image/Background/Number.png");
    SDL_Rect numRect[10];
    for (int i = 0; i < 10; i++) {
        numRect[i].x = i * 20;
        numRect[i].y = 0;
        numRect[i].h = 20;
        numRect[i].w = 20;
    }

    SDL_Rect firstNum;
    firstNum.x = 625;
    firstNum.y = 380;
    firstNum.h = 80;
    firstNum.w = 80;

    SDL_Rect secondNum;
    secondNum.x = 705;
    secondNum.y = 380;
    secondNum.h = 80;
    secondNum.w = 80;

    SDL_RenderCopy(renderer, number, &numRect[score / 10], &firstNum);
    SDL_RenderCopy(renderer, number, &numRect[score % 10], &secondNum);
}

void render(GameEngine* gameEngine) {
    drawPlayBackground();
    Map* rendermap = gameEngine->map;
    for (int y = 0; y < rendermap->getHeight(); y++) {
        for (int x = 0; x < rendermap->getWidth(); x++) {
            if (rendermap->getCell(x, y) == Types::FOOD)     drawFood(x, y);
            if (rendermap->getCell(x, y) == Types::POWER)    drawPower(x, y);
            if (rendermap->getCell(x, y) == Types::BOMB)     drawBomb(x, y);
        }
    }
    //render SnakeA
    std::vector<GameObject> NodeA = gameEngine->snakeA->getNodes();
    for (int i = 0; i < NodeA.size(); i++) {
        if (NodeA[i].getSymbol() == Types::HEAD) drawSnakeHead(NodeA[i], true);
        if (NodeA[i].getSymbol() == Types::BODY) drawSnakeBody(NodeA[i + 1], NodeA[i], NodeA[i - 1], true);
        if (NodeA[i].getSymbol() == Types::TAIL) drawSnakeTail(NodeA[i], true);
    }

    //render SnakeB
    std::vector<GameObject> NodeB = gameEngine->snakeB->getNodes();
    for (int i = 0; i < NodeB.size(); i++) {
        if (NodeB[i].getSymbol() == Types::HEAD) drawSnakeHead(NodeB[i], false);
        if (NodeB[i].getSymbol() == Types::BODY) drawSnakeBody(NodeB[i + 1], NodeB[i], NodeB[i - 1], false);
        if (NodeB[i].getSymbol() == Types::TAIL) drawSnakeTail(NodeB[i], false);
    }
}
