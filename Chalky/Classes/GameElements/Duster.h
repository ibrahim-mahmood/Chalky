//
//  Duster.h
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#ifndef __Chalky__Duster__
#define __Chalky__Duster__

#include <iostream>
#include "cocos2d.h"
#include "ChalkyManager.h"
USING_NS_CC;
class Duster: public CCSprite
{
public:
    static Duster* create(const char * spriteName,kDusterColor color);
    kDusterColor dusterColor;
    
private:
    
    Duster();
    ~Duster();
    bool init(const char * spriteName);
    
    void runApproachingAnimation();
    void runRubbingAnimation();
    void removeFromView();
    void playDusterSound();
    
    void calculateInitialPosition();
    void calculateFinalPosition();
    void calculateDisappearingPosition();

    CCSprite * m_sprite;
    CCPoint initialPosition;
    CCPoint finalPosition;
    CCPoint disappearingPosition;
};
#endif /* defined(__Chalky__Duster__) */
