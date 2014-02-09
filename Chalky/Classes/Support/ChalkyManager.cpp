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
    chalky1Index = 0;
    chalky2Index = 0;
    chalky3Index = 0;
    blueChalks = 2;
    yellowChalks = 1;
    redChalks = 2;
    
    chalky1Speed = 0;
    chalky2Speed = 0;
    chalky3Speed = 0;
    dusterLevel1 = 0;
    dusterLevel2 = 0;
    dusterLevel3 = 0;
    totalSteps = 0;
    gameMode = kModeUnknown;
    indexToHideSpecial = 0;
    newChalkyInterval = 0;
    
    normalPoints = 5;
    specialPoints = 10;
    specialProbability = 0.5;
    targetScore1 = 0;
    targetScore2 = 0;
    targetScore3 = 0;
    hsModeDuration = 0;
    normalModeDuration = 0;
}

ChalkyManager::~ChalkyManager() {
	
}

ChalkyManager* ChalkyManager::sharedManager() {
    
	if (!sharedInst) {
		sharedInst = new ChalkyManager();
	}
	return sharedInst;
}

void ChalkyManager::loadGameData()
{
    const char *relativePath = (CCFileUtils::sharedFileUtils()->fullPathForFilename("LevelData.plist")).c_str();
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(relativePath);
    chalky1Speed = ((CCString*)dict->objectForKey("ChalkySpeed1"))->intValue();
    chalky2Speed = ((CCString*)dict->objectForKey("ChalkySpeed2"))->intValue();
    chalky3Speed = ((CCString*)dict->objectForKey("ChalkySpeed3"))->intValue();
    dusterLevel1 = ((CCString*)dict->objectForKey("DusterSpeed1"))->intValue();
    dusterLevel2 = ((CCString*)dict->objectForKey("DusterSpeed2"))->intValue();
    dusterLevel3 = ((CCString*)dict->objectForKey("DusterSpeed3"))->intValue();
    newChalkyInterval = ((CCString*)dict->objectForKey("NewChalkyInterval"))->intValue();
    
    normalPoints = ((CCString*)dict->objectForKey("PointsNormal"))->intValue();
    specialPoints = ((CCString*)dict->objectForKey("PointsSpecial"))->intValue();
    specialProbability = ((CCString*)dict->objectForKey("SpecialProbability"))->floatValue();
    targetScore1 = ((CCString*)dict->objectForKey("TargetScoreLev1"))->intValue();
    targetScore2 = ((CCString*)dict->objectForKey("TargetScoreLev2"))->intValue();
    targetScore3 = ((CCString*)dict->objectForKey("TargetScoreLev3"))->intValue();
    hsModeDuration = ((CCString*)dict->objectForKey("HSModeDuration"))->intValue();
    normalModeDuration = ((CCString*)dict->objectForKey("NormalModeDuration"))->intValue();
}