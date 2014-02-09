//
//  LevelWinScreen.h
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#ifndef __Chalky__LevelWinScreen__
#define __Chalky__LevelWinScreen__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class LevelWinScreen : public CCLayer
{
public:
    CCScene* scene();
    CREATE_FUNC(LevelWinScreen);
    
    void continueButtonPressed();
    void quitButtonPressed();
private :
    
    LevelWinScreen();
    ~LevelWinScreen();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addButton();
    
};


#endif /* defined(__Chalky__LevelWinScreen__) */
