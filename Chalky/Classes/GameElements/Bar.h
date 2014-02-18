//
//  Tile.h
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#ifndef __Chalky__Tile__
#define __Chalky__Tile__

#include <iostream>
#include "cocos2d.h"
#include "ChalkyManager.h"

USING_NS_CC;

class Bar : public CCMenuItemSprite
{
public :
    static Bar *create(CCSprite* normalSprite, CCSprite* selectedSprite, CCSprite* disabledSprite = NULL);
    static Bar *create(CCSprite* normalSprite, CCSprite* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    static Bar *create(CCSprite* normalSprite, CCSprite* selectedSprite, CCSprite* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    
private :    
    Bar();
    ~Bar();
    bool init(CCSprite* normalSprite, CCSprite* selectedSprite, CCSprite* disabledSprite = NULL);
    bool init(CCSprite* normalSprite, CCSprite* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    bool init(CCSprite* normalSprite, CCSprite* selectedSprite, CCSprite* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    
    CC_SYNTHESIZE(kDusterColor, barColor, BarColor);
    void barTapped(CCObject* sender);
};

#endif /* defined(__Chalky__Tile__) */
