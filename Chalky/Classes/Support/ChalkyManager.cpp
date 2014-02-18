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
    chalky1Index = 0;
    chalky2Index = 0;
    chalky3Index = 0;
    blueChalks = 2;
    yellowChalks = 1;
    redChalks = 2;
    
    totalSteps = 0;
    gameMode = kModeUnknown;
    indexToHideSpecial = 0;
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

void ChalkyManager::updatePlayerScore(bool _isSpecialChalky)
{
    if (_isSpecialChalky)
        lastScore += getFloatValueForKey(POINTS_SPECIAL_KEY);
    else
        lastScore += getFloatValueForKey(POINTS_NORMAL_KEY);
}
