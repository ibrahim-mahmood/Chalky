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
    void addBarsForLevel(float level);
    void addChalkyForLevel(float level);
    bool init();
    void hideTileForBar(Duster* duster);
    
    CC_SYNTHESIZE_RETAIN(CCArray *, levelBars1, LevelBars1);
    CC_SYNTHESIZE_RETAIN(CCArray *, levelBars2, LevelBars2);
    CC_SYNTHESIZE_RETAIN(CCArray *, levelBars3, LevelBars3);
    
    int barWidth;
    int barHeight;
    
    void startGameForLevel(float levelNo);
    void stopLoop();
    void playChalkyLoseAnimation(CCSkeletonAnimation *chalkie);
    void gameLoop();
    
    void ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
	void ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event);
    virtual void update(float dt);
    
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalky1, Chalky1);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalky2, Chalky2);
    CC_SYNTHESIZE_RETAIN(CCSkeletonAnimation*, chalky3, Chalky3);

    void updateChalkyIndex(int chalky);
    void removeChalky1();
    void removeChalky2();
    void removeChalky3();
    
    void checkGameEnd1(float chalkyPosition);
    void checkGameEnd2(float chalkyPosition);
    void checkGameEnd3(float chalkyPosition);
    
    bool useChalkForChalkie(CCSkeletonAnimation * chalkie);
    void gameEnd();
    void hideChalkie1();
    void hideChalkie2();
    void hideChalkie3();
    
    bool chalky1Special;
    bool chalky2Special;
    bool chalky3Special;
    
    void addChalkiesRandomly();
    int startTag;
    int currentGameLevel;
    
    void goToHighScoreEndScreen();
    void goToLevelEndScreen(bool levelCleared);
};


#endif /* defined(__Chalky__GamePlayScene__) */
