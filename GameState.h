#pragma once

#include "StateMachine.h"
#include "EndState.h"
#include "SpritesManager.h"
#include "AudioManager.h"
#include "MilkShakeCookie.h"
#include "Tools.h"
#include <LibSchedule>
#include <LibLOG>

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

constexpr int FOOD_FOR_LEVELUP = 3;
constexpr int START_LIFES = 3;
constexpr int START_TIME = 900; //x.xx seconds
constexpr int FOOD_Y_REACH = 55;

extern MilkShakeCookie milkShakeCookie;

class IntroState;

class GameState {

    enum States {
        Initialize,
        Eating,
        Loading,
        Mixing,
        Falling,
        Waiting,
        MovingLeft,
        MovingRight,
        Eaten,
        GameOver,
        GameOverCat,
        GameOverBunny
    };

    private:

        static inline States state = States::Initialize;
    static inline SpritesManager::FoodType foodType;
    static inline int msState = PC::getTime();
    static inline int foodX = 0;
    static inline int foodY = 0;

    static inline int foodRotation;
    static inline int catCounter = 0;
    static inline int bunnyCounter = 0;
    static inline bool finalStageCat;
    static inline bool finalStageBunny;
    static inline bool flip;

    static inline int timerGame;
    static inline int livesGame;
    static inline int scoreGame;


    static int ElapsedMs() {
        return PC::getTime() - msState;
    };

    static void ChangeState(States newState) {
        msState = PC::getTime();
        state = newState;
        //LOG("state", newState, "\n");
    };

    static void TickTimer() {
        if (state != Loading && state != GameOver && state != GameOverBunny && state != GameOverCat)
            if (timerGame > 0)
                timerGame--;
            else
                timerGame = 0;
    };

    static void UpdateState() {
        switch (state) {

            case Initialize:
                scoreGame = 0;
                livesGame = START_LIFES;
                timerGame = START_TIME;
                ChangeState(Loading);
                break;

            case Eating:
                foodX = 0;
                foodY = 0;
                if (SpritesManager::catSprite.animEnd && SpritesManager::bunnySprite.animEnd) //  ElapsedMs() > 600) {
                {
                    //Stop animations
                    SpritesManager::PlayCatAnimation(SpritesManager::AnimType::Idle);
                    SpritesManager::PlayBunnyAnimation(SpritesManager::AnimType::Idle);

                    if (bunnyCounter >= FOOD_FOR_LEVELUP || (SpritesManager::bunnyLevel >= 5 && bunnyCounter > 0)) {
                        bunnyCounter = 0;
                        SpritesManager::bunnyLevel++;
                        SpritesManager::LoadBunny(SpritesManager::bunnyLevel);
                        AudioManager::playLoading();
                    }
                    if (catCounter >= FOOD_FOR_LEVELUP || (SpritesManager::catLevel >= 5 && catCounter > 0)) {
                        catCounter = 0;
                        SpritesManager::catLevel++;
                        SpritesManager::LoadCat(SpritesManager::catLevel);
                        AudioManager::playLoading();
                    }
                    ChangeState(Loading);
                }
                break;

            case Loading:
                if (!SpritesManager::loadingCat && !SpritesManager::loadingBunny) {
                    foodRotation += random(1000);
                    ChangeState(Mixing);
                }
                break;

            case Mixing:
                foodX = 0;
                foodY = 0;
                if (ElapsedMs() > 500) {
                    ChangeState(Falling);
                    SpritesManager::PlayCatAnimation(SpritesManager::AnimType::Idle);
                    SpritesManager::PlayBunnyAnimation(SpritesManager::AnimType::Idle);
                }
                break;

            case Falling:
                foodY += 5;
                if (foodY > FOOD_Y_REACH)
                    ChangeState(Waiting);
                break;

            case Waiting:
                if (StateMachine::DemoMode) {
                    if (ElapsedMs() > 250) {
                        if (random(100) > 50)
                            ChangeState(MovingLeft);
                        else
                            ChangeState(MovingRight);
                    }
                } else {
                    if (PB::leftBtn)
                        ChangeState(MovingLeft);
                    if (PB::rightBtn())
                        ChangeState(MovingRight);
                }
                break;

            case MovingLeft:

                if (PB::leftBtn() || StateMachine::DemoMode || finalStageBunny)
                    foodX -= finalStageBunny ? 2 : 5;
                else if (PB::rightBtn())
                    ChangeState(MovingRight);
                else if (foodX < 0)
                    foodX += finalStageBunny ? 2 : 5;

                if (foodX < -30) {
                    if (foodType == SpritesManager::FoodType::Pancake) {
                        SpritesManager::PlayBunnyAnimation(SpritesManager::AnimType::Good);
                        AudioManager::playGood();
                        bunnyCounter++;
                        scoreGame++;
                    } else {
                        SpritesManager::PlayBunnyAnimation(SpritesManager::AnimType::Bad);
                        AudioManager::playBad();
                        livesGame--;
                    }
                    foodType = SpritesManager::FoodType::None;
                    ChangeState(Eating);
                }
                break;

            case MovingRight:

                if (PB::rightBtn() || StateMachine::DemoMode || finalStageCat)
                    foodX += finalStageCat ? 2 : 5;
                else if (PB::leftBtn())
                    ChangeState(MovingLeft);
                else if (foodX > 0)
                    foodX -= finalStageCat ? 2 : 5;

                if (foodX > 30) {
                    if (foodType == SpritesManager::FoodType::Milkshake) {
                        SpritesManager::PlayCatAnimation(SpritesManager::AnimType::Good);
                        AudioManager::playGood();
                        catCounter++;
                        scoreGame++;
                    } else {
                        SpritesManager::PlayCatAnimation(SpritesManager::AnimType::Bad);
                        AudioManager::playBad();
                        livesGame--;
                    }
                    foodType = SpritesManager::FoodType::None;
                    ChangeState(Eating);
                }
                break;

            case GameOver:
                if (ElapsedMs() > 1000) {
                    //---------------------------------------
                    EndState::EndType = EndState::Timeout;
                    StateMachine::setState < EndState > ();
                    AudioManager::playGameOver();
                    //---------------------------------------
                }
                break;

            case GameOverCat:
                if (ElapsedMs() > 4000) {
                    //---------------------------------------
                    EndState::EndType = EndState::BadCat;
                    StateMachine::setState < EndState > ();
                    AudioManager::playGameOverFull();
                    //---------------------------------------
                }
                break;

            case GameOverBunny:
                if (ElapsedMs() > 4000) {
                    //---------------------------------------
                    EndState::EndType = EndState::BadBunny;
                    StateMachine::setState < EndState > ();
                    AudioManager::playGameOverFull();
                    //---------------------------------------
                }
                break;
        }
    };

    public:
        static void Init() {
            PD::setTASRowMask(0b11111111111111111111);

            SpritesManager::LoadBunny(0);
            SpritesManager::LoadCat(0);
            ChangeState(Initialize);

            //Schedule::cancel<0>();
            Schedule::repeat < 0 > (100, TickTimer);
            //--
            milkShakeCookie.games++;
            milkShakeCookie.saveCookie();
        };

    static void Update() {
        if (StateMachine::DemoMode && Tools::AnyKey()) {
            StateMachine::DemoMode = false;
            StateMachine::setState < IntroState > ();
        }

        //Check final stage condition
        finalStageBunny = (SpritesManager::bunnyLevel >= 5);
        finalStageCat = (SpritesManager::catLevel >= 5);

        if (state == Mixing || state == Falling) {
            foodRotation += (FOOD_Y_REACH-foodY);
            foodType = (SpritesManager::FoodType)(1 + ((int)(foodRotation/200) % 2));

            //Force food type at final stage
            if (finalStageBunny)
                foodType = SpritesManager::FoodType::Pancake;
            if (finalStageCat)
                foodType = SpritesManager::FoodType::Milkshake;

            //----------------------------------------------------------------
            //foodType = SpritesManager::FoodType::Milkshake; //Test purpose only
            //----------------------------------------------------------------
        }

        //Game over conditions
        if (state != Initialize &&
            state != GameOver &&
            state != GameOverCat &&
            state != GameOverBunny &&
            (livesGame <= 0 || timerGame <= 0)) {
            ChangeState(GameOver);
        }

        if (SpritesManager::catLevel > 5 && state != GameOverCat) {
            scoreGame += (timerGame / 20) + (livesGame * 2);
            ChangeState(GameOverCat);
        }

        if (SpritesManager::bunnyLevel > 5 && state != GameOverBunny) {
            scoreGame += (timerGame / 20) + (livesGame * 2);
            ChangeState(GameOverBunny);
        }

        //Save high score
        if (scoreGame > milkShakeCookie.highScore) {
            milkShakeCookie.highScore = scoreGame;
            milkShakeCookie.saveCookie();
        }
        EndState::FinalScore = scoreGame;

        //---
        UpdateState();
    };

    static void Draw() {
        SpritesManager::DrawStage();

        if (StateMachine::DemoMode) {
            auto ms = PC::getTime();
            auto c1 = 80 + (ms / 100) % 16;
            PD::setColor(c1, 15);
            Tools::PrintCentered(110, 80, c1, "DEMO MODE");
            Tools::PrintCentered(110, 90, c1, "press any");
            Tools::PrintCentered(110, 100, c1, "to play");
        }

        if (SpritesManager::loadingBunny)
            SpritesManager::DrawDust(50, 90, 30, true);
        else
            SpritesManager::bunnySprite.draw(0, 74, false, false);
        if (state == GameOverBunny)
            SpritesManager::DrawDust(50, 90, 50, false, true, false); //draw food also

        if (SpritesManager::loadingCat)
            SpritesManager::DrawDust(150, 90, 30, true);
        else
            SpritesManager::catSprite.draw(116, 74, false, false);
        if (state == GameOverCat)
            SpritesManager::DrawDust(150, 90, 50, false, false, true); //draw food also

        if (!SpritesManager::loadingBunny && !SpritesManager::loadingCat)
            SpritesManager::DrawFood(110 + foodX, 65 + foodY, foodType);

        SpritesManager::DrawGameGui(timerGame, START_TIME, livesGame, scoreGame);
    };

};