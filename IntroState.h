#pragma once

#include "StateMachine.h"
#include "GameState.h"
#include "Tools.h"
#include "MilkShakeCookie.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

extern MilkShakeCookie milkShakeCookie;

class IntroState {

    private:
        static inline int frame;

    public:

        static void Init() {
            PD::setTASRowMask(0b11111110000000000011);
            Tools::LoadImage("data/milkshak/StartScreen.i8");
            PD::setColor(7, 0);
        };

    static void Update() {
        auto elapsed = StateMachine::GetElapsed();
        if (elapsed > 500 && Tools::AnyKey()) {
            StateMachine::setState < GameState > ();
            AudioManager::playLoading();
        }
        if (elapsed > 10000 || PB::cBtn()) {
            StateMachine::DemoMode = true;
            StateMachine::setState < GameState > ();
        }
    };

    static void Draw() {

        //High Score
        Tools::PrintCentered(110, 2, 7, "HIGH SCORE: ");
        PD::printf("%d", milkShakeCookie.highScore);

        Tools::PrintCentered(110, 120, 7, "User left or right");
        Tools::PrintCentered(110, 130, 7, "to serve the correct");
        Tools::PrintCentered(110, 140, 7, "dish to bunny or cat");

        //Credits
        frame++;
        Tools::PrintCentered(110, 164, ((int)(frame/10))%8, "by @HomineLudens");
    };
};