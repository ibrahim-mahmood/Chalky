//
//  Chalky.h
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#ifndef __Chalky__Chalky__
#define __Chalky__Chalky__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "spine-cocos2dx.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum
{   kChalkyRed = 2,
    kChalkyBlue = 0,
    kChalkyYellow = 1
}ChalkyColor;

typedef enum
{
    kChalkyNormal = 0,
    kChalkySpecial = 1
}ChalkyType;

class  Chalky : public CCLayer
{
public:
    static Chalky *create(const char *jsonName, const char *atlasName, float positionX = 0.0, float positionY = 0.0);
    
    void setChalkyColor(const ccColor3B& color);
    void playRunningAnimation();
    void startChalkyUpdate();
    
    ChalkyColor col;
    ChalkyType type;

private:
    Chalky();
    ~Chalky();
    bool init(const char *fileName, const char *atlasName, float positionX = 0.0, float positionY = 0.0);
    void addSpriteToLayer(const char *jsonName, const char *atlasName);
    
    virtual void update(float dt);
    void checkGameEnd(float chalkyPosition);
    void stopChalkyUpdate();
    void playFallingAnimation();
    void removeChalky();
    
    int chalkyIndex;
    CCSkeletonAnimation * m_sprite;
};
#endif /* defined(__Chalky__Chalky__) */
