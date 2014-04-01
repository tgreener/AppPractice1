
#include "Game.h"
#include "ServiceLocator.h"

Game::Game() : usingAI(false), usingRender(false), usingPhys(false), isThreaded(false),
               renderUpdateDelta(0), AIUpdateDelta(0), physicsUpdateDelta(0), delegate(NULL) {}

void Game::setTimerCallback(int updateDelta, EventQueue* eq) {
    Timer* time = ServiceLocator::getDefaultLocator()->locateTimerService();
    
    time->setInterval(updateDelta, [=](unsigned long ts){
        eq->pushTimerEvent(ts);
    }, true);
}

void Game::setDelegate(GameDelegate* d) {
    delegate = d;
}

void Game::run() {
    gameApp.run([this]{
        if(usingAI) {
            thread AIThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(AIUpdateDelta, eq);
                
                eq->addTimerEventHandler([=](TimerEvent te) {
                    delegate->updateAI(te.getElapsedTimeMilli());
                });
                
                eq->serviceEventLoop();
            });
        }
        
        if(usingRender) {
            thread renderThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(renderUpdateDelta, eq);
                
                eq->addTimerEventHandler([=](TimerEvent te) {
                    delegate->render(te.getElapsedTimeMilli());
                });
                
                eq->serviceEventLoop();
            });
        }
        
        if(usingPhys) {
            thread renderThread([=]{
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                setTimerCallback(physicsUpdateDelta, eq);
                
                eq->addTimerEventHandler([=](TimerEvent te) {
                    delegate->updatePhysics(te.getElapsedTimeMilli());
                });
                
                eq->serviceEventLoop();
            });
        }
        
        thread updateThread([=]{
            EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
            setTimerCallback(gameUpdateDelta, eq);

            eq->addTimerEventHandler([this](TimerEvent te) {
                
                delegate->update(te.getElapsedTimeMilli());
                
                if(!isThreaded) {
                    for(UpdateFunctionVector::size_type i = 0; i < updateQueue.size(); i++) {
                        updateQueue[i](te.getElapsedTimeMilli());
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

void Game::queueUpdateFunction(UpdateFunction f) {
    if(!isThreaded) {
        updateQueue.push_back(f);
    }
}

void Game::queueAIUpdate() {
    queueUpdateFunction([=](unsigned long dt){
        delegate->updateAI(dt);
    });
}

void Game::queueRenderUpdate() {
    queueUpdateFunction([=](unsigned long dt){
        delegate->render(dt);
    });
}

void Game::queuePhysicsUpdate() {
    queueUpdateFunction([=](unsigned long dt){
        delegate->updatePhysics(dt);
    });
}
