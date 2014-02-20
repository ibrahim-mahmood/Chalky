//
//  MainMenu.cpp
//  Chalky
//
//  Created by Ibrahim on 22/09/2013.
//
//

#include "MainMenu.h"
#include "ChalkyManager.h"
#include "GamePlayScene.h"
#include "spine-cocos2dx.h"
#include "Constants.h"
#include "Macros.h"

USING_NS_CC_EXT;

#pragma mark - Initializations
MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
}

void MainMenu::onEnter() {
    CCLayer::onEnter();
    addLayerAssets();
}

void MainMenu::onExit() {
    CCLayer::onExit();
    removeAllChildrenWithCleanup(true);
}

CCScene* MainMenu::scene() {
	CCScene *scene = CCScene::create();
    scene->addChild(this);
	return scene;
}

#pragma mark - Add Assets
void MainMenu::addLayerAssets() {
    addBackground();
    addButton();
}

void MainMenu::addBackground() {
    CCSprite *background = CCSprite::create(GAME_BACKGROUND);
    background->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2));
    this->addChild(background);
    
    CCSprite *logo = CCSprite::create(CHALKY_LOGO);
    logo->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.65));
    this->addChild(logo);
}

void MainMenu::addButton() {
    CCMenuItemImage *playButton = CCMenuItemImage::create(PLAY_BUTTON_NORMAL, PLAY_BUTTON_PRESSED, this, menu_selector(MainMenu::playButtonPressed));
    playButton->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.35));
    
    CCMenuItemImage *playHSMode = CCMenuItemImage::create(EMPTY_BUTTON_NORMAL, EMPTY_BUTTON_PRESSED, this, menu_selector(MainMenu::playHSButtonPressed));
    playHSMode->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT * 0.20));
    
    CCLabelTTF *buttonLabel = CCLabelTTF::create("FUN MODE", CHALKY_FONT, CHALKY_FONT_SIZE);
    buttonLabel->setPosition(ccp(playHSMode->getContentSize().width/2, playHSMode->getContentSize().height/2));
    playHSMode->addChild(buttonLabel);
    
    CCMenu *menu = CCMenu::create(playButton, playHSMode,NULL);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

#pragma mark - Button Press Events
void MainMenu::playButtonPressed() {
    CHALKY_MANAGER->setGameMode(kModeNormal);
    if (CHALKY_MANAGER->currentLevel < 1 || CHALKY_MANAGER->currentLevel > 3) {
        CHALKY_MANAGER->currentLevel = 1;
    }
    GamePlayScene *pScene = GamePlayScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}

void MainMenu::playHSButtonPressed() {
    CHALKY_MANAGER->setGameMode(kModeHS);
    GamePlayScene *pScene = GamePlayScene::create();
    CCDirector::sharedDirector()->replaceScene(pScene->scene());
}
