//
//  LevelEndScreen.cpp
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#include "LevelEndScreen.h"
#include "ChalkyManager.h"
#include "GamePlayScene.h"
#include "MainMenu.h"
#include "Constants.h"

#define SUCCESS_TITLE           "Success!"
#define FAILED_TITLE            "Failed!"
#define SUCCESS_DESCRIPTION     "Yaay! Your Chalkies Made It"
#define FAILED_DESCRIPTION      "Time's Up! Your Chalkies Didn't Make It"
#pragma mark - Initializations
LevelEndScreen::LevelEndScreen()
{
    levelSuccess = false;
}

LevelEndScreen::~LevelEndScreen()
{
}

void LevelEndScreen::onEnter()
{
    CCLayer::onEnter();
    addLayerAssets();
    
}

void LevelEndScreen::onExit()
{
    CCLayer::onExit();
    removeAllChildrenWithCleanup(true);
}

CCScene* LevelEndScreen::scene()
{
	CCScene *scene = CCScene::create();
    scene->addChild(this);
	return scene;
}

LevelEndScreen* LevelEndScreen::create(bool levelCleared)
{
    LevelEndScreen *screen = new LevelEndScreen();
    if(screen != NULL && screen->init(levelCleared)) {
        screen->autorelease();
    } else {
        delete screen;
        screen = NULL;
    }
    return screen;
}

bool LevelEndScreen::init(bool levelCleared)
{
    if(!CCLayer::init())
        return false;
    
    levelSuccess = levelCleared;
    return true;
}


#pragma mark - Add Assets
void LevelEndScreen::addLayerAssets()
{
    addBackground();
    addLabels();
    addButtons();
    updateLevel();
}

void LevelEndScreen::addBackground()
{
    CCSprite *background = CCSprite::create(GAME_BACKGROUND);
    background->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(background);
}

void LevelEndScreen::addLabels()
{
    int level = CHALKY_MANAGER->currentLevel;
    //Limit total levels to 3
    if (level > 3)
        level = 3;
    
    CCString *levelStr = CCString::createWithFormat("LEVEL %i", level);
    CCLabelTTF *levelLabel = CCLabelTTF::create(levelStr->getCString(), CHALKY_FONT, 40.0);
    levelLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.85));
    this->addChild(levelLabel);
    
    CCLabelTTF *statusLabel;
    CCLabelTTF *descriptionLabel;
    if (levelSuccess){
        statusLabel = CCLabelTTF::create(SUCCESS_TITLE, CHALKY_FONT, 30.0);
        descriptionLabel = CCLabelTTF::create(SUCCESS_DESCRIPTION, CHALKY_FONT, 30.0);
    }
    else {
        statusLabel = CCLabelTTF::create(FAILED_TITLE, CHALKY_FONT, 30.0);
        descriptionLabel = CCLabelTTF::create(FAILED_DESCRIPTION, CHALKY_FONT, 30.0);
    }
    
    statusLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.75));
    descriptionLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.65));
    
    this->addChild(statusLabel);
    this->addChild(descriptionLabel);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("SCORE", CHALKY_FONT, 40.0);
    scoreLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.55));
    this->addChild(scoreLabel);
    
    CCString *scoreStr = CCString::createWithFormat("%i", CHALKY_MANAGER->lastScore);
    CCLabelTTF *playerScoreLabel = CCLabelTTF::create(scoreStr->getCString(), CHALKY_FONT, 40.0);
    playerScoreLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.475));
    this->addChild(playerScoreLabel);
}

void LevelEndScreen::addButtons()
{
    if (CHALKY_MANAGER->currentLevel > 3) {
        CCMenuItemImage *playHSMode = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(LevelEndScreen::quitButtonPressed));
        playHSMode->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.35));
        
        CCLabelTTF *buttonLabel = CCLabelTTF::create("HOME", CHALKY_FONT, CHALKY_FONT_SIZE);
        buttonLabel->setPosition(ccp(playHSMode->getContentSize().width/2, playHSMode->getContentSize().height/2));
        playHSMode->addChild(buttonLabel);
        
        CCMenu *menu = CCMenu::create(playHSMode,NULL);
        menu->setAnchorPoint(CCPointZero);
        menu->setPosition(CCPointZero);
        this->addChild(menu);
    }
    else {
        CCMenuItemImage *playButton = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(LevelEndScreen::continueButtonPressed));
        playButton->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.35));
        
        const char *playButtonString;
        if (levelSuccess)
            playButtonString = "CONTINUE";
        else
            playButtonString = "AGAIN";
        
        CCLabelTTF *playButtonLabel = CCLabelTTF::create(playButtonString, CHALKY_FONT, CHALKY_FONT_SIZE);
        playButtonLabel->setPosition(ccp(playButton->getContentSize().width/2, playButton->getContentSize().height/2));
        playButton->addChild(playButtonLabel);
        
        CCMenuItemImage *playHSMode = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(LevelEndScreen::quitButtonPressed));
        playHSMode->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.20));
        
        CCLabelTTF *buttonLabel = CCLabelTTF::create("HOME", CHALKY_FONT, CHALKY_FONT_SIZE);
        buttonLabel->setPosition(ccp(playHSMode->getContentSize().width/2, playHSMode->getContentSize().height/2));
        playHSMode->addChild(buttonLabel);
        
        CCMenu *menu = CCMenu::create(playButton, playHSMode,NULL);
        menu->setAnchorPoint(CCPointZero);
        menu->setPosition(CCPointZero);
        this->addChild(menu);
    }
    
}

#pragma mark - Button Press Events

void LevelEndScreen::continueButtonPressed()
{
    GamePlayScene *pScene = GamePlayScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void LevelEndScreen::quitButtonPressed()
{
    //Reset current level
    if (CHALKY_MANAGER->currentLevel > 3) {
        CHALKY_MANAGER->currentLevel = 1;
    }
    MainMenu *pScene = MainMenu::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}


void LevelEndScreen::updateLevel()
{
    if (levelSuccess)
        CHALKY_MANAGER->currentLevel++;
}