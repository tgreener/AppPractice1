
#include "Game.h"
#include "ServiceLocator.h"

Game::Game() : usingAI(false), usingRender(false), usingPhys(false), isThreaded(false),
               renderUpdateDelta(0), AIUpdateDelta(0), physicsUpdateDelta(0) {}

void Game::setTimerCallback(int updateDelta, EventQueue* eq) {
    Timer* time = ServiceLocator::getDefaultLocator()->locateTimerService();
    
    time->setInterval(updateDelta, [=]{
        unsigned long delta = 0;

        // Figure out how much time has passed

        eq->pushTimerEvent(delta);
    }, true);
}

void Game::run() {
    
    gameApp.run([this]{
        if(usingAI) {
            thread AIThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(AIUpdateDelta, eq);
                
                eq->addTimerEventHandler([](TimerEvent te) {
                    // Call game delegate updateAI() method.
                });
                
                eq->serviceEventLoop();
            });
        }
        
        if(usingRender) {
            thread renderThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(renderUpdateDelta, eq);
                
                eq->addTimerEventHandler([](TimerEvent te) {
                    // Call game delegate render() method.
                });
                
                eq->serviceEventLoop();
            });
        }
        
        if(usingPhys) {
            thread renderThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(physicsUpdateDelta, eq);
                
                eq->addTimerEventHandler([](TimerEvent te) {
                    // Call game delegate updatePhysics() method.
                });
                
                eq->serviceEventLoop();
            });
        }
        
        thread updateThread([=]{
            EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
            setTimerCallback(gameUpdateDelta, eq);

            eq->addTimerEventHandler([this](TimerEvent te) {
                
                // Call game delegate update() method.
                
                if(!isThreaded) {
                    for(ProcedureVector::size_type i = 0; i < updateQueue.size(); i++) {
                        updateQueue[i]();
                    }
                }
            });

            eq->serviceEventLoop();
        });
    });
}

void Game::stop() {
    // Need to stop thread event pumps...
    gameApp.stop();
}

void Game::setThreaded() {
    isThreaded = true;
}

void Game::setGameUpdatePeriod(int updateDelta) {
    gameUpdateDelta = updateDelta;
}

void Game::useRenderThread(int dt) {
    if(isThreaded) {
        usingAI = true;
        AIUpdateDelta = dt;
    }
}

void Game::useAIThread(int dt) {
    if(isThreaded) {
        usingRender = true;
        renderUpdateDelta = dt;
    }
}

void Game::usePhysicsThread(int updateDelta) {
    if(isThreaded) {
        usingPhys = true;
        physicsUpdateDelta = updateDelta;
    }
}

void Game::queueAIUpdate() {
    if(!isThreaded) {
        updateQueue.push_back([this]{
            // Call game delegate updateAI() method.
        });
    }
}

void Game::queueRenderUpdate() {
    if(!isThreaded) {
        updateQueue.push_back([this]{
            // Call game delegate render() method.
        });
    }
}

void Game::queuePhysicsUpdate() {
    if(!isThreaded) {
        updateQueue.push_back([this]{
            // Call game delegate updatePhysics() method.
        });
    }
}
