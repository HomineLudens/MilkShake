
// Generated file - DO NOT EDIT!

#pragma once

class Sprite {
public:
    using OnEndAnimationCallback = void (*)(Sprite*);

    OnEndAnimationCallback onEndAnimation = +[](Sprite *sprite){ if(sprite->loop)sprite->frame = 0; sprite->animEnd = true; };
    const uint8_t *data = nullptr;
    std::uint32_t frameTime = 0;
    std::uint16_t frame = 0;
    std::uint16_t animation = 0;
    bool loop = false;
    bool animEnd = false;

    Sprite() = default;
    virtual ~Sprite(){}
    
    template<typename SpriteType>
    void play(const SpriteType& data, typename SpriteType::Animation animation){ 
        this->animation = static_cast<std::uint16_t>(animation); 
        this->data = reinterpret_cast<const uint8_t *>(&data);
        frame = 0;
        frameTime = Pokitto::Core::getTime() + getFrameDuration(0);
        animEnd = false;
    }
    
    std::uint8_t getAnimationFrameCount(){ return data[ 2 + animation ]; }

    std::uint8_t getFrameId(std::uint32_t frame){ return data[ 2 + animation + 1 + frame * 2]; }

    std::uint32_t getFrameDuration(std::uint32_t frame){ return data[ 2 + animation + 1 + frame * 2 + 1 ] * 10; }
    
    std::uint32_t getFrameWidth(){ return getFrameBitmap(getFrameId(frame))[2]; }
    
    std::uint32_t getFrameHeight(){ return getFrameBitmap(getFrameId(frame))[3]; }

    const uint8_t *getFrameBitmap(std::uint32_t frameId){ 
        std::uint32_t offset = 2 + data[0] + (static_cast<std::uint32_t>(data[1]) << 8);
        uint32_t shift;
        switch(Pokitto::Display::m_colordepth){
        case 8: shift = 0; break;
        case 4: shift = 1; break;
        case 2: shift = 2; break;
        case 1: shift = 3; break;
        default: shift = 0; break;
        }
        
        while(frameId--){
            std::uint32_t w = data[offset + 2];
            std::uint32_t h = data[offset + 3];
            std::uint32_t total = w*h >> shift;
            offset += total + 4;
        }
        
        return data + offset;
    }

    void draw(std::uint32_t x, std::uint32_t y, bool flip=false, bool mirror=false, std::uint32_t recolor=0){
        if(!data) 
            return;
            
        std::uint32_t now = Pokitto::Core::getTime();
        while(true) {
            int32_t delta = now - frameTime;
            if( delta < 0 ){
                const uint8_t *bmp = getFrameBitmap(getFrameId(frame));
                x += *bmp++;
                y += *bmp++;

                #if PROJ_SCREENMODE == TASMODE
                if(Pokitto::Display::m_colordepth == 8){
                    Pokitto::Display::drawSprite(x, y, bmp, flip, mirror, recolor);
                    return;
                }
                #endif

                if(flip) Pokitto::Display::drawBitmapYFlipped(x, y, bmp);
                else if(mirror)  Pokitto::Display::drawBitmapXFlipped(x, y, bmp);
                else  Pokitto::Display::drawBitmap(x, y, bmp);
                return;
            }
            frame++;
            if( frame == getAnimationFrameCount() ){
                onEndAnimation(this);
                if(!loop)
                    frame = getAnimationFrameCount()-1;
            }
            
            frameTime += getFrameDuration(frame);
        }
    }
};

class Bunny1 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Bunny2 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Bunny3 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Bunny4 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Bunny5 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 12
	};
};

class Bunny6 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3
	};
};

class Cat1 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Cat2 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Cat3 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Cat4 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Cat5 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3,
		Bad = 10
	};
};

class Cat6 {
public:
    enum Animation : std::uint16_t {
		Idle = 0,
		Good = 3
	};
};


// https://stackoverflow.com/a/19591902
extern "C" {
extern const Bunny1 bunny1;
extern const Bunny2 bunny2;
extern const Bunny3 bunny3;
extern const Bunny4 bunny4;
extern const Bunny5 bunny5;
extern const Bunny6 bunny6;
extern const Cat1 cat1;
extern const Cat2 cat2;
extern const Cat3 cat3;
extern const Cat4 cat4;
extern const Cat5 cat5;
extern const Cat6 cat6;
}
