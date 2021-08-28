#pragma once

#include "sprites.h"
#include "images/milkshake.h"
#include "images/pancake.h"
#include "images/tablePiece.h"
#include "images/chair.h"
#include "images/dust.h"
#include "images/star.h"

#include <LibHotswap>
#include <LibLog>

class SpritesManager {
    using PD = Pokitto::Display;
    using CatData = Hotswap < 64 * 1024, 0 > ;
    using BunnyData = Hotswap < 64 * 1024, 1 > ;

    inline static constexpr int loadPriority = 4;

    private:
        inline static
    const uint8_t * dataCat;
    inline static
    const uint8_t * dataBunny;

    public:
        enum AnimType {
            Idle,
            Good,
            Bad
        };

    enum FoodType {
        None,
        Milkshake,
        Pancake
    };

    static inline int catLevel;
    static inline int bunnyLevel;

    static inline Sprite catSprite;
    static inline Sprite bunnySprite;

    static inline bool loadingCat;
    static inline bool loadingBunny;

    static void catDataLoaded(const uint8_t * data) {
        dataCat = data;
        PlayCatAnimation(AnimType::Idle);
        loadingCat = false;
    }

    static void LoadCat(int level) {
        catLevel = level;
        loadingCat = true;
        switch (catLevel) {
            case 0:
                CatData::load("data/milkshak/cat1.bin", catDataLoaded, loadPriority);
                break;
            case 1:
                CatData::load("data/milkshak/cat2.bin", catDataLoaded, loadPriority);
                break;
            case 2:
                CatData::load("data/milkshak/cat3.bin", catDataLoaded, loadPriority);
                break;
            case 3:
                CatData::load("data/milkshak/cat4.bin", catDataLoaded, loadPriority);
                break;
            case 4:
                CatData::load("data/milkshak/cat5.bin", catDataLoaded, loadPriority);
                break;
            case 5:
                CatData::load("data/milkshak/cat6.bin", catDataLoaded, loadPriority);
                break;
        }
    };

    static void PlayCatAnimation(AnimType type) {
        switch (type) {
            case AnimType::Idle:
                catSprite.play( * reinterpret_cast <
                    const Cat1 * > (dataCat), Cat1::Idle);
                break;
            case AnimType::Good:
                catSprite.play( * reinterpret_cast <
                    const Cat1 * > (dataCat), Cat1::Good);
                break;
            case AnimType::Bad:
                catSprite.play( * reinterpret_cast <
                    const Cat1 * > (dataCat), Cat1::Bad);
                break;
        }
    };

    //-------------------------------------------------------
    static void bunnyDataLoaded(const uint8_t * data) {
        dataBunny = data;
        PlayBunnyAnimation(AnimType::Idle);
        loadingBunny = false;
    }


    static void LoadBunny(int level) {
        loadingBunny = true;
        bunnyLevel = level;
        switch (bunnyLevel) {
            case 0:
                BunnyData::load("data/milkshak/bunny1.bin", bunnyDataLoaded, loadPriority);
                break;
            case 1:
                BunnyData::load("data/milkshak/bunny2.bin", bunnyDataLoaded, loadPriority);
                break;
            case 2:
                BunnyData::load("data/milkshak/bunny3.bin", bunnyDataLoaded, loadPriority);
                break;
            case 3:
                BunnyData::load("data/milkshak/bunny4.bin", bunnyDataLoaded, loadPriority);
                break;
            case 4:
                BunnyData::load("data/milkshak/bunny5.bin", bunnyDataLoaded, loadPriority);
                break;
            case 5:
                BunnyData::load("data/milkshak/bunny6.bin", bunnyDataLoaded, loadPriority);
                break;
        }
    };

    static void PlayBunnyAnimation(AnimType type) {

        switch (type) {
            case AnimType::Idle:
                bunnySprite.play( * reinterpret_cast <
                    const Bunny1 * > (dataBunny), Bunny1::Idle);
                break;
            case AnimType::Good:
                bunnySprite.play( * reinterpret_cast <
                    const Bunny1 * > (dataBunny), Bunny1::Good);
                break;
            case AnimType::Bad:
                bunnySprite.play( * reinterpret_cast <
                    const Bunny1 * > (dataBunny), Bunny1::Bad);
                break;
        }
    };

    //---------------------------------------------------

    static void DrawFood(int x, int y, FoodType foodType) {
        switch (foodType) {
            case FoodType::Milkshake:
                PD::drawBitmap(x - milkshake[0] / 2, y - milkshake[1], milkshake);
                break;
            case FoodType::Pancake:
                PD::drawBitmap(x - pancake[0] / 2, y - pancake[1], pancake);
                break;
        }
    };


    static void DrawStage() {

        //Background
        PD::setColor(15);
        PD::fillRect(0, 0, 220, 176);

        //Floor
        PD::setColor(45);
        PD::fillRect(0, 145, 220, 35);

        //Battiscopa
        PD::setColor(91);
        PD::fillRect(0, 141, 220, 4);

        //Char
        PD::drawBitmap(30, 100, chair);
        PD::drawBitmapXFlipped(145, 100, chair);

        //
        constexpr int border = 4;

        //Sign pancake
        constexpr int xPan = 50;
        constexpr int yPan = 45;

        PD::setColor(158);
        PD::fillRect(xPan - border * 2 - pancake[0] / 2, yPan - border * 2, pancake[0] + border * 4, pancake[1] + border * 4);
        PD::setColor(150);
        PD::fillRect(xPan - border - pancake[0] / 2, yPan - border, pancake[0] + border * 2, pancake[1] + border * 2);
        PD::setColor(9); //nail
        PD::fillRect(xPan - 1, yPan + 1 - border * 2, 2, 2);
        PD::drawBitmap(xPan - pancake[0] / 2, yPan, pancake);

        //Sign milkshake
        constexpr int xMilk = 170;
        constexpr int yMilk = 45;
        PD::setColor(158);
        PD::fillRect(xMilk - border * 2 - milkshake[0] / 2, yMilk - border * 2, milkshake[0] + border * 4, milkshake[1] + border * 4);
        PD::setColor(150);
        PD::fillRect(xMilk - border - milkshake[0] / 2, yMilk - border, milkshake[0] + border * 2, milkshake[1] + border * 2);
        PD::setColor(9); //nail
        PD::fillRect(xMilk - 1, yMilk + 1 - border * 2, 2, 2);
        PD::drawBitmap(xMilk - milkshake[0] / 2, yMilk, milkshake);

        //Table
        PD::drawBitmap(66, 118 + 24, tablePiece);
        PD::drawBitmap(66, 118 + 16, tablePiece);
        PD::drawBitmap(66, 118 + 8, tablePiece);
        PD::drawBitmap(66, 118, tablePiece);
    };

    static void DrawGameGui(int timer, int maxTimer, int retries, int score) {

        constexpr int starWidth = 36;
        auto centerX = (220 - 3 * starWidth) / 2;
        for (int i = 0; i < retries; i++)
            PD::drawBitmap(centerX + i * starWidth, 8, star);

        //Draw remaming time
        PD::setColor(246 - 8);
        PD::fillRect(0, 0, 220, 4);

        auto timeWidth = 220 * timer / maxTimer;
        PD::setColor(246);
        PD::fillRect(0, 0, timeWidth, 4);

        //Timer
        PD::setColor(7, 15);
        PD::setCursor(10, 10);
        PD::print("TIME");
        PD::setCursor(10, 20);
        PD::printf("%d.%d", timer / 10, timer % 10);

        //Score
        PD::setColor(7, 15);
        PD::setCursor(180, 10);
        PD::print("SCORE");
        PD::setCursor(200, 20);
        PD::print(score);
    }

    static void DrawDust(int x, int y, int range, bool withStars, bool withPancake = false, bool withMilkshake = false) {
        bool flip = false;
        for (int i = 0; i < 10; i++) {
            PD::drawBitmap(x + random(-range, range), y + random(-range, range), flip && withStars ? star : dust);

            if (withPancake)
                PD::drawBitmap(x + random(-range, range), y + random(-range, range), pancake);
            if (withMilkshake)
                PD::drawBitmap(x + random(-range, range), y + random(-range, range), milkshake);

            flip = !flip;
        }
    }
};