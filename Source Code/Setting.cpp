#include "Setting.h"
#include <fstream>

extern SDL_Renderer *renderer;

void startGame(bool& newGame, Sound& gameSound) {
    drawStartBackground();
    drawHighScoreMenu();
    Mix_PlayMusic(gameSound.getBackgroundMusic(), -1);
    SDL_RenderPresent(renderer);

    SDL_Event e;

    Button playButton;
    playButton.setButtonPosition(200, 300, 250, 100);

    Button helpButton;
    helpButton.setButtonPosition(200, 430, 250, 100);

    Button exitHelpButton;
    exitHelpButton.setButtonPosition(900, 100, 80, 80);

    Button exitButton;
    exitButton.setButtonPosition(200, 590, 250, 100);

    while (!newGame) {

        if (Mix_PausedMusic() == 1)
            {
                Mix_ResumeMusic();
            }
        SDL_PollEvent(&e);

        if (e.type == SDL_QUIT) exit(1);
        SDL_RenderClear(renderer);

        drawStartBackground();

        if (playButton.isMouseIn(e)) {
            drawPlayButton();
            drawHighScoreMenu();
            //if press in play button
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                    newGame = true;
                    Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                    break;
            }
        }

        if (helpButton.isMouseIn(e)) {
            drawHelpButton();
            drawHighScoreMenu();
            //if press in help button
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                bool exitHelp = false;
                while (!exitHelp) {
                    //delete help pic by clear the screen
                    SDL_RenderClear(renderer);
                    //draw help picture
                    drawHelpWindow();
                    SDL_PollEvent(&e);
                    if (e.type == SDL_QUIT) exit(1);
                    if (exitHelpButton.isMouseIn(e)) {
                        if (e.type == SDL_MOUSEBUTTONDOWN)  {
                                exitHelp = true;
                                Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                        }
                    }
                    SDL_RenderPresent(renderer);
                }
            }
        }

        if (exitButton.isMouseIn(e)) {
            drawExitButton();
            drawHighScoreMenu();
            SDL_RenderPresent(renderer);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                    Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                    exit(1);
            }
        }
        SDL_RenderPresent(renderer);
    }
}

void runGame(int width, int height, bool& newGame, Sound& gameSound, bool& playSound) {
    newGame = false;
    bool pause = false;
    //set button
    Button pauseButton;
    pauseButton.setButtonPosition(575, 720, 60, 60);

    Button replayButton;
    replayButton.setButtonPosition(470, 720, 60, 60);

    Button muteButton;
    muteButton.setButtonPosition(680, 720, 60, 60);

    GameEngine* gameEngine = new GameEngine(width, height, 3);
    int status = gameEngine->getStatus();
    gameEngine->generateMap();

    SDL_Event e;
    int keyA = KeyPress::RIGHT;
    int keyB = KeyPress::LEFT;
    srand(time(nullptr));

    render(gameEngine);
    if (playSound == true) drawUnmuteButton();
    else drawMuteButton();
    drawContinueButton();
    drawScoreA(gameEngine->snakeA->getLength());
    drawScoreB(gameEngine->snakeB->getLength());
    if (playSound == true) Mix_PlayMusic(gameSound.getBackgroundMusic(), -1);
    SDL_RenderPresent(renderer);
    //Press any key to play
    waitUntilKeyPressed();

    do {
        if (playSound == false) Mix_PauseMusic();
        if (Mix_PausedMusic() == 1 && playSound == true)
            {
                Mix_ResumeMusic();
            }
        SDL_RenderClear(renderer);
        while (SDL_PollEvent( &e ) != 0) {
            if( e.type == SDL_QUIT ) exit(1);
            else if( e.type == SDL_KEYDOWN ){
                switch( e.key.keysym.sym ){
                    case SDLK_ESCAPE: SDL_Quit(); break;
                    case SDLK_UP: keyB = KeyPress::UP; break;
                    case SDLK_DOWN: keyB = KeyPress::DOWN; break;
                    case SDLK_LEFT: keyB = KeyPress::LEFT; break;
                    case SDLK_RIGHT: keyB = KeyPress::RIGHT; break;
                    case SDLK_SPACE: keyB = KeyPress::USINGPOWER; break;
                    case SDLK_a: keyA = KeyPress::LEFT; break;
                    case SDLK_s: keyA = KeyPress::DOWN; break;
                    case SDLK_d: keyA = KeyPress::RIGHT; break;
                    case SDLK_w: keyA = KeyPress::UP; break;
                    case SDLK_q: keyA = KeyPress::USINGPOWER; break;
                    case SDLK_p: pause = true; break;
                    case SDLK_n: newGame = true; break;
                    default: break;
                }
            } else  if (muteButton.isMouseIn(e)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (playSound == true) playSound = false;
                    else playSound = true;
                    if (playSound == false) Mix_PauseMusic();
                    cout << "Mute by mouse" << endl;
                }
            } else if (pauseButton.isMouseIn(e)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (pause == true) pause = false;
                    else pause = true;
                    cout << "Pause by mouse" << endl;
                }
            } else if (replayButton.isMouseIn(e)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    newGame = true;
                    cout << "New Game by mouse" << endl;
                }
            }
        }
        if (newGame == true) break;
        gameEngine->step(keyA, keyB, gameSound, playSound);
        gameEngine->generateMap();

        status = gameEngine->getStatus();
        if (status == Status::EXITING) break;

        render(gameEngine);

         //if pause
        if (pause == true) {
            cout << "Pause" << endl;
            while (true) {
                render(gameEngine);
                drawContinueButton();
                drawScoreA(gameEngine->snakeA->getLength());
                drawScoreB(gameEngine->snakeB->getLength());
                if (playSound == true) drawUnmuteButton();
                else drawMuteButton();
                SDL_RenderPresent(renderer);
                if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN))
                    if (e.key.keysym.sym == SDLK_p) break;
                if (pauseButton.isMouseIn(e) && e.type == SDL_MOUSEBUTTONDOWN) {
                    break;
                }

                if (replayButton.isMouseIn(e) && e.type == SDL_MOUSEBUTTONDOWN) {
                    newGame = true;
                    break;
                }
                if (muteButton.isMouseIn(e) && e.type == SDL_MOUSEBUTTONDOWN) {
                    if (playSound == true) playSound = false;
                    else playSound = true;
                    if (playSound == false) Mix_PauseMusic();
                }

                SDL_Delay(10);
                SDL_RenderClear(renderer);
            }
            pause = false;
            SDL_RenderClear(renderer);
            render(gameEngine);
            cout << "Continue" << endl;
        }
        drawPauseButton();
        //if mute
        if (playSound == false) {
            cout << "Mute" << endl;
            drawMuteButton();
        }else drawUnmuteButton();

        drawScoreA(gameEngine->snakeA->getLength());
        drawScoreB(gameEngine->snakeB->getLength());
        SDL_RenderPresent(renderer);
        SDL_Delay(55);
    }   while (status == Status::RUNNING);
    //Result
    if (newGame == false) {
        if (playSound == true) Mix_PlayChannel(-1, gameSound.getEndGameSound(), 0);
        else Mix_PauseMusic();
        if (gameEngine->isAwinner() == false && gameEngine->isBwinner() == true) {SDL_Delay(90); drawSnakeBwin(); cout << "B win" << endl;}
        if (gameEngine->isBwinner() == false && gameEngine->isAwinner() == true) {SDL_Delay(90); drawSnakeAwin(); cout << "A win" << endl;}

        if (playSound == true) drawUnmuteButton();
            else drawMuteButton();
        drawContinueButton();
        drawScoreA(gameEngine->snakeA->getLength());
        drawScoreB(gameEngine->snakeB->getLength());

        SDL_RenderPresent(renderer);

        updateNewHighScore(gameEngine->snakeA->getLength(), gameEngine->snakeB->getLength());

        bool quit = false;
        while (!quit) {
            if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN)) {
                if (e.key.keysym.sym == SDLK_n) {newGame = true; break;}
            }
            if ((e.type == SDL_QUIT)) {
                quit = true;
                break;
            }
            if (muteButton.isMouseIn(e)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (playSound == true) playSound = false;
                        else playSound = true;
                    if (playSound == true) Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                    cout << "Mute by mouse" << endl;
                    SDL_RenderClear(renderer);
                    if (gameEngine->isAwinner() == false && gameEngine->isBwinner() == true) {SDL_Delay(50); drawSnakeBwin(); cout << "B win" << endl;}
                    if (gameEngine->isBwinner() == false && gameEngine->isAwinner() == true) {SDL_Delay(50); drawSnakeAwin(); cout << "A win" << endl;}
                    if (playSound == true) drawUnmuteButton();
                        else drawMuteButton();
                    drawContinueButton();
                    drawScoreA(gameEngine->snakeA->getLength());
                    drawScoreB(gameEngine->snakeB->getLength());

                    SDL_RenderPresent(renderer);
                }
            }
            if (replayButton.isMouseIn(e)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    newGame = true;
                    if (playSound == true) Mix_PlayChannel(-1, gameSound.getClickSound(), 0);
                    cout << "New Game by mouse" << endl;
                    break;
                }
            }
            SDL_Delay(5);
        }
    }
    delete gameEngine;
}

int readHighScore() {
    ifstream filein("HighScore.txt");
    int n;
    filein >> n;
    return n;
}

void updateNewHighScore(int scoreA, int scoreB) {
    int highScore = readHighScore();
    if (scoreA > highScore) highScore = scoreA;
    if (scoreB > highScore) highScore = scoreB;
    ofstream fileout("HighScore.txt");
    fileout << highScore;
    fileout.close();
}
