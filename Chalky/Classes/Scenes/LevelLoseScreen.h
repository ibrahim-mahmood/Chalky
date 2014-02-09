//
//  LevelLoseScreen.h
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#ifndef __Chalky__LevelLoseScreen__
#define __Chalky__LevelLoseScreen__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class LevelLoseScreen : public CCLayer
{
public :
    CCScene* scene();
    CREATE_FUNC(LevelLoseScreen);
private :
    
    LevelLoseScreen();
    ~LevelLoseScreen();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addButton();
    
    void continueButtonPressed();
    void quitButtonPressed();
};


#endif /* defined(__Chalky__LevelLoseScreen__) */
