
#include "Game.h"
#include "ServiceLocator.h"

Game::Game() : usingAI(false), usingRender(false), renderUpdateDelta(0), AIUpdateDelta(0) {
    comsSem.signal();
}

void Game::run() {
    comsSem.wait();
    
    gameApp.run([this]{
        // Maybe some day I'll need to pass messages from the main thread to the
        // others, but for now it's not necessary.
        // ServiceLocator* sloc = ServiceLocator::getDefaultLocator();
        
        if(usingAI) {
            thread AIThread([=]{
                Timer* time = ServiceLocator::getDefaultLocator()->locateTimerService();
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                
                time->setInterval(AIUpdateDelta, [=]{
                    unsigned long delta = 0;
                    
                    // Figure out how much time has passed
                    
                    eq->pushTimerEvent(delta);
                }, true);
                
                eq->addTimerEventHandler([](TimerEvent te) {
                    // Call game delegate updateAI() method.
                });
                
                eq->serviceEventLoop();
            });
        }
        
        if(usingRender) {
            thread renderThread([=]{
                Timer* time = ServiceLocator::getDefaultLocator()->locateTimerService();
                EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();
                
                time->setInterval(renderUpdateDelta, [=]{
                    unsigned long delta = 0;
                    
                    // Figure out how much time has passed
                    
                    eq->pushTimerEvent(delta);
                }, true);
                
                eq->addTimerEventHandler([](TimerEvent te) {
                    // Call game delegate render() method.
                });
                
                eq->serviceEventLoop();
            });
        }
        
        thread updateThread([=]{
            Timer* time = ServiceLocator::getDefaultLocator()->locateTimerService();
            EventQueue* eq = ServiceLocator::getDefaultLocator()->locateEventService();

            time->setInterval(gameUpdateDelta, [=]{
                unsigned long delta = 0;

                // Figure out how much time has passed

                eq->pushTimerEvent(delta);
            }, true);

            eq->addTimerEventHandler([](TimerEvent te) {
                // Call game delegate update() method.
                if(!usingAI) {
                    // Call game delegate updateAI() method.
                }
                
                if(!usingRender) {
                    // Call game delegate render() method.
                }
            });

            eq->serviceEventLoop();
        });
    });
    
    comsSem.signal();
}

void Game::stop() {
    comsSem.wait();
    
    gameApp.stop();
    
    comsSem.signal();
}

void Game::setGameUpdatePeriod(int updateDelta) {
    comsSem.wait();
    
    gameUpdateDelta = updateDelta;
    
    comsSem.signal();
}

void Game::useRenderThread(int dt) {
    comsSem.wait();
    
    usingAI = true;
    AIUpdateDelta = dt;
    
    comsSem.signal();
}

void Game::useAIThread(int dt) {
    comsSem.wait();
    
    usingRender = true;
    renderUpdateDelta = dt;
    
    comsSem.signal();
}
