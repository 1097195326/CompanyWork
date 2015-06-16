//
//  GameLoading.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#include "GameLoading.h"

#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GuanQiaManager.h"

#include "json/json.h"

float GameLoading::loadSprites()
{
    
}
float GameLoading::loadFrames()
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("HumanThrow.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("explosion.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao.plist"));
    
    std::map<std::string,Gun *>::iterator gunIter;
    std::map<std::string,Gun *> gunData = GunManager::getInstance()->getTakeUpGunData();
    for (gunIter = gunData.begin(); gunIter != gunData.end(); ++gunIter)
    {
        Gun * gun = gunIter->second;
        std::string modelId = gun->getModelId();
        if ("qiang3" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang3.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang3_2.plist"));
        }else if ("qiang5" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang5.plist"));
        }else if ("qiang7" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang7.plist"));
        }
    }
    
    std::map<std::string,Prop *>::iterator propIter;
    std::map<std::string,Prop *> propData = PropManager::getInstance()->getTakeUpProp();
    for (propIter = propData.begin(); propIter != propData.end(); ++propIter)
    {
        Prop * prop = propIter->second;
        std::string modelId = prop->getModelId();
        if ("daoju1" == modelId || "daoju2" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("Daoju12.plist"));
        }else if ("daoju5" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("Daoju5.plist"));
        }else if ("daoju6" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear1.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear2.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear3.plist"));
        }
    }
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("burn.plist"));
    
    std::map<std::string,DefenseBuilding *>::iterator buildingIter;
    std::map<std::string,DefenseBuilding *> buildingData = DefenseBuildingManager::getInstance()->getBuildingData();
    for (buildingIter = buildingData.begin(); buildingIter != buildingData.end(); ++buildingIter)
    {
        DefenseBuilding * building = buildingIter->second;
        std::string modelId = building->getModelId();
        if ("building3" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("monkey.plist"));
        }
    }
    
    GuanqiaModel * guanqiaModel = GuanQiaManager::getInstance()->getCurrentGuanqia();
    
    Json::Value dataValue = guanqiaModel->getMonsters();
    
    for (int i = 0; i < dataValue.size(); ++i)
    {
        Json::Value data = dataValue[i];
        for (int i = 0; i < data.size(); ++i) {
            Json::Value d = data[i];
            int monsterId = atoi(d["monsterid"].asString().c_str());
            switch (monsterId) {
                case 100001:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull4.plist"));
                    break;
                case 100002:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullArmor.plist"));
                    break;
                case 100003:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie3.plist"));
                    break;
                case 100004:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieArmor.plist"));
                    break;
                case 100005:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("bat.plist"));
                    break;
                case 100006:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("bat.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("batArmor.plist"));
                    break;
                case 100007:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("crow.plist"));
                    break;
                case 100008:
                    
                    break;
                case 100009:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind2.plist"));
                    break;
                case 100010:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blindArmor.plist"));
                    break;
                case 100011:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea4.plist"));
                    break;
                case 100012:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaArmor.plist"));
                    break;
                case 100013:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin4.plist"));
                    break;
                case 100014:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinArmor.plist"));
                    break;
                case 100015:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow4.plist"));
                    break;
                case 100016:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowArmor.plist"));
                    break;
                case 200001:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2.plist"));
                    break;
                case 200002:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking2.plist"));
                    break;
                case 200003:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking4.plist"));
                    break;
                case 200004:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking2.plist"));
                    break;
                default:
                    break;
            }
        }
    }
    
//    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf1.plist"));
//    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf2.plist"));
//    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf3.plist"));
//    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf4.plist"));
//    
//    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demon.plist"));
    
}