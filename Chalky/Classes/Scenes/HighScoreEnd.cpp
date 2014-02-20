//
//  HighScoreEnd.cpp
//  Chalky
//
//  Created by Ibrahim on 23/09/2013.
//
//

#include "HighScoreEnd.h"
#include "ChalkyManager.h"
#include "GamePlayScene.h"
#include "MainMenu.h"
#include "Constants.h"

#pragma mark - Initializations
HighScoreEnd::HighScoreEnd()
{
}

HighScoreEnd::~HighScoreEnd()
{
}

void HighScoreEnd::onEnter()
{
    CCLayer::onEnter();
    addLayerAssets();
    
}

void HighScoreEnd::onExit()
{
    CCLayer::onExit();
    removeAllChildrenWithCleanup(true);
}

CCScene* HighScoreEnd::scene()
{
	CCScene *scene = CCScene::create();
    scene->addChild(this);
	return scene;
}

#pragma mark - Add Assets

void HighScoreEnd::addLayerAssets()
{
    addBackground();
    addButton();
}

void HighScoreEnd::addBackground()
{
    CCSprite *background = CCSprite::create(GAME_BACKGROUND);
    background->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(background);
    
    CCLabelTTF *successLabel1 = CCLabelTTF::create("Your Chalkies Made It", CHALKY_FONT, 30.0);
    successLabel1->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.85));
    this->addChild(successLabel1);
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("SCORE", CHALKY_FONT, 40.0);
    scoreLabel->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.70));
    this->addChild(scoreLabel);
    
    CCString *scoreStr = CCString::createWithFormat("%i", CHALKY_MANAGER->lastScore);
    CCLabelTTF *scoreLabel1 = CCLabelTTF::create(scoreStr->getCString(), CHALKY_FONT, 30.0);
    scoreLabel1->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.60));
    this->addChild(scoreLabel1);
    
}

void HighScoreEnd::addButton()
{
    CCMenuItemImage *playButton = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(HighScoreEnd::continueButtonPressed));
    playButton->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.35));
    
    CCLabelTTF *playButtonLabel = CCLabelTTF::create("AGAIN", CHALKY_FONT, CHALKY_FONT_SIZE);
    playButtonLabel->setPosition(ccp(playButton->getContentSize().width/2, playButton->getContentSize().height/2));
    playButton->addChild(playButtonLabel);
    
    CCMenuItemImage *playHSMode = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(HighScoreEnd::quitButtonPressed));
    playHSMode->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.20));
    
    CCLabelTTF *buttonLabel = CCLabelTTF::create("HOME", CHALKY_FONT, CHALKY_FONT_SIZE);
    buttonLabel->setPosition(ccp(playHSMode->getContentSize().width/2, playHSMode->getContentSize().height/2));
    playHSMode->addChild(buttonLabel);
    
    CCMenu *menu = CCMenu::create(playButton, playHSMode,NULL);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

#pragma mark - Button Press Events

void HighScoreEnd::continueButtonPressed()
{
    GamePlayScene *pScene = GamePlayScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void HighScoreEnd::quitButtonPressed()
{
    MainMenu *pScene = MainMenu::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}
