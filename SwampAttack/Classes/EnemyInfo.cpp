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
    // wolfArmor 狼人
    EnemyInfoData wolfArmor;
    wolfArmor.attackFrame = 8;
    wolfArmor.attackFrames = 11;
    wolfArmor.hurtHeavyFrames = 9;
    wolfArmor.hurtLightFrames = 5;
    wolfArmor.hurtOnFrames = 5;
    wolfArmor.walkFrames = 14;
    wolfArmor.downFrames = 0;
    wolfArmor.width = 260;
    wolfArmor.height = 130;
    wolfArmor.widthOffSet = 0;
    m_data["wolf_armor"] = wolfArmor;
    //snowman
    EnemyInfoData snowman;
    snowman.attackFrame = 8;
    snowman.attackFrames = 11;
    snowman.hurtHeavyFrames = 9;
    snowman.hurtLightFrames = 5;
    snowman.hurtOnFrames = 5;
    snowman.walkFrames = 14;
    snowman.downFrames = 13;
    snowman.width = 300;
    snowman.height = 250;
    snowman.widthOffSet = 0;
    m_data["snowman"] = snowman;
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
    // skull 骷髅射手
    EnemyInfoData skull_a;
    skull_a.attackFrame = 8;
    skull_a.attackFrames = 14;
    skull_a.hurtHeavyFrames = 9;
    skull_a.hurtLightFrames = 5;
    skull_a.hurtOnFrames = 5;
    skull_a.walkFrames = 14;
    skull_a.downFrames = 13;
    skull_a.width = 180;
    skull_a.height = 180;
    skull_a.widthOffSet = 0;
    m_data["skull_a"] = skull_a;
    // skull 骷髅盾兵
    EnemyInfoData skull_shield;
    skull_shield.attackFrame = 8;
    skull_shield.attackFrames = 12;
    skull_shield.hurtHeavyFrames = 10;
    skull_shield.hurtLightFrames = 6;
    skull_shield.hurtOnFrames = 5;
    skull_shield.walkFrames = 14;
    skull_shield.downFrames = 14;
    skull_shield.width = 180;
    skull_shield.height = 180;
    skull_shield.widthOffSet = 0;
    m_data["skull_shield"] = skull_shield;
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
    // Muroidea 老鼠兵
    EnemyInfoData muroideaArmor;
    muroideaArmor.attackFrame = 5;
    muroideaArmor.attackFrames = 11;
    muroideaArmor.hurtHeavyFrames = 9;
    muroideaArmor.hurtLightFrames = 5;
    muroideaArmor.hurtOnFrames = 5;
    muroideaArmor.walkFrames = 14;
    muroideaArmor.downFrames = 13;
    muroideaArmor.width = 180;
    muroideaArmor.height = 90;
    muroideaArmor.widthOffSet = 0;
    m_data["Muroidea_armor"] = muroideaArmor;
    //恶僧
    EnemyInfoData butcher;
    butcher.attackFrame = 5;
    butcher.attackFrames = 11;
    butcher.hurtHeavyFrames = 9;
    butcher.hurtLightFrames = 5;
    butcher.hurtOnFrames = 5;
    butcher.walkFrames = 14;
    butcher.downFrames = 13;
    butcher.width = 201;
    butcher.height = 154;
    butcher.widthOffSet = 0;
    m_data["butcher"] = butcher;
    //吸血鬼
    EnemyInfoData vampire;
    vampire.attackFrame = 5;
    vampire.attackFrames = 11;
    vampire.hurtHeavyFrames = 10;
    vampire.hurtLightFrames = 5;
    vampire.hurtOnFrames = 5;
    vampire.walkFrames = 14;
    vampire.downFrames = 13;
    vampire.width = 250;
    vampire.height = 200;
    vampire.widthOffSet = 0;
    m_data["vampire"] = vampire;
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
    // bat 蝙蝠
    EnemyInfoData bee;
    bee.attackFrame = 7;
    bee.attackFrames = 10;
    bee.walkFrames = 4;
    bee.downFrames = 13;
    bee.width = 150;
    bee.height = 150;
    bee.widthOffSet = 0;
    m_data["bee"] = bee;
    // demon 蝙蝠
    EnemyInfoData demon;
    demon.attackFrame = 7;
    demon.attackFrames = 9;
    demon.walkFrames = 7;
    demon.downFrames = 13;
    demon.width = 170;
    demon.height = 170;
    demon.widthOffSet = 0;
    m_data["demon"] = demon;
    // bat_armor
    EnemyInfoData demonArmor;
    demonArmor.attackFrame = 7;
    demonArmor.attackFrames = 9;
    demonArmor.walkFrames = 7;
    demonArmor.width = 170;
    demonArmor.height = 85;
    demonArmor.widthOffSet = 0;
    m_data["demon_armor"] = demonArmor;
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
    // zombieking 僵尸王
    EnemyInfoData zombieking;
    zombieking.attackFrame = 8;
    zombieking.attackFrames = 11;
    zombieking.hurtHeavyFrames = 9;
    zombieking.hurtLightFrames = 5;
    zombieking.hurtOnFrames = 5;
    zombieking.walkFrames = 13;
    zombieking.downFrames = 13;
    zombieking.width = 330;
    zombieking.height = 330;
    zombieking.widthOffSet = 0;
    m_data["zombieking"] = zombieking;
    // scareking 草人王
    EnemyInfoData scareking;
    scareking.attackFrame = 7;
    scareking.attackFrames = 11;
    scareking.hurtHeavyFrames = 9;
    scareking.hurtLightFrames = 5;
    scareking.hurtOnFrames = 5;
    scareking.walkFrames = 14;
    scareking.downFrames = 13;
    scareking.width = 420;
    scareking.height = 350;
    scareking.widthOffSet = 0;
    m_data["scareking"] = scareking;
    // skullking 骷髅王
    EnemyInfoData skullking;
    skullking.attackFrame = 8;
    skullking.attackFrames = 11;
    skullking.hurtHeavyFrames = 9;
    skullking.hurtLightFrames = 5;
    skullking.hurtOnFrames = 5;
    skullking.walkFrames = 14;
    skullking.downFrames = 13;
    skullking.width = 380;
    skullking.height = 350;
    skullking.widthOffSet = 0;
    m_data["skullking"] = skullking;
    // skullking 骷髅王2
    EnemyInfoData skullking2;
    skullking2.attackFrame = 8;
    skullking2.attackFrames = 12;
    skullking2.hurtHeavyFrames = 10;
    skullking2.hurtLightFrames = 6;
    skullking2.hurtOnFrames = 5;
    skullking2.walkFrames = 14;
    skullking2.downFrames = 14;
    skullking2.width = 380;
    skullking2.height = 350;
    skullking2.widthOffSet = 0;
    m_data["skullking2"] = skullking2;
    // wolfking 狼王
    EnemyInfoData wolfking;
    wolfking.attackFrame = 8;
    wolfking.attackFrames = 11;
    wolfking.hurtHeavyFrames = 9;
    wolfking.hurtLightFrames = 5;
    wolfking.hurtOnFrames = 5;
    wolfking.walkFrames = 14;
    wolfking.downFrames = 13;
    wolfking.width = 470;
    wolfking.height = 470;
    wolfking.widthOffSet = 0;
    m_data["wolfking"] = wolfking;
    // wolfking 狼王
    EnemyInfoData wolfking2;
    wolfking2.attackFrame = 8;
    wolfking2.attackFrames = 12;
    wolfking2.hurtHeavyFrames = 10;
    wolfking2.hurtLightFrames = 6;
    wolfking2.hurtOnFrames = 5;
    wolfking2.walkFrames = 14;
    wolfking2.downFrames = 14;
    wolfking2.width = 470;
    wolfking2.height = 470;
    wolfking2.widthOffSet = 0;
    m_data["wolfking2"] = wolfking2;
    //butcherking
    EnemyInfoData butcherking;
    butcherking.attackFrame = 8;
    butcherking.attackFrames = 12;
    butcherking.hurtHeavyFrames = 10;
    butcherking.hurtLightFrames = 6;
    butcherking.hurtOnFrames = 5;
    butcherking.walkFrames = 14;
    butcherking.downFrames = 14;
    butcherking.width = 550;
    butcherking.height = 450;
    butcherking.widthOffSet = 0;
    m_data["butcherking"] = butcherking;
    //snowmanking
    EnemyInfoData snowmanking;
    snowmanking.attackFrame = 8;
    snowmanking.attackFrames = 12;
    snowmanking.hurtHeavyFrames = 10;
    snowmanking.hurtLightFrames = 6;
    snowmanking.hurtOnFrames = 5;
    snowmanking.walkFrames = 14;
    snowmanking.downFrames = 14;
    snowmanking.width = 500;
    snowmanking.height = 400;
    snowmanking.widthOffSet = 0;
    m_data["snowmanking"] = snowmanking;
    //vampireking
    EnemyInfoData vampireking;
    vampireking.attackFrame = 8;
    vampireking.attackFrames = 12;
    vampireking.hurtHeavyFrames = 10;
    vampireking.hurtLightFrames = 6;
    vampireking.hurtOnFrames = 5;
    vampireking.walkFrames = 14;
    vampireking.downFrames = 14;
    vampireking.width = 400;
    vampireking.height = 400;
    vampireking.widthOffSet = 0;
    m_data["vampireking"] = vampireking;
    // demonking
    EnemyInfoData demonking;
    demonking.attackFrame = 7;
    demonking.attackFrames = 10;
    demonking.walkFrames = 7;
    demonking.downFrames = 13;
    demonking.width = 450;
    demonking.height = 400;
    demonking.widthOffSet = 0;
    m_data["demonking"] = demonking;
    
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