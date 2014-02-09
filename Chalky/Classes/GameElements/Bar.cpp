//
//  Tile.cpp
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#include "Bar.h"

#pragma mark - constructor/destructor
Bar::Bar()
{

    
}

Bar::~Bar()
{
}

#pragma mark - create methods
Bar* Bar::create(CCSprite *normalSprite, CCSprite *selectedSprite, CCSprite *disabledSprite)
{
    Bar *b = new Bar();
    if (b != NULL && b->init(normalSprite, selectedSprite, disabledSprite)) {
        b->autorelease();
//        b->setNormalImage(normalSprite);
//        b->setSelectedImage(selectedSprite);
//        b->setDisabledImage(disabledSprite);
        b->setTarget(b, menu_selector(Bar::barTapped));
    } else {
        delete b;
        b = NULL;
    }
    return b;
}

Bar* Bar::create(CCSprite *normalSprite, CCSprite *selectedSprite, CCObject *target, SEL_MenuHandler selector)
{
    Bar *b = new Bar();
    if (b != NULL && b->init(normalSprite, selectedSprite, target, selector)) {
        b->autorelease();
        b->setNormalImage(normalSprite);
        b->setSelectedImage(selectedSprite);
    } else {
        delete b;
        b = NULL;
    }
    return b;
}

Bar* Bar::create(CCSprite *normalSprite, CCSprite *selectedSprite, CCSprite *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    Bar *b = new Bar();
    if (b != NULL && b->init(normalSprite, selectedSprite, disabledSprite, target, selector)) {
        b->autorelease();
        b->setNormalImage(normalSprite);
        b->setSelectedImage(selectedSprite);
        b->setDisabledImage(disabledSprite);
    } else {
        delete b;
        b = NULL;
    }
    return b;
}


#pragma mark - init methods
bool Bar::init(CCSprite *normalSprite, CCSprite *selectedSprite, CCSprite *disabledSprite)
{
    if (!CCMenuItemSprite::create(normalSprite, selectedSprite, disabledSprite)) {
        return false;
    }
    CCSprite * copyNormal = CCSprite::createWithTexture(normalSprite->getTexture());
    CCSprite * copySelected = CCSprite::createWithTexture(selectedSprite->getTexture());
    this->setNormalImage(copyNormal);
    this->setSelectedImage(copySelected);
    return true;
}

bool Bar::init(CCSprite *normalSprite, CCSprite *selectedSprite, CCObject *target, SEL_MenuHandler selector)
{
    if (!CCMenuItemSprite::create(normalSprite, selectedSprite, target, selector)) {
        return false;
    }
    return true;
}

bool Bar::init(CCSprite *normalSprite, CCSprite *selectedSprite, CCSprite *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
    if (!CCMenuItemSprite::create(normalSprite, selectedSprite, disabledSprite, target, selector)) {
        return false;
    }
    return true;
}
                     
                     
void Bar::barTapped(CCObject* sender)
{
    Bar *b = (Bar*)sender;
    CCLog("BAR TAG IS : %i", b->getTag());
    b->setVisible(false);
}







