//
//  Chalky.cpp
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#include "Chalky.h"
#include "ChalkyManager.h"
#include "Bar.h"
#include "GamePlayScene.h"

Chalky::Chalky()
{
    m_sprite = NULL;
}
Chalky::~Chalky()
{
    
}

Chalky* Chalky::create(const char *jsonName, const char *atlasName, float positionX, float positionY)
{
    Chalky *b = new Chalky();
    if (b != NULL && b->init(jsonName, atlasName, positionX, positionY)) {
        b->retain();
        b->setPosition(ccp(positionX, positionY));
        b->setAnchorPoint(ccp(0.5, 0.5));
        b->addSpriteToLayer(jsonName, atlasName);
        b->chalkyIndex = 0;
    } else {
        delete b;
        b = NULL;
    }
    return b;
}

bool Chalky::init(const char *jsonName, const char *atlasName, float positionX, float positionY)
{
    if (!CCLayer::create()) {
        return false;
    }
    return true;
}

void Chalky::addSpriteToLayer(const char *jsonName, const char *atlasName)
{
    m_sprite = CCSkeletonAnimation::createWithFile(jsonName, atlasName);
    addChild(m_sprite);
}

void Chalky::startChalkyUpdate()
{
    scheduleUpdate();
}

void Chalky::stopChalkyUpdate()
{
    unscheduleUpdate();
}

void Chalky::update(float dt)
{
    if (dynamic_cast<GamePlayScene*>(this->getParent())) {
        ((GamePlayScene*)this->getParent())->updateTimer(dt);
    }
    if (col == kChalkyBlue) {
        float oldChalkyPosition = getPositionX();
        float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(1, CHALKY_SPEED_KEY) * dt);
        setPosition(ccp(newChalkyPosition, getPositionY()));
        checkGameEnd(newChalkyPosition);
    }
    else if (col == kChalkyYellow) {
        float oldChalkyPosition = getPositionX();
        float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(2, CHALKY_SPEED_KEY) * dt);
        setPosition(ccp(newChalkyPosition, getPositionY()));
        checkGameEnd(newChalkyPosition);
    }
    else {
        float oldChalkyPosition = getPositionX();
        float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(3, CHALKY_SPEED_KEY) * dt);
        setPosition(ccp(newChalkyPosition, getPositionY()));
        checkGameEnd(newChalkyPosition);
    }
    
}

void Chalky::checkGameEnd(float chalkyPosition)
{
    if (chalkyIndex >= CHALKY_MANAGER->totalSteps) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(type);
        removeFromParentAndCleanup(true);
    }
    else {
        int tag = 0;
        tag = chalkyPosition / CHALKY_MANAGER->barWidth;
        chalkyIndex = tag;
        CCNode *parent = getParent();
        Bar *b = (Bar*)parent->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                //playFallingAnimation();
                removeChalky();
            }
        }
        else {
            CCLog("Stop here");
        }
    }
}

void Chalky::playRunningAnimation()
{
    m_sprite->setAnimation(RIDE_ANIMATION_NAME, true);
}
void Chalky::playFallingAnimation()
{
    m_sprite->addAnimation(FALL_ANIMATION_NAME, false);
    CCDelayTime *delay = CCDelayTime::create(0.5);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(Chalky::removeChalky));
    CCSequence *seq = CCSequence::create(delay, call, NULL);
    m_sprite->runAction(seq);
}

void Chalky::setChalkyColor(const ccColor3B &color)
{
    m_sprite->setColor(color);
}

void Chalky::removeChalky()
{
    m_sprite->stopAllActions();
    m_sprite->removeFromParentAndCleanup(true);
    m_sprite = NULL;
    removeFromParentAndCleanup(true);
}
