//
//  MainMenu.h
//  Chalky
//
//  Created by Ibrahim on 22/09/2013.
//
//

#ifndef __Chalky__MainMenu__
#define __Chalky__MainMenu__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class MainMenu : public CCLayer
{
public:
    CCScene* scene();
    CREATE_FUNC(MainMenu);
private :
    MainMenu();
    ~MainMenu();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addButton();
    
    void playButtonPressed();
    void playHSButtonPressed();
    
};

#endif /* defined(__Chalky__MainMenu__) */
