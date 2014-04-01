/* 
 * File:   GameDelegate.h
 * Author: toddgreener
 *
 * Created on March 31, 2014, 11:53 PM
 */

#ifndef GAMEDELEGATE_H
#define	GAMEDELEGATE_H

class GameDelegate {
public:
    virtual void update(int dt){};
    virtual void updateAI(int dt){};
    virtual void updatePhysics(int dt){};
    virtual void render(int dt){};
};

#endif	/* GAMEDELEGATE_H */

