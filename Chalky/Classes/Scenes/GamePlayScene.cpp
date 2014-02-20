//
//  GamePlayScene.cpp
//  Chalky
//
//  Created by Ibrahim on 9/20/13.
//
//

#include "GamePlayScene.h"
#include "Bar.h"
#include "Duster.h"
#include "Chalky.h"
#include "HighScoreEnd.h"
#include "LevelEndScreen.h"
#include "Constants.h"


#pragma mark - Initializations
GamePlayScene::GamePlayScene()
{
    levelBars1 = NULL;
    levelBars2 = NULL;
    levelBars3 = NULL;
    chalky1 = NULL;
    chalky2 = NULL;
    chalky3 = NULL;
}

GamePlayScene::~GamePlayScene()
{
    CC_SAFE_RELEASE_NULL(levelBars1);
    CC_SAFE_RELEASE_NULL(levelBars2);
    CC_SAFE_RELEASE_NULL(levelBars3);

    CC_SAFE_RELEASE_NULL(chalky1);
    CC_SAFE_RELEASE_NULL(chalky2);
    CC_SAFE_RELEASE_NULL(chalky3);

}

bool GamePlayScene::init()
{
    this->setTouchEnabled(true);
    return true;
}

void GamePlayScene::onEnter()
{
    CCLayer::onEnter();
    CHALKY_MANAGER->loadGameData();
    CHALKY_MANAGER->lastScore = 0;
    
    chalky1Special = false;
    chalky2Special = false;
    chalky3Special = false;
    
    currentGameLevel = CHALKY_MANAGER->currentLevel;
    if (CHALKY_MANAGER->getGameMode() == kModeHS) {
        currentGameLevel = 3;
        startTag = 0;
    }
    this->setLevelBars1(CCArray::create());
    if(currentGameLevel >= 2)
        this->setLevelBars2(CCArray::create());
    if(currentGameLevel >= 3)
        this->setLevelBars3(CCArray::create());
    addLayerAssets();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GamePlayScene::hideTileForBar), TILE_REMOVED_NOTIFICATION, NULL);
}

void GamePlayScene::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CCLayer::onExit();
    removeAllChildrenWithCleanup(true);
}

CCScene* GamePlayScene::scene()
{
	CCScene *scene = CCScene::create();
    scene->addChild(this);
	return scene;
}

#pragma mark - Add Assets

void GamePlayScene::addLayerAssets()
{
    srand (time(NULL));
    addBackground();
    addBarsForLevel(currentGameLevel);
    startGameForLevel(currentGameLevel);
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        for(int i= (int)currentGameLevel > 3 ? 3:(int)currentGameLevel ; i > 0; i--)
        {
            addChalkyForLevel(i);
        }
        
        this->scheduleUpdate();
    }
    else {
        addChalkiesRandomly();
    }
}
void GamePlayScene::hideTileForBar(Duster * duster)
{
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        switch (duster->dusterColor) {
            case 0:
            {
                if (CHALKY_MANAGER->indexToHide1 == CHALKY_MANAGER->chalky1Index) {
                    
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHide1);
                    if (b) {
                        if (b->isVisible()) {
                            b->setVisible(false);
                        }
                    }
                }
            }
                break;
            case 1:
            {
                if (CHALKY_MANAGER->indexToHide2 == CHALKY_MANAGER->chalky2Index) {
                    
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHide2 + BAR_TAG_2);
                    if (b) {
                        if (b->isVisible()) {
                            b->setVisible(false);
                        }
                    }
                }
            }
                break;
            case 2:
            {
                if (CHALKY_MANAGER->indexToHide3 == CHALKY_MANAGER->chalky3Index) {
                    
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHide3 + BAR_TAG_3);
                    if (b) {
                        if (b->isVisible()) {
                            b->setVisible(false);
                        }
                    }
                }
            }
                break;
            default:
                break;
        }
    }
    else {
        switch (duster->dusterColor) {
            case 0:
            {
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideSpecial);
                if (b) {
                    if (b->isVisible()) {
                        b->setVisible(false);
                    }
                }
            }
                break;
            case 1:
            {
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideSpecial + BAR_TAG_2);
                if (b) {
                    if (b->isVisible()) {
                        b->setVisible(false);
                    }
                }
            }
                break;
            case 2:
            {
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideSpecial + BAR_TAG_3);
                if (b) {
                    if (b->isVisible()) {
                        b->setVisible(false);
                    }
                }
            }
                break;
            default:
                break;
        }
    }
}

void GamePlayScene::addBackground()
{
    CCSprite *background = CCSprite::create(GAME_BACKGROUND);
    background->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(background);
    
    CCSprite *progressBarBack = CCSprite::create("chalky-progress-bar.png");
    progressBarBack->setPosition(ccp(0, WIN_HEIGHT));
    this->addChild(progressBarBack);
    progressBarBack->setAnchorPoint(ccp(0,1));
}

void GamePlayScene::addChalkyForLevel(float level)
{
    int randomNumber = rand() % 10 + 1;
    if (randomNumber/10 > CHALKY_MANAGER->getFloatValueForKey(SPECIAL_PROBABILITY_KEY)) {
        int randNumber = rand() % 3 + 1;
        if (randNumber == 1) {
            chalky1Special = true;
        }
        else if (randNumber == 2) {
            chalky2Special = true;
        }
        else {
            chalky3Special = true;
        }
    }
    int levelNumber = (int)level;
    switch (levelNumber) {
        case 5:
        case 4:
        case 3:
        {
            chalky3 = NULL;
            this->setChalky3(CCSkeletonAnimation::createWithFile("chalky.json", "chalky.atlas"));
            chalky3->setAnimation(RIDE_ANIMATION_NAME, true);
            chalky3->setPosition(ccp(0.0,CHALKY_MANAGER->bar3Height));
            chalky3->setAnchorPoint(ccp(0.5,0));
            chalky3->setScale(0.5);
            if (chalky3Special)
                chalky3->setColor(ccc3(244, 0, 7));
            this->addChild(chalky3);
            
            CCSprite *red= CCSprite::create("chalky-red-chalk.png");
            red->setPosition(ccp(WIN_WIDTH/3.5, 0));
            this->addChild(red);
            red->setAnchorPoint(ccp(0.5,0));
        }
            break;
        case 2:
        {
            chalky2 = NULL;
            this->setChalky2(CCSkeletonAnimation::createWithFile("chalky.json", "chalky.atlas"));
            chalky2->setAnimation(RIDE_ANIMATION_NAME, true);
            chalky2->setPosition(ccp(0.0,CHALKY_MANAGER->bar2Height));
            chalky2->setAnchorPoint(ccp(0.5,0));
            chalky2->setScale(0.5);
            if (chalky2Special)
                chalky2->setColor(ccc3(252, 198, 8));
            this->addChild(chalky2);
            
            CCSprite *yellow = CCSprite::create("chalky-yellow-chalk.png");
            yellow->setPosition(ccp(WIN_WIDTH/2.5, 0));
            this->addChild(yellow);
            yellow->setAnchorPoint(ccp(0.5,0));
            
        }
            break;
        case 1:
        {
            chalky1 = NULL;
            this->setChalky1(CCSkeletonAnimation::createWithFile("chalky.json", "chalky.atlas"));
            chalky1->setAnimation(RIDE_ANIMATION_NAME, true);
            chalky1->setPosition(ccp(0.0,CHALKY_MANAGER->bar1Height));
            chalky1->setAnchorPoint(ccp(0.5,0));
            chalky1->setScale(0.5);
            if (chalky1Special)
                chalky1->setColor(ccc3(45, 196, 255));
            this->addChild(chalky1,10);
            
            CCSprite *blueChalk = CCSprite::create("chalky-blue-chalk.png");
            blueChalk->setPosition(ccp(WIN_WIDTH/1.5, 0));
            this->addChild(blueChalk);
            blueChalk->setAnchorPoint(ccp(0.5,0));
            
        }
        default:
            break;
    }
    
}

void GamePlayScene::addChalkiesRandomly()
{
    bool isSpecial = false;
    int rNumber = rand() % 10 + 1;
    if (rNumber/10 > CHALKY_MANAGER->getFloatValueForKey(SPECIAL_PROBABILITY_KEY)) {
        isSpecial = true;
    }
    
    int randomNumber = rand() % 3 + 1;
    Chalky *chalky = Chalky::create("chalky.json", "chalky.atlas");
    chalky->setAnchorPoint(ccp(0.5,0));
    chalky->setScale(0.5);
    chalky->type = kChalkyNormal;
    
    if (randomNumber == 1) {
        chalky->col = kChalkyBlue;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->bar1Height));
        if (isSpecial) {
            chalky->type = kChalkySpecial;
            chalky->setChalkyColor(ccc3(45, 196, 255));
        }
    }
    else if (randomNumber == 2) {
        chalky->col = kChalkyYellow;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->bar2Height));
        if (isSpecial) {
            chalky->type = kChalkySpecial;
            chalky->setChalkyColor(ccc3(252, 198, 8));
        }
    }
    else {
        chalky->col = kChalkyRed;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->bar3Height));
        if (isSpecial) {
            chalky->type = kChalkySpecial;
            chalky->setChalkyColor(ccc3(244, 0, 7));
        }
    }
    this->addChild(chalky, startTag);
    
    chalky->startChalkyUpdate();
    chalky->playRunningAnimation();
}

void GamePlayScene::addBarsForLevel(float level)
{
    CCSprite *normalSprite = NULL;
    CCSprite *selectedSprite = NULL;
    int levelNumber = (int)currentGameLevel;
    if(currentGameLevel >=3)
        levelNumber = 3;
    switch (levelNumber)
    {
        case 5:
        case 4:
        case 3:
        {
            float x = 0.0;
            float y = CHALKY_MANAGER->bar3Height;
            normalSprite = CCSprite::create("red_0.png");
            
            for (int i = 0; i <11; i++)
            {
                normalSprite = NULL;
                CCString * name = CCString::createWithFormat("red_%d.png",i);
                normalSprite = CCSprite::create(name->getCString());
                selectedSprite = CCSprite::create("red_0.png");
                float increment = 0.0;
                Bar *b = Bar::create(normalSprite, selectedSprite);
                b->setBarColor(kDusterBlue);
                b->setAnchorPoint(ccp(0.0, 0.5));
                b->setPosition(x, y);
                b->setTag(BAR_TAG_3+i);
                b->setEnabled(true);
                this->addChild(b);
                levelBars3->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-red.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->bar3Height));
            this->addChild(portal,BAR_TAG_3);

        }
        case 2:
        {
            float x = 0.0;
            float y = CHALKY_MANAGER->bar2Height;
            normalSprite = CCSprite::create("yellow_0.png");
            
            for (int i = 0; i <11; i++)
            {
                normalSprite = NULL;
                CCString * name = CCString::createWithFormat("yellow_%d.png",i);
                normalSprite = CCSprite::create(name->getCString());
                selectedSprite = CCSprite::create("yellow_0.png");
                float increment = 0.0;
                Bar *b = Bar::create(normalSprite, selectedSprite);
                b->setBarColor(kDusterYellow);
                b->setAnchorPoint(ccp(0.0, 0.5));
                b->setPosition(x, y);
                b->setTag(BAR_TAG_2+i);
                b->setEnabled(true);
                this->addChild(b);
                levelBars2->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-yellow.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->bar2Height));
            this->addChild(portal,BAR_TAG_3);

        }
        case 1:
        {
            float x = 0.0;
            float y = CHALKY_MANAGER->bar1Height;
            normalSprite = CCSprite::create("blue_0.png");
            
            for (int i = 0; i <11; i++)
            {
                normalSprite = NULL;
                CCString * name = CCString::createWithFormat("blue_%d.png",i);
                normalSprite = CCSprite::create(name->getCString());
                selectedSprite = CCSprite::create("blue_0.png");
                float increment = 0.0;
                Bar *b = Bar::create(normalSprite, selectedSprite);
                b->setBarColor(kDusterRed);
                b->setAnchorPoint(ccp(0.0, 0.5));
                b->setPosition(x, y);
                b->setTag(i);
                b->setEnabled(true);
                this->addChild(b);
                levelBars1->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-blue.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->bar1Height));
            this->addChild(portal,BAR_TAG_3);
        }
        break;
        default:
            break;
    }
    
    CHALKY_MANAGER->totalSteps = levelBars1->count();
    CHALKY_MANAGER->barWidth = barWidth;
        
}

#pragma mark - Screen Touch Events

void GamePlayScene::ccTouchesBegan(CCSet *touches, CCEvent *event)
{
    
}
void GamePlayScene::ccTouchesEnded(CCSet *touches, CCEvent* event) {
    
    // Choose one of the touches to work with
	CCTouch *touch = (CCTouch *)(touches->anyObject());
    CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    int tag = 0;
    if ((touchPoint.y >= CHALKY_MANAGER->bar1Height && touchPoint.y < (CHALKY_MANAGER->bar1Height + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->bar1Height && touchPoint.y > (CHALKY_MANAGER->bar1Height - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
    }
    
    else if ((touchPoint.y >= CHALKY_MANAGER->bar2Height && touchPoint.y < (CHALKY_MANAGER->bar2Height + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->bar2Height && touchPoint.y > (CHALKY_MANAGER->bar2Height - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
        tag = (BAR_TAG_2+tag);
    }
    else if ((touchPoint.y >= CHALKY_MANAGER->bar3Height && touchPoint.y < (CHALKY_MANAGER->bar3Height + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->bar3Height && touchPoint.y > (CHALKY_MANAGER->bar3Height - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
        tag = (BAR_TAG_3+tag);
    }


    CCLog("BAR TAG IS : %i", tag);
    Bar *b = (Bar*)this->getChildByTag(tag);
    if (b) {
        if (!b->isVisible())
            b->setVisible(true);
    }
}

void GamePlayScene::startGameForLevel(float levelNo)
{
    float interval = CHALKY_MANAGER->getFloatValueForKey(levelNo, DUSTER_SPEED_KEY);
    this->schedule(schedule_selector(GamePlayScene::gameLoop), interval);
    if (CHALKY_MANAGER->getGameMode() == kModeHS) {
        this->schedule(schedule_selector(GamePlayScene::addChalkiesRandomly), CHALKY_MANAGER->getFloatValueForKey(CHALKY_INTERVAL_KEY));
        this->schedule(schedule_selector(GamePlayScene::goToHighScoreEndScreen), 0, 0, CHALKY_MANAGER->getFloatValueForKey(HS_DURATION_KEY));
    }
    else {
        this->schedule(schedule_selector(GamePlayScene::goToHighScoreEndScreen), 0, 0, CHALKY_MANAGER->getFloatValueForKey(NORMAL_DURATION_KEY));
    }
}

#pragma mark - Screen Change Methods

void GamePlayScene::goToHighScoreEndScreen()
{
    HighScoreEnd *pScene = HighScoreEnd::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void GamePlayScene::goToLevelEndScreen(bool levelCleared)
{
    LevelEndScreen *pScene = LevelEndScreen::create(levelCleared);
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}


#pragma mark - Game Loop

void GamePlayScene::gameLoop()
{
    CHALKY_MANAGER->indexToHide3 = 0;
    CHALKY_MANAGER->indexToHide2 = 0;
    CHALKY_MANAGER->indexToHide1 = 0;
    
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        switch ((int)currentGameLevel) {
            case 5:
            case 4:
            case 3:
            {
                //rand()%(max-min + 1) + min;
                
                int chalky3Position = CHALKY_MANAGER->chalky3Index;
                int randomIndex = rand()%(levelBars3->count() - chalky3Position) + chalky3Position;
                //int randomIndex = rand()%(levelBars3->count());
                CHALKY_MANAGER->indexToHide3 = randomIndex;
                
            }
            case 2:
            {
                int chalky2Position = CHALKY_MANAGER->chalky2Index;
                int randomIndex = rand()%(levelBars2->count() - chalky2Position) + chalky2Position;
                //int randomIndex = rand()%(levelBars2->count());
                CHALKY_MANAGER->indexToHide2 = randomIndex;
            }
            case 1:
            {
                int chalky1Position = CHALKY_MANAGER->chalky1Index;
                int randomIndex = rand()%(levelBars1->count() - chalky1Position) + chalky1Position;
                //int randomIndex = rand()%(levelBars1->count());
                CHALKY_MANAGER->indexToHide1 = randomIndex;
            }
                
            default:
                break;
        }
    }
    else {
        int randomIndex = rand()%(levelBars1->count());
        CHALKY_MANAGER->indexToHideSpecial = randomIndex;
    }
    
    kDusterColor col;
    
    if (currentGameLevel == 1) {
        col = kDusterBlue;
    }
    else if (currentGameLevel == 2) {
        int randomNumber = rand() % 2 + 1;
        if (randomNumber == 1) {
            col = kDusterBlue;
        }
        else if (randomNumber == 2) {
            col = kDusterYellow;
        }
    }
    else {
        int randomNumber = rand() % 3 + 1;
        if (randomNumber == 1) {
            col = kDusterBlue;
        }
        else if (randomNumber == 2) {
            col = kDusterYellow;
        }
        else if (randomNumber == 3) {
            col = kDusterRed;
        }
        else {
            CCLog("INVALID");
        }
    }
    
    Duster * devil = Duster::create("duster.png", col);
    this->addChild(devil,10);
}

void GamePlayScene::update(float dt)
{
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        if(chalky1)
        {
            float oldChalkyPosition = chalky1->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(1, CHALKY_SPEED_KEY) * dt);
            chalky1->setPosition(ccp(newChalkyPosition, chalky1->getPositionY()));
            checkGameEnd1(newChalkyPosition);
        }
        if (chalky2)
        {
            float oldChalkyPosition = chalky2->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(2, CHALKY_SPEED_KEY) * dt);
            chalky2->setPosition(ccp(newChalkyPosition, chalky2->getPositionY()));
            checkGameEnd2(newChalkyPosition);
        }
        if(chalky3)
        {
            float oldChalkyPosition = chalky3->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(3, CHALKY_SPEED_KEY) * dt);
            chalky3->setPosition(ccp(newChalkyPosition, chalky3->getPositionY()));
            checkGameEnd3(newChalkyPosition);
        }
        
        if (CHALKY_MANAGER->lastScore >= CHALKY_MANAGER->getFloatValueForKey(currentGameLevel, LEVEL_TARGET_KEY)) {
            goToLevelEndScreen(true);
        }
    }
}

void GamePlayScene::updateChalkyIndex(int chalky)
{
    CHALKY_MANAGER->chalky1Index++;
}

void GamePlayScene::stopLoop()
{
    this->unscheduleUpdate();
    this->unschedule(schedule_selector(GamePlayScene::gameLoop));
}

#pragma mark - Game End Conditions

void GamePlayScene::checkGameEnd1(float chalkyPosition)
{
    if (CHALKY_MANAGER->chalky1Index >= levelBars1->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalky1Special);
        chalky1Special = false;
        chalky1->removeFromParentAndCleanup(true);
        chalky1 = NULL;
    }
    else {
        int tag = 0;
        tag = chalkyPosition / barWidth;
        CHALKY_MANAGER->chalky1Index = tag;
        CCLog("BAR TAG IS : %i", tag);
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                //GAME LOSE CONDITION
                if(!chalky2 && !chalky3)
                    gameEnd();
                playChalkyLoseAnimation(chalky1);
            }
        }
    }
}
void GamePlayScene::checkGameEnd2(float chalkyPosition)
{
    if (CHALKY_MANAGER->chalky2Index >= levelBars2->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalky2Special);
        chalky2Special = false;
        chalky2->removeFromParentAndCleanup(true);
        chalky2 = NULL;
    }
    else {
        int tag = 0;
        int index = 0;
        index = chalkyPosition / barWidth;
        tag = (BAR_TAG_2 + index);
        CHALKY_MANAGER->chalky2Index = index;
        CCLog("BAR TAG IS : %i", tag);
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                //GAME LOSE CONDITION
                if(!chalky1 && !chalky3)
                    gameEnd();
                playChalkyLoseAnimation(chalky2);
            }
        }
    }
}
void GamePlayScene::checkGameEnd3(float chalkyPosition)
{
    if (CHALKY_MANAGER->chalky3Index >= levelBars3->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalky3Special);
        chalky3Special = false;
        chalky3->removeFromParentAndCleanup(true);
        chalky3=NULL;
    }
    else {
        int tag = 0;
        int index = 0;
        index = chalkyPosition / barWidth;
        tag = (BAR_TAG_3 + index);
        CHALKY_MANAGER->chalky3Index = index;
        CCLog("BAR TAG IS : %i", tag);
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                //GAME LOSE CONDITION
                if(!chalky1 && !chalky2)
                    gameEnd();
                playChalkyLoseAnimation(chalky3);
            }
        }
    }
}

void GamePlayScene::playChalkyLoseAnimation(CCSkeletonAnimation *chalky)
{
    //GAME LOSE CONDITION
    int chalky1Position = 0;
    if (chalky == chalky1) {
        chalky1Position = CHALKY_MANAGER->chalky1Index;
    }
    else if (chalky == chalky2)
    {
        chalky1Position = CHALKY_MANAGER->chalky2Index;
    }
    else if (chalky == chalky3)
    {
        chalky1Position = CHALKY_MANAGER->chalky3Index;
    }
    Bar *b = (Bar*)this->getChildByTag(chalky1Position);
    float currentPositionX = b->getPositionX();
    float currentPositionY = b->getPositionY();
    float barSize = b->getContentSize().width / 2;
    float newPositionX = currentPositionX + barSize;
    float newPositionY = currentPositionY - BAR_TAG_3;
    
    CCDelayTime *delay = CCDelayTime::create(0.5);
    if (chalky == chalky1) {
        chalky->addAnimation("Falling", false);
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalky1));
        CCSequence *seq = CCSequence::create(delay, call, NULL);
        chalky->runAction(seq);
    }
    else if (chalky == chalky2)
    {
        chalky->addAnimation("Falling", false);
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalky2));
        CCSequence *seq = CCSequence::create(delay, call, NULL);
        chalky->runAction(seq);
    }
    else if (chalky == chalky3)
    {
        chalky->addAnimation("Falling", false);
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalky3));
        CCSequence *seq = CCSequence::create(delay, call, NULL);
        chalky->runAction(seq);
    }

}

void GamePlayScene::removeChalky1()
{
    chalky1Special = false;
    CHALKY_MANAGER->chalky1Index = 0;
    chalky1->stopAllActions();
    chalky1->removeFromParentAndCleanup(true);
    chalky1 = NULL;
    if(useChalkForChalkie(chalky1))
    {
        addChalkyForLevel(1);
    }
}
void GamePlayScene::removeChalky2()
{
    chalky2Special = false;
    CHALKY_MANAGER->chalky2Index = BAR_TAG_2;
    chalky2->setVisible(false);
    chalky2->stopAllActions();
    chalky2->removeFromParentAndCleanup(true);
    chalky2 = NULL;

    if(useChalkForChalkie(chalky2))
    {
        addChalkyForLevel(2);
    }

}

void GamePlayScene::hideChalkie1()
{
    chalky1->setVisible(false);
}
void GamePlayScene::hideChalkie2()
{
    chalky2->setVisible(false);
}
void GamePlayScene::hideChalkie3()
{
    chalky3->setVisible(false);
}

void GamePlayScene::removeChalky3()
{
    chalky3Special = false;
    CHALKY_MANAGER->chalky3Index = BAR_TAG_3;
    chalky3->setVisible(false);
    chalky3->stopAllActions();
    chalky3->removeFromParentAndCleanup(true);
    chalky3 = NULL;
    if(useChalkForChalkie(chalky3))
    {
        addChalkyForLevel(3);
    }
    
}

bool GamePlayScene::useChalkForChalkie(CCSkeletonAnimation * chalkie)
{
    if (chalky1 == chalkie) {
        if (CHALKY_MANAGER->blueChalks>=0) {
            CHALKY_MANAGER->blueChalks-=1;
            return true;
        }
    }
    else if (chalky2 == chalkie) {
        if (CHALKY_MANAGER->yellowChalks>=0) {
            CHALKY_MANAGER->yellowChalks-=1;
            return true;
        }
    }
    else if (chalky3 == chalkie) {
        if (CHALKY_MANAGER->redChalks>=0) {
            CHALKY_MANAGER->redChalks-=1;
            return true;
        }
    }
    return false;
}
void GamePlayScene::gameEnd()
{
    
}
