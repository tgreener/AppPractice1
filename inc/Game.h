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
#include <vector>

typedef vector<function<void (void)> > ProcedureVector;

class Game {
protected:
    bool usingRender;
    bool usingAI;
    bool usingPhys;
    bool isThreaded;
    
    int renderUpdateDelta;
    int AIUpdateDelta;
    int physicsUpdateDelta;
    int gameUpdateDelta;
    
    Application gameApp;
    
    ProcedureVector updateQueue;
    
    void setTimerCallback(int updateDelta, EventQueue* eq);
    
public:
    Game();

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

