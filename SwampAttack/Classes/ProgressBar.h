//
//  ProgressBar.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/22.
//
//

#ifndef __SwampAttack__ProgressBar__
#define __SwampAttack__ProgressBar__

#include "BaseCode.h"

class ProgressBar : public Sprite
{
private:
    ProgressTimer   * timer;
    Sprite          * bg;
    
public:
    void    updatePercent(float per);
    void    setBarLeft();
    void    setBarRight();
    void    setBarPositon(Vec2 point);
public:
    ProgressBar(std::string barName, std::string barBg);
    ~ProgressBar();
    
    
};

#endif /* defined(__SwampAttack__ProgressBar__) */
