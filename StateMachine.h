#pragma once
using PC = Pokitto::Core;

namespace StateMachine {
    
    inline bool DemoMode = false;
    
    namespace {
        inline void (*Init)() = +[]{};
        inline int msState;
    }
    
    inline void (*Draw)() = +[]{};
    
    inline void (*Update)() = +[]{};
    
    template <class Class> void setState(){
        Update = +[]{
            Update = Class::Update;
            Draw = Class::Draw;
            msState = PC::getTime();
            Init();
            Update();
        };
        Init = Class::Init;
    }
      
    int GetElapsed(){
        return PC::getTime() - msState;
    }
    
}