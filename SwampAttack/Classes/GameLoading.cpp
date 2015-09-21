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
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("HumanThrow.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("explosion.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao.plist"));
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao2.plist"));
    
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
            log("add qiang3");
        }else if ("qiang5" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang5.plist"));
        }else if ("qiang7" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang7.plist"));
        }else if ("qiang8" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang8.plist"));
        }else if ("qiang9" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang9.plist"));
        }else if ("qiang10" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang10.plist"));
        }else if ("qiang11" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang11.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang11_2.plist"));
        }else if ("qiang12" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("qiang12.plist"));
        }
    }
    
    std::map<std::string,Prop *>::iterator propIter;
    std::map<std::string,Prop *> propData = PropManager::getInstance()->getTakeUpProp();
    for (propIter = propData.begin(); propIter != propData.end(); ++propIter)
    {
        Prop * prop = propIter->second;
        std::string modelId = prop->getModelId();
        if ("daoju1" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("daoju1.plist"));
        }else if ("daoju2" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("daoju2.plist"));
        }else if ("daoju5" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("Daoju5_1.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("Daoju5_2.plist"));
        }else if ("daoju6" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear1.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear2.plist"));
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("nulear3.plist"));
        }else if ("daoju7" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("daoju7.plist"));
        }else if ("daoju8" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("daoju8.plist"));
        }else if ("daoju9" == modelId)
        {
            spriteFrameCache->addSpriteFramesWithFile(ImagePath("daoju9.plist"));
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
                    break;
                case 100002:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullArmor.plist"));
                    break;
                case 100003:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie1.plist"));
                    break;
                case 100004:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombie1.plist"));
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
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind.plist"));
                    break;
                case 100010:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blind.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("blindArmor.plist"));
                    break;
                case 100011:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea1.plist"));
                    break;
                case 100012:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Muroidea1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("muroideaArmor.plist"));
                    break;
                case 100013:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin1.plist"));
                    break;
                case 100014:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("Pumpkin1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("pumpkinArmor.plist"));
                    break;
                case 100015:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow1.plist"));
                    break;
                case 100016:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrow1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scarecrowArmor.plist"));
                    break;
                case 100017:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demon.plist"));
                    break;
                case 100018:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demon.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demonArmor.plist"));
                    break;
                case 100019:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf2.plist"));
                    break;
                case 100020:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolf2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfArmor1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfArmor2.plist"));
                    break;
                case 100021:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowman1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowman2.plist"));
                    break;
                case 100022:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skull_shield.plist"));
                    break;
                case 100023:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("vampire1.plist"));
                    break;
                case 100024:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("bee.plist"));
                    break;
                case 100025:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullA.plist"));
                    break;
                case 100026:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcher1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcher2.plist"));
                    break;
                case 200001:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking4.plist"));
                    break;
                case 200002:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("zombieking4.plist"));
                    break;
                case 200003:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking5.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking6.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking7.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking8.plist"));
                    break;
                case 200004:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("scareking5.plist"));
                    break;
                case 200005:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2_1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2_2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2_3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("skullking2_4.plist"));
                    break;
                case 200006:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_5.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_6.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("wolfking2_7.plist"));
                    break;
                case 200007:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demonking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("demonking2.plist"));
                    break;
                case 200008:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowmanking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowmanking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowmanking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowmanking4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("snowmanking5.plist"));
                    break;
                case 200009:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking3.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking4.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking5.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("butcherking6.plist"));
                    break;
                case 200010:
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("vampireking1.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("vampireking2.plist"));
                    spriteFrameCache->addSpriteFramesWithFile(ImagePath("vampireking3.plist"));
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