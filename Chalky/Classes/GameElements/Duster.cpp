//
//  Duster.cpp
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#include "Duster.h"
#include "ChalkyManager.h"
#include "SimpleAudioEngine.h"
Duster::Duster()
{
    initialPosition = CCPoint(0.0, 0.0);
    finalPosition = CCPoint(0.0,0.0);
    disappearingPosition = CCPoint(0.0,0.0);
    m_sprite = NULL;
}
Duster::~Duster()
{
    
}

Duster* Duster::create(const char * spriteName, kDusterColor color)
{
    Duster *b = new Duster();
    if (b != NULL && b->init(spriteName)) {
        b->autorelease();
        b->dusterColor = color;
        b->setAnchorPoint(ccp(0,0.5));
        b->calculateInitialPosition();
        b->calculateFinalPosition();
        b->calculateDisappearingPosition();
        b->setPosition(b->initialPosition);
        CCSequence * seq = CCSequence::create(
                                              CCMoveTo::create(0.5f,b->finalPosition),CCCallFunc::create(b, callfunc_selector(Duster::runRubbingAnimation)),
                                              CCDelayTime::create(0.2f),
                                              CCMoveTo::create(1.0f,b->disappearingPosition),
                                              CCCallFunc::create(b, callfunc_selector(Duster::removeFromView)),NULL);
        b->runAction(seq);
        
    } else {
        delete b;
        b = NULL;
    }
    return b;
    
}
bool Duster::init(const char * spriteName)
{
    if(!CCSprite::initWithFile(spriteName))
    return false;
    this->m_sprite = CCSprite::create(spriteName);
    return true;
    
}
void Duster::runApproachingAnimation()
{
    
}
void Duster::runRubbingAnimation()
{
    CCCallFunc *playSound = CCCallFunc::create(this, callfunc_selector(Duster::playDusterSound));
    CCMoveTo *r1 = CCMoveTo::create(0.1,ccp(this->getPositionX(),this->getPositionY()+20.0f));
    CCMoveTo *r2 = CCMoveTo::create(0.1,ccp(this->getPositionX(),this->getPositionY()-20.0f));
    CCSequence *seq = CCSequence::create(playSound, r1,r2,NULL);
    CCRepeat * seq1 = CCRepeat::create(seq, 3);
    
    this->runAction(seq1);
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(TILE_REMOVED_NOTIFICATION, this);
}

void Duster::playDusterSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("erasing.m4a");
}

void Duster::removeFromView()
{
    this->removeFromParentAndCleanup(true);
}
void Duster::calculateInitialPosition()
{
    initialPosition = CCPointMake(0.0, 0.0);
}
void Duster::calculateFinalPosition()
{
    CCSprite * image = CCSprite::create("blue_0.png");
    
    float width = image->getContentSize().width;
    switch (CHALKY_MANAGER->getGameMode()) {
        case kModeNormal:
        {
            if(dusterColor == kDusterBlue)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHide1, CHALKY_MANAGER->bar1Height);
            else if(dusterColor == kDusterYellow)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHide2, CHALKY_MANAGER->bar2Height);
            else if(dusterColor == kDusterRed)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHide3, CHALKY_MANAGER->bar3Height);
        }
        break;
        case kModeHS:
        {
            if(dusterColor == kDusterBlue)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHideSpecial, CHALKY_MANAGER->bar1Height);
            else if(dusterColor == kDusterYellow)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHideSpecial, CHALKY_MANAGER->bar2Height);
            else if(dusterColor == kDusterRed)
                finalPosition = CCPointMake(width * CHALKY_MANAGER->indexToHideSpecial, CHALKY_MANAGER->bar3Height);
        }
        break;
        
        default:
        break;
    }
    
}
void Duster::calculateDisappearingPosition()
{
    disappearingPosition =  CCPointMake(WIN_WIDTH/2.0, WIN_HEIGHT);
}
