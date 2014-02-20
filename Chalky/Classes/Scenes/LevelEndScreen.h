//
//  LevelEndScreen.h
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#ifndef __Chalky__LevelEndScreen__
#define __Chalky__LevelEndScreen__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class LevelEndScreen : public CCLayer
{
public:
    CCScene* scene();
    static LevelEndScreen* create(bool levelCleared);
    
    void continueButtonPressed();
    void quitButtonPressed();
private :
    
    bool levelSuccess;
    
    LevelEndScreen();
    ~LevelEndScreen();
    virtual void onEnter();
    virtual void onExit();
    virtual bool init(bool levelCleared);
    void addLayerAssets();
    void addBackground();
    void addLabels();
    void addButtons();
    void updateLevel();
    
};


#endif /* defined(__Chalky__LevelEndScreen__) */
