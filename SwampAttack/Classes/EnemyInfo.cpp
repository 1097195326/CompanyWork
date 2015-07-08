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
    // zombieking 僵尸王
    EnemyInfoData zombieking;
    zombieking.attackFrame = 8;
    zombieking.attackFrames = 11;
    zombieking.hurtHeavyFrames = 9;
    zombieking.hurtLightFrames = 5;
    zombieking.hurtOnFrames = 5;
    zombieking.walkFrames = 14;
    zombieking.downFrames = 13;
    zombieking.width = 240;
    zombieking.height = 230;
    zombieking.widthOffSet = 0;
    m_data["zombieking"] = zombieking;
    // wolf 狼人
    EnemyInfoData wolf;
    wolf.attackFrame = 8;
    wolf.attackFrames = 11;
    wolf.hurtHeavyFrames = 9;
    wolf.hurtLightFrames = 5;
    wolf.hurtOnFrames = 5;
    wolf.walkFrames = 14;
    wolf.downFrames = 13;
    wolf.width = 260;
    wolf.height = 260;
    wolf.widthOffSet = 0;
    m_data["wolf"] = wolf;
    // wolfking 狼王
    EnemyInfoData wolfking;
    wolfking.attackFrame = 8;
    wolfking.attackFrames = 11;
    wolfking.hurtHeavyFrames = 9;
    wolfking.hurtLightFrames = 5;
    wolfking.hurtOnFrames = 5;
    wolfking.walkFrames = 14;
    wolfking.downFrames = 13;
    wolfking.width = 350;
    wolfking.height = 350;
    wolfking.widthOffSet = 0;
    m_data["wolfking"] = wolfking;
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
    // skullking 骷髅王
    EnemyInfoData skullking;
    skullking.attackFrame = 8;
    skullking.attackFrames = 11;
    skullking.hurtHeavyFrames = 9;
    skullking.hurtLightFrames = 5;
    skullking.hurtOnFrames = 5;
    skullking.walkFrames = 14;
    skullking.downFrames = 13;
    skullking.width = 270;
    skullking.height = 270;
    skullking.widthOffSet = 0;
    m_data["skullking"] = skullking;
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
    skullArmor.height = 90;
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
    scarecrowArmor.height = 95;
    scarecrowArmor.widthOffSet = 0;
    m_data["scarecrow_armor"] = scarecrowArmor;
    // scareking 草人王
    EnemyInfoData scareking;
    scareking.attackFrame = 7;
    scareking.attackFrames = 11;
    scareking.hurtHeavyFrames = 9;
    scareking.hurtLightFrames = 5;
    scareking.hurtOnFrames = 5;
    scareking.walkFrames = 14;
    scareking.downFrames = 13;
    scareking.width = 310;
    scareking.height = 250;
    scareking.widthOffSet = 0;
    m_data["scareking"] = scareking;
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
    bat.downFrames = 13;
    bat.width = 160;
    bat.height = 140;
    bat.widthOffSet = 0;
    m_data["bat"] = bat;
    // bat_armor
    EnemyInfoData batArmor;
    batArmor.attackFrame = 7;
    batArmor.attackFrames = 11;
    batArmor.walkFrames = 7;
    batArmor.width = 160;
    batArmor.height = 70;
    batArmor.widthOffSet = 0;
    m_data["bat_armor"] = batArmor;
    // crow 乌鸦
    EnemyInfoData crow;
    crow.attackFrame = 6;
    crow.attackFrames = 7;
    crow.walkFrames = 7;
    crow.width = 200;
    crow.height = 170;
    crow.widthOffSet = 0;
    m_data["crow"] = crow;
    // blind 自爆兵
    EnemyInfoData blind;
    blind.attackFrame = 7;
    blind.attackFrames = 14;
    blind.hurtHeavyFrames = 9;
    blind.hurtLightFrames = 5;
    blind.hurtOnFrames = 5;
    blind.walkFrames = 8;
    blind.downFrames = 14;
    blind.width = 170;
    blind.height = 160;
    blind.widthOffSet = 0;
    m_data["blind"] = blind;
    // blindArmor
    EnemyInfoData blindArmor;
    blindArmor.attackFrame = 7;
    blindArmor.attackFrames = 14;
    blindArmor.hurtHeavyFrames = 9;
    blindArmor.hurtLightFrames = 5;
    blindArmor.hurtOnFrames = 5;
    blindArmor.walkFrames = 8;
    blindArmor.width = 170;
    blindArmor.height = 80;
    blindArmor.widthOffSet = 0;
    m_data["blind_armor"] = blindArmor;
    
    
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