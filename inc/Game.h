/* 
 * File:   Game.h
 * Author: toddgreener
 *
 * Created on March 28, 2014, 11:25 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "Semaphore.h"
#include "Application.h"

class Game {
protected:
    bool usingRender;
    bool usingAI;
    
    int renderUpdateDelta;
    int AIUpdateDelta;
    
    Application gameApp;
    
    Semaphore comsSem;
    
public:
    Game();
    
    void useRenderThread(int updateDelta);
    void useAIThread(int updateDelta);
    
    void run();
    void stop();
};

#endif	/* GAME_H */

