//
//  EnemyProgressBar.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/26.
//
//

#include "EnemyProgressBar.h"
#include "GameFightScene.h"
#include "EnemyManager.h"
#include "GameMapManager.h"


EnemyProgressBar::EnemyProgressBar():m_progress(0),m_enemyProgress(0)
{
    init();
    
    m_progressBar = new ProgressBar("fight_enemy_bar.png","fight_enemy_barbg.png");
    m_progressBar->autorelease();
    addChild(m_progressBar);
    m_progressBar->setBarLeft();
    m_progressBar->updatePercent(0);
    setPosition(_G_M_M->fightScene_EnemyBar_Position);
    
    m_headSpr = Sprite::create(ImagePath("enemy_head.png"));
    m_headSpr->setPosition(170, 0);
    addChild(m_headSpr);
    
    schedule(CC_SCHEDULE_SELECTOR(EnemyProgressBar::update), 1/30);
    _G_V->addChild(this,641);
}
EnemyProgressBar::~EnemyProgressBar()
{
//    delete m_progressBar;
}
void EnemyProgressBar::update(float data)
{
    if (m_progress >= m_enemyProgress)
    {
        return;
    }
    
    m_progress += data * 4;
    m_progressBar->updatePercent(m_progress);
//    log("enemy progress:%f",m_progress);
    m_headSpr->setPosition(170 -  (m_progress / 100.0f) * 340, 0);
}
void EnemyProgressBar::updateData()
{
    EnemyManager * _m = (EnemyManager *)m_sub;
    m_enemyProgress = _m->getEnemyProgress();
}