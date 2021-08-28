#pragma once

#include <LibAudio>

constexpr auto tuneGood = SIMPLE_TUNE(C / 4, C5 / 4, C6 / 4).tempo(240);
constexpr auto tuneBad = SIMPLE_TUNE(E - 4 / 2, D - 3 / 4, C - 2 / 2, ).tempo(220);
constexpr auto tuneLoading = SIMPLE_TUNE(A / 4, B / 4, C / 4, D / 4, E / 4, F / 4, G / 4).tempo(220);
constexpr auto tuneGameOver = SIMPLE_TUNE(D - 4 / 4, C #4/4,C-4/4,B-3/4,A#3/1,X/4,A-3/4,D-4/4).tempo(220);
constexpr auto tuneGameOverFull = SIMPLE_TUNE(C - 4 / 4, C - 4 / 4, C - 4 / 4, D - 4 / 4, C - 4 / 2, X / 4, E - 4 / 4, F - 4 / 4).tempo(200);

class AudioManager {

    public:

        static void playMusic() {
            //Audio::play < 0 > ("music/milk1.raw");
        };

    static void playGood() {
        auto & source = Audio::play < 0 > (tuneGood);
        source.note().wave(WSQUARE);
    };

    static void playBad() {
        Audio::play < 0 > (tuneBad);
    };

    static void playLoading() {
        Audio::play < 1 > (tuneLoading);
    };

    static void playGameOver() {
        Audio::play < 1 > (tuneGameOver);
    };
    
    static void playGameOverFull() {
        Audio::play < 1 > (tuneGameOverFull);
    };

};