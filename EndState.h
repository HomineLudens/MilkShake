#pragma once

#include "StateMachine.h"
#include "IntroState.h"
#include "Tools.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

extern MilkShakeCookie milkShakeCookie;

class IntroState;

class EndState {

    public:
        enum Ends {
            Timeout,
            BadBunny,
            BadCat,
        };

    static inline Ends EndType;
    static inline int FinalScore;

    static void Init() {
        PD::setTASRowMask(0b11110000000000001111);

        if (EndType == Timeout)
            Tools::LoadImage("data/milkshak/GameOverScreen.i8");
        if (EndType == BadBunny)
            Tools::LoadImage("data/milkshak/EndBunnyScreen.i8");
        if (EndType == BadCat)
            Tools::LoadImage("data/milkshak/EndCatScreen.i8");

    };

    static void Update() {
        auto elapsed = StateMachine::GetElapsed();
        if (elapsed > 1000 && (Tools::AnyKey() || StateMachine::DemoMode)) {
            StateMachine::setState < IntroState > ();
        }
    };

    static void Draw() {
        
        PD::setCursor(8, 2);
        PD::setColor(7, 0);
        PD::print("YOUR SCORE: ");
        PD::printf("%d", FinalScore);

        PD::setCursor(120, 2);
        PD::setColor(7, 0);
        PD::print("HIGH SCORE: ");
        PD::printf("%d", milkShakeCookie.highScore);
        
        PD::setCursor(120, 2);
        PD::setColor(7, 0);
        Tools::PrintCentered(110, 140, 7, "No animals were harmed in");
        Tools::PrintCentered(110, 150, 7, "the making of this game");
         
        Tools::PrintCentered(110, 165, 7, "Press any key..");

    };
};