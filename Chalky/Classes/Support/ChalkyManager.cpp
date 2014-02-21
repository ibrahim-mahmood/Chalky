//
//  ChalkyManager.cpp
//  Chalky
//
//  Created by Ibrahim on 20/09/2013.
//
//

#include "ChalkyManager.h"

#pragma mark - initializations
static ChalkyManager *sharedInst = NULL;

ChalkyManager::ChalkyManager() {
    
    gameData = NULL;
    blueChalkyPosition = 0;
    yellowChalkyPosition = 0;
    redChalkyPosition = 0;
    currentLevel = 1;
    
    totalSteps = 0;
    gameMode = kModeUnknown;
    indexToHideHSMode = 0;
}

ChalkyManager::~ChalkyManager() {
	CC_SAFE_RELEASE(gameData);
}

ChalkyManager* ChalkyManager::sharedManager() {
    
	if (!sharedInst)
		sharedInst = new ChalkyManager();
	return sharedInst;
}

void ChalkyManager::loadGameData()
{
    const char *relativePath = (CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_DATA_FILE)).c_str();
    this->setGameData(CCDictionary::createWithContentsOfFile(relativePath));
}

float ChalkyManager::getFloatValueForKey(int _numberToAppend, std::string _key)
{
    float ret_value = 0.0f;
    if (gameData) {
        std::string speedKey = appendIntToString(_numberToAppend, _key);
        ret_value = (static_cast<CCString*>(gameData->objectForKey(speedKey)))->floatValue();
    }
    return ret_value;
}

float ChalkyManager::getFloatValueForKey(std::string _key)
{
    float ret_value = 0.0f;
    if (gameData)
        ret_value = (static_cast<CCString*>(gameData->objectForKey(_key)))->floatValue();
    return ret_value;
}

std::string ChalkyManager::getStringForKey(std::string _key)
{
    std::string ret_value = std::string("");
    if (gameData)
        ret_value = (static_cast<CCString*>(gameData->objectForKey(_key)))->m_sString;
    return ret_value;
}

void ChalkyManager::updatePlayerScore(bool _isSpecialChalky)
{
    if (_isSpecialChalky)
        lastScore += getFloatValueForKey(POINTS_SPECIAL_KEY);
    else
        lastScore += getFloatValueForKey(POINTS_NORMAL_KEY);
}

void ChalkyManager::resetGameState()
{
    blueChalkyPosition = 0;
    yellowChalkyPosition = 0;
    redChalkyPosition = 0;
    indexToHideHSMode = 0;
    lastScore = 0;
    loadLives();
}

void ChalkyManager::loadLives()
{
    blueChalks = getFloatValueForKey(BLUE_LIVES_KEY);
    yellowChalks = getFloatValueForKey(YELLOW_LIVES_KEY);
    redChalks = getFloatValueForKey(RED_LIVES_KEY);
}
