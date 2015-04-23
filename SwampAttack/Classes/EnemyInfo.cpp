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
    zombie.attackFrames = 12;
    zombie.waitFrames = 12;
    zombie.walkFrames = 14;
    zombie.downFrames = 14;
    zombie.width = 190;
    zombie.height = 190;
    zombie.widthOffSet = 0;
    m_data["zombie"] = zombie;
    // skull 骷髅
    EnemyInfoData skull;
    skull.attackFrame = 8;
    skull.attackFrames = 12;
    skull.waitFrames = 12;
    skull.walkFrames = 14;
    skull.downFrames = 14;
    skull.width = 200;
    skull.height = 190;
    skull.widthOffSet = 0;
    m_data["skull"] = skull;
    // scarecrow 草人
    EnemyInfoData scarecrow;
    scarecrow.attackFrame = 10;
    scarecrow.attackFrames = 12;
    scarecrow.waitFrames = 12;
    scarecrow.walkFrames = 14;
    scarecrow.downFrames = 14;
    scarecrow.width = 190;
    scarecrow.height = 190;
    scarecrow.widthOffSet = 0;
    m_data["scarecrow"] = scarecrow;
    // pumpkin 南瓜头
    EnemyInfoData pumpkin;
    pumpkin.attackFrame = 10;
    pumpkin.attackFrames = 12;
    pumpkin.waitFrames = 12;
    pumpkin.walkFrames = 14;
    pumpkin.downFrames = 13;
    pumpkin.width = 180;
    pumpkin.height = 180;
    pumpkin.widthOffSet = 0;
    m_data["pumpkin"] = pumpkin;
    // muroidea 老鼠兵
    EnemyInfoData muroidea;
    muroidea.attackFrame = 7;
    muroidea.attackFrames = 12;
    muroidea.waitFrames = 12;
    muroidea.walkFrames = 14;
    muroidea.downFrames = 14;
    muroidea.width = 190;
    muroidea.height = 190;
    muroidea.widthOffSet = 0;
    m_data["muroidea"] = muroidea;
    // bat 蝙蝠
    EnemyInfoData bat;
    bat.attackFrame = 7;
    bat.attackFrames = 11;
    bat.waitFrames = 7;
    bat.walkFrames = 7;
    bat.downFrames = 0;
    bat.width = 160;
    bat.height = 140;
    bat.widthOffSet = 0;
    m_data["bat"] = bat;
    // crow 乌鸦
    EnemyInfoData crow;
    crow.attackFrame = 6;
    crow.attackFrames = 7;
    crow.waitFrames = 7;
    crow.walkFrames = 7;
    crow.downFrames = 0;
    crow.width = 180;
    crow.height = 150;
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