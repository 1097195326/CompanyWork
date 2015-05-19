//
//  EnemyInfo.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "EnemyInfo.h"


EnemyInfo::EnemyInfo()
{
    // zombie 僵尸
    EnemyInfoData zombie;
    zombie.attackFrame = 8;
    zombie.attackFrames = 11;
    zombie.hurtHeavyFrames = 9;
    zombie.hurtLightFrames = 5;
    zombie.hurtOnFrames = 5;
    zombie.walkFrames = 14;
    zombie.downFrames = 13;
    zombie.width = 170;
    zombie.height = 170;
    zombie.widthOffSet = 0;
    m_data["zombie"] = zombie;
    // skull 骷髅
    EnemyInfoData skull;
    skull.attackFrame = 8;
    skull.attackFrames = 11;
    skull.hurtHeavyFrames = 9;
    skull.hurtLightFrames = 5;
    skull.hurtOnFrames = 5;
    skull.walkFrames = 14;
    skull.downFrames = 13;
    skull.width = 180;
    skull.height = 180;
    skull.widthOffSet = 0;
    m_data["skull"] = skull;
    // skullArmor
    EnemyInfoData skullArmor;
    skullArmor.attackFrame = 8;
    skullArmor.attackFrames = 11;
    skullArmor.hurtHeavyFrames = 9;
    skullArmor.hurtLightFrames = 5;
    skullArmor.hurtOnFrames = 5;
    skullArmor.walkFrames = 14;
    skullArmor.downFrames = 0;
    skullArmor.width = 180;
    skullArmor.height = 180;
    skullArmor.widthOffSet = 0;
    m_data["skull_armor"] = skullArmor;
    // scarecrow 草人
    EnemyInfoData scarecrow;
    scarecrow.attackFrame = 7;
    scarecrow.attackFrames = 11;
    scarecrow.hurtHeavyFrames = 9;
    scarecrow.hurtLightFrames = 5;
    scarecrow.hurtOnFrames = 5;
    scarecrow.walkFrames = 14;
    scarecrow.downFrames = 13;
    scarecrow.width = 230;
    scarecrow.height = 190;
    scarecrow.widthOffSet = 0;
    m_data["scarecrow"] = scarecrow;
    // scarecrowArmor 草人
    EnemyInfoData scarecrowArmor;
    scarecrowArmor.attackFrame = 7;
    scarecrowArmor.attackFrames = 11;
    scarecrowArmor.hurtHeavyFrames = 9;
    scarecrowArmor.hurtLightFrames = 5;
    scarecrowArmor.hurtOnFrames = 5;
    scarecrowArmor.walkFrames = 14;
    scarecrowArmor.downFrames = 13;
    scarecrowArmor.width = 230;
    scarecrowArmor.height = 190;
    scarecrowArmor.widthOffSet = 0;
    m_data["scarecrow_armor"] = scarecrowArmor;
    // Pumpkin 南瓜头
    EnemyInfoData pumpkin;
    pumpkin.attackFrame = 7;
    pumpkin.attackFrames = 11;
    pumpkin.hurtHeavyFrames = 9;
    pumpkin.hurtLightFrames = 5;
    pumpkin.hurtOnFrames = 5;
    pumpkin.walkFrames = 14;
    pumpkin.downFrames = 13;
    pumpkin.width = 200;
    pumpkin.height = 180;
    pumpkin.widthOffSet = 0;
    m_data["Pumpkin"] = pumpkin;
    // Muroidea 老鼠兵
    EnemyInfoData muroidea;
    muroidea.attackFrame = 5;
    muroidea.attackFrames = 11;
    muroidea.hurtHeavyFrames = 9;
    muroidea.hurtLightFrames = 5;
    muroidea.hurtOnFrames = 5;
    muroidea.walkFrames = 14;
    muroidea.downFrames = 13;
    muroidea.width = 180;
    muroidea.height = 180;
    muroidea.widthOffSet = 0;
    m_data["Muroidea"] = muroidea;
    // bat 蝙蝠
    EnemyInfoData bat;
    bat.attackFrame = 7;
    bat.attackFrames = 11;
    bat.walkFrames = 7;
    bat.width = 160;
    bat.height = 140;
    bat.widthOffSet = 0;
    m_data["bat"] = bat;
    // crow 乌鸦
    EnemyInfoData crow;
    crow.attackFrame = 6;
    crow.attackFrames = 7;
    crow.walkFrames = 7;
    crow.width = 200;
    crow.height = 170;
    crow.widthOffSet = 0;
    m_data["crow"] = crow;
    
}
EnemyInfo * EnemyInfo::getInstance()
{
    static EnemyInfo info;
    return &info;
}
EnemyInfoData EnemyInfo::getInfoByName(string name)
{
    return m_data[name];
}