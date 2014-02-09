//
//  LevelLoseScreen.cpp
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#include "LevelLoseScreen.h"
#include "LevelWinScreen.h"
#include "ChalkyManager.h"
#include "GamePlayScene.h"
#include "MainMenu.h"
#include "Constants.h"

#pragma mark - Initializations
LevelLoseScreen::LevelLoseScreen()
{
}

LevelLoseScreen::~LevelLoseScreen()
{
}

void LevelLoseScreen::onEnter()
{
    CCLayer::onEnter();
    addLayerAssets();
    
}

void LevelLoseScreen::onExit()
{
    CCLayer::onExit();
    removeAllChildrenWithCleanup(true);
}

CCScene* LevelLoseScreen::scene()
{
	CCScene *scene = CCScene::create();
    scene->addChild(this);
	return scene;
}


#pragma mark - Add Assets

void LevelLoseScreen::addLayerAssets()
{
    addBackground();
    addButton();
}

void LevelLoseScreen::addBackground()
{
    CCSprite *background = CCSprite::create(GAME_BACKGROUND);
    background->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(background);
    
    int level = CHALKY_MANAGER->currentLevel;
    if (level > 3)
    {
        level = 3;
    }
    CCString *levelStr = CCString::createWithFormat("LEVEL %i", level);
    CCLabelTTF *levelLabel = CCLabelTTF::create(levelStr->getCString(), "chalky-button-pressed.png", 40.0);
    levelLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.85));
    this->addChild(levelLabel);
    
    CCLabelTTF *successLabel = CCLabelTTF::create("Failed!", "chalky-button-pressed.png", 30.0);
    successLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.75));
    this->addChild(successLabel);
    
    CCLabelTTF *successLabel1 = CCLabelTTF::create("Your Chalkies Didn't Make It", "chalky-button-pressed.png", 30.0);
    successLabel1->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.65));
    this->addChild(successLabel1);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("SCORE", "chalky-button-pressed.png", 40.0);
    scoreLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(scoreLabel);
    
    CCString *scoreStr = CCString::createWithFormat("%i", CHALKY_MANAGER->lastScore);
    CCLabelTTF *scoreLabel1 = CCLabelTTF::create(scoreStr->getCString(), "chalky-button-pressed.png", 30.0);
    scoreLabel1->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(scoreLabel1);
    
}

void LevelLoseScreen::addButton()
{
    if (CHALKY_MANAGER->currentLevel > 3) {
        CCMenuItemImage *playHSMode = CCMenuItemImage::create("chalky-button.png", "chalky-button-pressed.png", this, menu_selector(LevelWinScreen::quitButtonPressed));
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
        CCMenuItemImage *playButton = CCMenuItemImage::create("chalky-button.png", "chalky-button-pressed.png", this, menu_selector(LevelWinScreen::continueButtonPressed));
        playButton->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.35));
        
        CCLabelTTF *playButtonLabel = CCLabelTTF::create("RETRY", CHALKY_FONT, CHALKY_FONT_SIZE);
        playButtonLabel->setPosition(ccp(playButton->getContentSize().width/2, playButton->getContentSize().height/2));
        playButton->addChild(playButtonLabel);
        
        CCMenuItemImage *playHSMode = CCMenuItemImage::create("chalky-button.png", "chalky-button-pressed.png", this, menu_selector(LevelWinScreen::quitButtonPressed));
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
void LevelLoseScreen::continueButtonPressed()
{
    GamePlayScene *pScene = GamePlayScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void LevelLoseScreen::quitButtonPressed()
{
    MainMenu *pScene = MainMenu::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}
