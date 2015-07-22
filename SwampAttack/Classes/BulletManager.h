//
//  BulletManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__BulletManager__
#define __SwampAttack__BulletManager__

#include "GameObject.h"
#include "Bullet.h"


class BulletManager : public GameObject {
private:
    std::map<std::string,BulletModel *> m_bulletModelData;
    std::map<int,std::string> m_hashHead;
    
    std::list<Bullet*> bullets;
    
public:
    void    fire(BulletParameter bp);
    std::list<Bullet*> getBulletData();
    void    resetData();
public:
    
    BulletManager();
    ~BulletManager();
    static BulletManager * getInstance();
    
    BulletModel * getBulletModelById(std::string _id);
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__BulletManager__) */
