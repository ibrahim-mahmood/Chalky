//
//  ChalkyManager.h
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#ifndef __Chalky__ChalkyManager__
#define __Chalky__ChalkyManager__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "Macros.h"

USING_NS_CC;

#define CHALKY_MANAGER ChalkyManager::sharedManager()

typedef enum
{
    kDusterRed = 2,
    kDusterBlue = 0,
    kDusterYellow = 1
}kDusterColor;

typedef enum
{
    kModeNormal,
    kModeHS,
    kModeUnknown
}kGameMode;


class ChalkyManager : public CCObject
{
public:
	ChalkyManager();
	~ChalkyManager();
	
	static ChalkyManager* sharedManager();
    int chalky1Index;
    int chalky2Index;
    int chalky3Index;
    
    int indexToHide1;
    int indexToHide2;
    int indexToHide3;
    
    int indexToHideSpecial;
    
    int bar1Height = WIN_HEIGHT/1.5;
    int bar2Height = WIN_HEIGHT/2.2;
    int bar3Height = WIN_HEIGHT/3.9;
    
    int lastScore;
    
    int blueChalks;
    int yellowChalks;
    int redChalks;

    int currentLevel;
    
    int totalSteps;
    int barWidth;
    
    void loadGameData();
    float getFloatValueForKey(int _numberToAppend, std::string _key);
    float getFloatValueForKey(std::string _key);
    void updatePlayerScore(bool _isSpecialChalky);
    
    CC_SYNTHESIZE(kGameMode, gameMode, GameMode);
    CC_SYNTHESIZE_RETAIN(CCDictionary*, gameData, GameData);
    
    
};

#endif /* defined(__Chalky__ChalkyManager__) */
