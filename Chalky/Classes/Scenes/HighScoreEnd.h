//
//  HighScoreEnd.h
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#ifndef __Chalky__HighScoreEnd__
#define __Chalky__HighScoreEnd__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class HighScoreEnd : public CCLayer
{
public:
    CCScene* scene();
    CREATE_FUNC(HighScoreEnd);
private :
    HighScoreEnd();
    ~HighScoreEnd();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addButton();
    
    void continueButtonPressed();
    void quitButtonPressed();
};



#endif /* defined(__Chalky__HighScoreEnd__) */
