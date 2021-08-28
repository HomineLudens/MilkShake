#pragma once

#include <Pokitto.h>
#include <File>
#include <LibLOG>

using PC = Pokitto::Core;
using PD = Pokitto::Display;
using PB = Pokitto::Buttons;

class Tools {
    public:
    
    static void LoadImage(const char * img) {
        File file;
        file.openRO(img);
        for (int i = 0; i < 176; ++i) {
            unsigned char buffer[220];
            file.read(buffer);
            flushLine(PD::paletteptr, buffer);
        };
    };

    static void PrintCentered(int x, int y, int color,
        const char * text) {

        auto fw = PD::fontWidth - 2;
        auto chars = strlen(text);

        PD::setColor(color);
        PD::setCursor(x - (chars * fw) / 2, y);
        PD::print(text);
    };

    static bool AnyKey() {
        return PB::pressed(BTN_LEFT) ||
        PB::pressed(BTN_RIGHT) ||
        PB::pressed(BTN_UP) ||
        PB::pressed(BTN_DOWN) ||
        PB::pressed(BTN_A) ||
        PB::pressed(BTN_B) ||
        PB::pressed(BTN_C);
    };

};