//
//  BulletManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletManager.h"
#include "ConfigManager.h"

#include "PunctureBullet.h"
#include "CurveBullet.h"
#include "LiquidBullet.h"

BulletManager::BulletManager()
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("bulletTable");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string bulletId = iter->second;
        BulletModel * bulletModel = new BulletModel(data[bulletId]);
        m_bulletModelData[bulletId] = bulletModel;
    }
}
BulletManager::~BulletManager()
{
    
}
BulletManager * BulletManager::getInstance()
{
    static BulletManager _bulletManager;
    return &_bulletManager;
}
BulletModel * BulletManager::getBulletModelById(std::string _id)
{
    return m_bulletModelData[_id];
}
void BulletManager::fire(BulletParameter bp)
{
//    bp.m_num = 1;
    BulletModel * model = getBulletModelById(bp.m_modelId);
    
    for (int i = 0; i < bp.m_num; ++i) {
        Bullet * bullet = NULL;
        switch (model->getWeaponType())
        {
            case 2:
                bullet = new Bullet(bp);
                break;
            case 3:
                bullet = new PunctureBullet(bp);
                break;
            case 5:
                bullet = new LiquidBullet(bp);
                break;
            case 6:
                bullet = new CurveBullet(bp);
                break;
            default:
                bullet = new Bullet(bp);
                break;
        }
        bullet->setView();
        bullets.push_back(bullet);
    }
}
void BulletManager::gameLoop(float data)
{
    std::list<Bullet *>::iterator itr;
    for (itr = bullets.begin(); itr != bullets.end();) {
        Bullet * bullet = *itr;
        if (bullet->isCanDelete()) {
            bullets.erase(itr++);
            delete bullet;
        }else
        {
            itr++;
            bullet->gameLoop(data);
        }
    }
}
void BulletManager::resetData()
{
    std::list<Bullet *>::iterator itr;
    for (itr = bullets.begin(); itr != bullets.end();) {
        Bullet * bullet = *itr++;
        delete bullet;
    }
    bullets.clear();
}
std::list<Bullet*> BulletManager::getBulletData()
{
    return bullets;
}