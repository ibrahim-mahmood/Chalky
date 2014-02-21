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

#define TIME_REMAINING_STRING   "You have %d seconds"

#pragma mark - Initializations
GamePlayScene::GamePlayScene()
{
    barsBlue = NULL;
    barsYellow = NULL;
    barsRed = NULL;
    chalkyBlue = NULL;
    chalkyYellow = NULL;
    chalkyRed = NULL;
    timerLabel = NULL;
    currentGameLevel = 0;
    totalTimePlayed = 0.0f;
    previousTimeCount = 0;
}

GamePlayScene::~GamePlayScene()
{
    CC_SAFE_RELEASE_NULL(barsBlue);
    CC_SAFE_RELEASE_NULL(barsYellow);
    CC_SAFE_RELEASE_NULL(barsRed);

    CC_SAFE_RELEASE_NULL(chalkyBlue);
    CC_SAFE_RELEASE_NULL(chalkyYellow);
    CC_SAFE_RELEASE_NULL(chalkyRed);
}

bool GamePlayScene::init()
{
    this->setTouchEnabled(true);
    return true;
}

void GamePlayScene::onEnter()
{
    CCLayer::onEnter();
    
    setupGameElements();
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
    addLabels();
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

void GamePlayScene::setupGameElements()
{
    CHALKY_MANAGER->resetGameState();
    CHALKY_MANAGER->loadGameData();
    
    chalkySpecialBlue = false;
    chalkySpecialYellow = false;
    chalkySpecialRed = false;
    
    currentGameLevel = CHALKY_MANAGER->currentLevel;
    countdownTimer = CHALKY_MANAGER->getFloatValueForKey(NORMAL_DURATION_KEY);
    if (CHALKY_MANAGER->getGameMode() == kModeHS) {
        currentGameLevel = 3;
        startTag = 0;
        countdownTimer = CHALKY_MANAGER->getFloatValueForKey(HS_DURATION_KEY);
    }
    this->setBarsBlue(CCArray::create());
    if(currentGameLevel >= 2)
        this->setBarsYellow(CCArray::create());
    if(currentGameLevel >= 3)
        this->setbarsRed(CCArray::create());
}

void GamePlayScene::hideTileForBar(Duster * duster)
{
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        switch (duster->dusterColor) {
            case 0:
            {
                if (CHALKY_MANAGER->blueBarToHide == CHALKY_MANAGER->blueChalkyPosition) {
                    //DO NOT REMOVE LINE IF CHALKY HAS ALREADY REACHED IT
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->blueBarToHide);
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
                if (CHALKY_MANAGER->yellowBarToHide == CHALKY_MANAGER->yellowChalkyPosition) {
                    //DO NOT REMOVE LINE IF CHALKY HAS ALREADY REACHED IT
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->yellowBarToHide + BAR_TAG_YELLOW);
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
                if (CHALKY_MANAGER->redBarToHide == CHALKY_MANAGER->redChalkyPosition) {
                    //DO NOT REMOVE LINE IF CHALKY HAS ALREADY REACHED IT
                }
                else {
                    Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->redBarToHide + BAR_TAG_RED);
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
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideHSMode);
                if (b) {
                    if (b->isVisible()) {
                        b->setVisible(false);
                    }
                }
            }
                break;
            case 1:
            {
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideHSMode + BAR_TAG_YELLOW);
                if (b) {
                    if (b->isVisible()) {
                        b->setVisible(false);
                    }
                }
            }
                break;
            case 2:
            {
                Bar *b = (Bar*)this->getChildByTag(CHALKY_MANAGER->indexToHideHSMode + BAR_TAG_RED);
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
    
}

void GamePlayScene::addLabels()
{
    CCLabelTTF *titleLabel;
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        titleLabel = CCLabelTTF::create(CHALKY_MANAGER->getStringForKey(NORMAL_DESCRIPTION_KEY).c_str(), CHALKY_FONT, CHALKY_FONT_SIZE);
        
        CCLabelTTF *targetLabel = CCLabelTTF::create(CCString::createWithFormat("TARGET %d", (int)CHALKY_MANAGER->getFloatValueForKey(currentGameLevel, LEVEL_TARGET_KEY))->getCString(), CHALKY_FONT, CHALKY_FONT_SIZE);
        targetLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.875));
        this->addChild(targetLabel);
    }
    else {
        titleLabel = CCLabelTTF::create(CHALKY_MANAGER->getStringForKey(HS_DESCRIPTION_KEY).c_str(), CHALKY_FONT, CHALKY_FONT_SIZE);
    }
    titleLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.975));
    this->addChild(titleLabel);
    
    
    timerLabel = CCLabelTTF::create(CCString::createWithFormat(TIME_REMAINING_STRING, countdownTimer)->getCString(), CHALKY_FONT, CHALKY_FONT_SIZE);
    timerLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.925));
    this->addChild(timerLabel);
    
    CCLabelTTF *detailsLabel = CCLabelTTF::create("Each Chalky gives 5 Points. Colored Chalkies are worth 10", CHALKY_FONT, CHALKY_FONT_SIZE);
    detailsLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.10));
    this->addChild(detailsLabel);
    
}

void GamePlayScene::setSpecialChalkyStatus()
{
    int randomNumber = rand() % 10 + 1;
    if (randomNumber/10 > CHALKY_MANAGER->getFloatValueForKey(SPECIAL_PROBABILITY_KEY)) {
        int randNumber = rand() % 3 + 1;
        if (randNumber == 1) {
            chalkySpecialBlue = true;
        }
        else if (randNumber == 2) {
            chalkySpecialYellow = true;
        }
        else {
            chalkySpecialRed = true;
        }
    }
}

void GamePlayScene::addChalkyForLevel(float level)
{
    setSpecialChalkyStatus();
    int levelNumber = (int)level;
    switch (levelNumber) {
        case 5:
        case 4:
        case 3:
        {
            chalkyRed = NULL;
            this->setChalkyRed(CCSkeletonAnimation::createWithFile(CHALKY_ANIMATION_JSON, CHALKY_ANIMATION_ATLAS));
            chalkyRed->setAnimation(RIDE_ANIMATION_NAME, true);
            chalkyRed->setPosition(ccp(0.0,CHALKY_MANAGER->redBarHeight));
            chalkyRed->setAnchorPoint(ccp(0.5,0));
            chalkyRed->setScale(0.5);
            if (chalkySpecialRed)
                chalkyRed->setColor(ccc3(244, 0, 7));
            this->addChild(chalkyRed);
        }
            break;
        case 2:
        {
            chalkyYellow = NULL;
            this->setChalkyYellow(CCSkeletonAnimation::createWithFile(CHALKY_ANIMATION_JSON, CHALKY_ANIMATION_ATLAS));
            chalkyYellow->setAnimation(RIDE_ANIMATION_NAME, true);
            chalkyYellow->setPosition(ccp(0.0,CHALKY_MANAGER->yellowBarHeight));
            chalkyYellow->setAnchorPoint(ccp(0.5,0));
            chalkyYellow->setScale(0.5);
            if (chalkySpecialYellow)
                chalkyYellow->setColor(ccc3(252, 198, 8));
            this->addChild(chalkyYellow);
            
        }
            break;
        case 1:
        {
            chalkyBlue = NULL;
            this->setChalkyBlue(CCSkeletonAnimation::createWithFile(CHALKY_ANIMATION_JSON, CHALKY_ANIMATION_ATLAS));
            chalkyBlue->setAnimation(RIDE_ANIMATION_NAME, true);
            chalkyBlue->setPosition(ccp(0.0,CHALKY_MANAGER->blueBarHeight));
            chalkyBlue->setAnchorPoint(ccp(0.5,0));
            chalkyBlue->setScale(0.5);
            if (chalkySpecialBlue)
                chalkyBlue->setColor(ccc3(45, 196, 255));
            this->addChild(chalkyBlue,10);
            
        }
            break;
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
    Chalky *chalky = Chalky::create(CHALKY_ANIMATION_JSON, CHALKY_ANIMATION_ATLAS);
    chalky->setAnchorPoint(ccp(0.5,0));
    chalky->setScale(0.5);
    chalky->type = kChalkyNormal;
    
    if (randomNumber == 1) {
        chalky->col = kChalkyBlue;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->blueBarHeight));
        if (isSpecial) {
            chalky->type = kChalkySpecial;
            chalky->setChalkyColor(ccc3(45, 196, 255));
        }
    }
    else if (randomNumber == 2) {
        chalky->col = kChalkyYellow;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->yellowBarHeight));
        if (isSpecial) {
            chalky->type = kChalkySpecial;
            chalky->setChalkyColor(ccc3(252, 198, 8));
        }
    }
    else {
        chalky->col = kChalkyRed;
        chalky->setPosition(ccp(0.0,CHALKY_MANAGER->redBarHeight));
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
            float y = CHALKY_MANAGER->redBarHeight;
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
                b->setTag(BAR_TAG_RED + i);
                b->setEnabled(true);
                this->addChild(b);
                barsRed->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-red.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->redBarHeight));
            this->addChild(portal,BAR_TAG_RED);

        }
        case 2:
        {
            float x = 0.0;
            float y = CHALKY_MANAGER->yellowBarHeight;
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
                b->setTag(BAR_TAG_YELLOW + i);
                b->setEnabled(true);
                this->addChild(b);
                barsYellow->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-yellow.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->yellowBarHeight));
            this->addChild(portal,BAR_TAG_RED);

        }
        case 1:
        {
            float x = 0.0;
            float y = CHALKY_MANAGER->blueBarHeight;
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
                barsBlue->addObject(b);
                
                CCSize barSize = b->getContentSize();
                increment = barSize.width;
                barWidth = barSize.width;
                barHeight = barSize.height;
                x += increment;
            }
            CCSprite *portal = CCSprite::create("chalky-portal-blue.png");
            portal->setAnchorPoint(ccp(1,0.2));
            portal->setPosition(ccp(WIN_WIDTH,CHALKY_MANAGER->blueBarHeight));
            this->addChild(portal,BAR_TAG_RED);
        }
        break;
        default:
            break;
    }
    
    CHALKY_MANAGER->totalSteps = barsBlue->count();
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
    if ((touchPoint.y >= CHALKY_MANAGER->blueBarHeight && touchPoint.y < (CHALKY_MANAGER->blueBarHeight + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->blueBarHeight && touchPoint.y > (CHALKY_MANAGER->blueBarHeight - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
    }
    
    else if ((touchPoint.y >= CHALKY_MANAGER->yellowBarHeight && touchPoint.y < (CHALKY_MANAGER->yellowBarHeight + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->yellowBarHeight && touchPoint.y > (CHALKY_MANAGER->yellowBarHeight - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
        tag = (BAR_TAG_YELLOW + tag);
    }
    else if ((touchPoint.y >= CHALKY_MANAGER->redBarHeight && touchPoint.y < (CHALKY_MANAGER->redBarHeight + barHeight + 10)) || (touchPoint.y <= CHALKY_MANAGER->redBarHeight && touchPoint.y > (CHALKY_MANAGER->redBarHeight - barHeight - 10))) {
        tag = touchPoint.x/barWidth;
        tag = (BAR_TAG_RED + tag);
    }


    Bar *b = (Bar*)this->getChildByTag(tag);
    if (b) {
        if (!b->isVisible())
            b->setVisible(true);
    }
}

#pragma mark - Screen Change Methods

void GamePlayScene::goToHighScoreEndScreen()
{
    HighScoreEnd *pScene = HighScoreEnd::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void GamePlayScene::goToLevelWinScreen()
{
    LevelEndScreen *pScene = LevelEndScreen::create(true);
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void GamePlayScene::goToLevelLoseScreen()
{
    LevelEndScreen *pScene = LevelEndScreen::create(false);
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

#pragma mark - Game Loop

void GamePlayScene::startGameForLevel(float levelNo)
{
    float interval = CHALKY_MANAGER->getFloatValueForKey(levelNo, DUSTER_SPEED_KEY);
    this->schedule(schedule_selector(GamePlayScene::gameLoop), interval);
    if (CHALKY_MANAGER->getGameMode() == kModeHS) {
        this->schedule(schedule_selector(GamePlayScene::addChalkiesRandomly), CHALKY_MANAGER->getFloatValueForKey(CHALKY_INTERVAL_KEY));
        this->schedule(schedule_selector(GamePlayScene::goToHighScoreEndScreen), 0, 0, CHALKY_MANAGER->getFloatValueForKey(HS_DURATION_KEY));
    }
    else {
        this->schedule(schedule_selector(GamePlayScene::goToLevelLoseScreen), 0, 0, CHALKY_MANAGER->getFloatValueForKey(NORMAL_DURATION_KEY));
    }
}

void GamePlayScene::gameLoop()
{
    CHALKY_MANAGER->redBarToHide = 0;
    CHALKY_MANAGER->yellowBarToHide = 0;
    CHALKY_MANAGER->blueBarToHide = 0;
    
    //calculate which bar the duster will remove
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        switch ((int)currentGameLevel) {
            case 5:
            case 4:
            case 3:
            {
                int redPosition = CHALKY_MANAGER->redChalkyPosition;
                int randomIndex;
                if (redPosition < MAX_INDEX_TO_REMOVE)
                    randomIndex = rand()%(barsRed->count() - redPosition) + redPosition;
                else
                    randomIndex = CCRANDOM_0_1() * 2;
                
                if (randomIndex == redPosition)
                    randomIndex++;
                if (randomIndex > MAX_INDEX_TO_REMOVE) {
                    randomIndex = MAX_INDEX_TO_REMOVE;
                }
                
                CHALKY_MANAGER->redBarToHide = randomIndex;
                
            }
            case 2:
            {
                int yellowPosition = CHALKY_MANAGER->yellowChalkyPosition;
                int randomIndex;
                if (yellowPosition < MAX_INDEX_TO_REMOVE)
                    randomIndex = rand()%(barsYellow->count() - yellowPosition) + yellowPosition;
                else
                    randomIndex = CCRANDOM_0_1() * 2;
                
                if (randomIndex == yellowPosition)
                    randomIndex++;
                if (randomIndex > MAX_INDEX_TO_REMOVE)
                    randomIndex = MAX_INDEX_TO_REMOVE;
                
                CHALKY_MANAGER->yellowBarToHide = randomIndex;
            }
            case 1:
            {
                int bluePosition = CHALKY_MANAGER->blueChalkyPosition;
                int randomIndex;
                if (bluePosition < MAX_INDEX_TO_REMOVE)
                    randomIndex = rand()%(barsBlue->count() - bluePosition) + bluePosition;
                else
                    randomIndex = CCRANDOM_0_1() * 2;
                
                if (randomIndex == bluePosition)
                    randomIndex++;
                if (randomIndex > MAX_INDEX_TO_REMOVE)
                    randomIndex = MAX_INDEX_TO_REMOVE;
                
                CHALKY_MANAGER->blueBarToHide = randomIndex;
                
            }
                
            default:
                break;
        }
    }
    else {
        int randomIndex = rand()%(barsBlue->count());
        if (randomIndex > MAX_INDEX_TO_REMOVE)
            randomIndex = MAX_INDEX_TO_REMOVE;
        CHALKY_MANAGER->indexToHideHSMode = randomIndex;
    }
    
    
    //Choose type of duster for removing next line (Red/Blue/Yellow)
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
    
    Duster * devil = Duster::create(DUSTER_IMAGE, col);
    this->addChild(devil,10);
}

void GamePlayScene::update(float dt)
{
    updateTimer(dt);
    if (CHALKY_MANAGER->getGameMode() == kModeNormal) {
        if(chalkyBlue)
        {
            float oldChalkyPosition = chalkyBlue->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(1, CHALKY_SPEED_KEY) * dt);
            chalkyBlue->setPosition(ccp(newChalkyPosition, chalkyBlue->getPositionY()));
            checkGameEndBlue(newChalkyPosition);
        }
        if (chalkyYellow)
        {
            float oldChalkyPosition = chalkyYellow->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(2, CHALKY_SPEED_KEY) * dt);
            chalkyYellow->setPosition(ccp(newChalkyPosition, chalkyYellow->getPositionY()));
            checkGameEndYellow(newChalkyPosition);
        }
        if(chalkyRed)
        {
            float oldChalkyPosition = chalkyRed->getPositionX();
            float newChalkyPosition = oldChalkyPosition + (CHALKY_MANAGER->getFloatValueForKey(3, CHALKY_SPEED_KEY) * dt);
            chalkyRed->setPosition(ccp(newChalkyPosition, chalkyRed->getPositionY()));
            checkGameEndRed(newChalkyPosition);
        }
        
        if (CHALKY_MANAGER->lastScore >= CHALKY_MANAGER->getFloatValueForKey(currentGameLevel, LEVEL_TARGET_KEY)) {
            goToLevelWinScreen();
        }
    }
}

void GamePlayScene::updateTimer(float dt)
{
    totalTimePlayed += dt;
    int totalTimePlayedInt = (int)totalTimePlayed;
    if (totalTimePlayedInt == previousTimeCount + 1 && countdownTimer > 0) {
        countdownTimer--;
        previousTimeCount++;
    }
    
    timerLabel->setString(CCString::createWithFormat(TIME_REMAINING_STRING, countdownTimer)->getCString());
}

void GamePlayScene::stopLoop()
{
    this->unscheduleUpdate();
    this->unschedule(schedule_selector(GamePlayScene::gameLoop));
}

#pragma mark - Game End Conditions

void GamePlayScene::checkGameEndBlue(float chalkyPosition)
{
    if (CHALKY_MANAGER->blueChalkyPosition >= barsBlue->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalkySpecialBlue);
        chalkySpecialBlue = false;
        chalkyBlue->removeFromParentAndCleanup(true);
        chalkyBlue = NULL;
    }
    else {
        int tag = 0;
        tag = chalkyPosition / barWidth;
        CHALKY_MANAGER->blueChalkyPosition = tag;
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                playChalkyFallAnimation(chalkyBlue);
            }
        }
    }
}
void GamePlayScene::checkGameEndYellow(float chalkyPosition)
{
    if (CHALKY_MANAGER->yellowChalkyPosition >= barsYellow->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalkySpecialYellow);
        chalkySpecialYellow = false;
        chalkyYellow->removeFromParentAndCleanup(true);
        chalkyYellow = NULL;
    }
    else {
        int tag = 0;
        int index = 0;
        index = chalkyPosition / barWidth;
        tag = (BAR_TAG_YELLOW + index);
        CHALKY_MANAGER->yellowChalkyPosition = index;
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                playChalkyFallAnimation(chalkyYellow);
            }
        }
    }
}
void GamePlayScene::checkGameEndRed(float chalkyPosition)
{
    if (CHALKY_MANAGER->redChalkyPosition >= barsRed->count()) {
        //GAME WIN CONDITION
        CHALKY_MANAGER->updatePlayerScore(chalkySpecialRed);
        chalkySpecialRed = false;
        chalkyRed->removeFromParentAndCleanup(true);
        chalkyRed=NULL;
    }
    else {
        int tag = 0;
        int index = 0;
        index = chalkyPosition / barWidth;
        tag = (BAR_TAG_RED + index);
        CHALKY_MANAGER->redChalkyPosition = index;
        Bar *b = (Bar*)this->getChildByTag(tag);
        if (b) {
            if (!b->isVisible()) {
                playChalkyFallAnimation(chalkyRed);
            }
        }
    }
}

void GamePlayScene::playChalkyFallAnimation(CCSkeletonAnimation *chalkyToRemove)
{
    CCDelayTime *delay = CCDelayTime::create(0.5);
    chalkyToRemove->addAnimation(FALL_ANIMATION_NAME, false);
    CCCallFunc *methodToCall;
    
    if (chalkyToRemove == chalkyBlue)
        methodToCall = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalkyBlue));
    else if (chalkyToRemove == chalkyYellow)
        methodToCall = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalkyYellow));
    else if (chalkyToRemove == chalkyRed)
        methodToCall = CCCallFunc::create(this, callfunc_selector(GamePlayScene::removeChalkyRed));
    
    CCSequence *seq = CCSequence::create(delay, methodToCall, NULL);
    chalkyToRemove->runAction(seq);

}

void GamePlayScene::removeChalkyBlue()
{
    chalkySpecialBlue = false;
    CHALKY_MANAGER->blueChalkyPosition = 0;
    chalkyBlue->stopAllActions();
    chalkyBlue->removeFromParentAndCleanup(true);
    chalkyBlue = NULL;
    addChalkyForLevel(1);
}
void GamePlayScene::removeChalkyYellow()
{
    chalkySpecialYellow = false;
    CHALKY_MANAGER->yellowChalkyPosition = 0;
    chalkyYellow->setVisible(false);
    chalkyYellow->stopAllActions();
    chalkyYellow->removeFromParentAndCleanup(true);
    chalkyYellow = NULL;
    addChalkyForLevel(2);
}

void GamePlayScene::removeChalkyRed()
{
    chalkySpecialRed = false;
    CHALKY_MANAGER->redChalkyPosition = 0;
    chalkyRed->setVisible(false);
    chalkyRed->stopAllActions();
    chalkyRed->removeFromParentAndCleanup(true);
    chalkyRed = NULL;
    addChalkyForLevel(3);
    
}
