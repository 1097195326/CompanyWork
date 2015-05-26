//
//  EnemyProgressBar.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/26.
//
//

#ifndef __SwampAttack__EnemyProgressBar__
#define __SwampAttack__EnemyProgressBar__

#include "GameObserver.h"
#include "ProgressBar.h"
#include "BaseCode.h"

class EnemyProgressBar :public Sprite,  public GameObserver {
private:
    ProgressBar *   m_progressBar;
    float           m_enemyProgress;
    float           m_progress;
public:
    EnemyProgressBar();
    ~EnemyProgressBar();
    void    updateData();
    void    update(float data);
};

#endif /* defined(__SwampAttack__EnemyProgressBar__) */
