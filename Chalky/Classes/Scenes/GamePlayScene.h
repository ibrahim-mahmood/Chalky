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
private :
    GamePlayScene();
    ~GamePlayScene();
    virtual void onEnter();
    virtual void onExit();
    void addLayerAssets();
    void addBackground();
    void addTitleLabel();
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
    void playChalkyLoseAnimation(CCSkeletonAnimation *chalkyToRemove);
    void gameLoop();
    
    void ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
	void ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
    virtual void update(float dt);
    
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyBlue, ChalkyBlue);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyYellow, ChalkyYellow);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalkyRed, ChalkyRed);

    void updateChalkyIndex(int chalky);
    void removeChalkyBlue();
    void removeChalkyYellow();
    void removeChalkyRed();
    
    void checkGameEnd1(float chalkyPosition);
    void checkGameEnd2(float chalkyPosition);
    void checkGameEnd3(float chalkyPosition);
    
    bool useChalkForChalkie(CCSkeletonAnimation * chalky);
    void gameEnd();
    
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
};


#endif /* defined(__Chalky__GamePlayScene__) */
