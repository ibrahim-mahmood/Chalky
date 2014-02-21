//
//  GamePlayScene.h
//  Chalky
//
//  Created by Ibrahim on 9/20/13.
//
//

#ifndef __Chalky__GamePlayScene__
#define __Chalky__GamePlayScene__

#include <iostream>
#include "cocos2d.h"
#include "ChalkyManager.h"
#include "Duster.h"
#include "cocos-ext.h"

#include "spine-cocos2dx.h"

using namespace extension;

USING_NS_CC;

class GamePlayScene : public CCLayer
{
public :
    CCScene* scene();
    CREATE_FUNC(GamePlayScene);
    void updateTimer(float dt);
private :
    GamePlayScene();
    ~GamePlayScene();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addLabels();
    void addBarsForLevel(float level);
    void addChalkyForLevel(float level);
    bool init();
    void hideTileForBar(Duster* duster);
    
    CC_SYNTHESIZE_RETAIN(CCArray *, barsBlue, BarsBlue);
    CC_SYNTHESIZE_RETAIN(CCArray *, barsYellow, BarsYellow);
    CC_SYNTHESIZE_RETAIN(CCArray *, barsRed, barsRed);
    
    int barWidth;
    int barHeight;
    
    void startGameForLevel(float levelNo);
    void stopLoop();
    void playChalkyFallAnimation(CCSkeletonAnimation *chalkyToRemove);
    void gameLoop();
    
    void ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
	void ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
    virtual void update(float dt);
    
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyBlue, ChalkyBlue);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyYellow, ChalkyYellow);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyRed, ChalkyRed);

    void removeChalkyBlue();
    void removeChalkyYellow();
    void removeChalkyRed();
    
    void checkGameEndBlue(float chalkyPosition);
    void checkGameEndYellow(float chalkyPosition);
    void checkGameEndRed(float chalkyPosition);
    
    bool chalkySpecialBlue;
    bool chalkySpecialYellow;
    bool chalkySpecialRed;
    
    void addChalkiesRandomly();
    int startTag;
    int currentGameLevel;
    
    void goToHighScoreEndScreen();
    void goToLevelWinScreen();
    void goToLevelLoseScreen();
    
    void setupGameElements();
    
    CCLabelTTF *timerLabel;
    int countdownTimer;
    float totalTimePlayed;
    int previousTimeCount;
    
    void setSpecialChalkyStatus();
    
};


#endif /* defined(__Chalky__GamePlayScene__) */
