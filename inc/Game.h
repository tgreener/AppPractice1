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
#include "EventQueue.h"
#include "GameDelegate.h"
#include <vector>

typedef function<void (unsigned long dt)> UpdateFunction;
typedef vector<UpdateFunction> UpdateFunctionVector;

class Game {
protected:
    GameDelegate* delegate;
    
    bool usingRender;
    bool usingAI;
    bool usingPhys;
    bool isThreaded;
    
    int renderUpdateDelta;
    int AIUpdateDelta;
    int physicsUpdateDelta;
    int gameUpdateDelta;
    
    Application gameApp;
    
    UpdateFunctionVector updateQueue;
    
    void setTimerCallback(int updateDelta, EventQueue* eq);
    void queueUpdateFunction(UpdateFunction f);
    
public:
    Game();

    void setDelegate(GameDelegate* d);
    
    void setThreaded();
    void useRenderThread(int updateDelta);
    void useAIThread(int updateDelta);
    void usePhysicsThread(int updateDelta);
    void setGameUpdatePeriod(int updateDelta);
    
    void queueAIUpdate();
    void queueRenderUpdate();
    void queuePhysicsUpdate();
    
    void run();
    void stop();
};

#endif	/* GAME_H */

