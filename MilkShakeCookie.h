#pragma once
#include "Pokitto.h"
#include "PokittoCookie.h"

class MilkShakeCookie: public Pokitto::Cookie {

    public:

        uint8_t version = 1;
        int games = 0;
        uint8_t highScore = 0;
        bool soundtrack = false;
};