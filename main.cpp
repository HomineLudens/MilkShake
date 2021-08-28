#include <Pokitto.h>
#include <miloslav.h>
#include <File>
#include <LibLOG>
#include "MilkShakeCookie.h"

#include "StateMachine.h"
#include "IntroState.h"
#include "AudioManager.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

Audio::Sink < 2, PROJ_AUD_FREQ > audio;
MilkShakeCookie milkShakeCookie;

void init() {
    PD::loadRGBPalette(miloslav);
    PD::setFont(fontMonkey);
    milkShakeCookie.begin("MILKSHAK", milkShakeCookie); //initialize cookie 

    StateMachine::setState<IntroState>();
}

void update() {
    StateMachine::Update();
    StateMachine::Draw();
}