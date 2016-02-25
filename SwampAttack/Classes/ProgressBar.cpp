//
//  ProgressBar.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/22.
//
//

#include "ProgressBar.h"


ProgressBar::ProgressBar(std::string barName, std::string barBg)
{
    init();
    if (barBg.length()>0) {
        addChild(Sprite::create(ImagePath(barBg)));
    }
    
    timer = ProgressTimer::create(Sprite::create(ImagePath(barName)));
    timer->setType(ProgressTimer::Type::BAR);
    timer->setBarChangeRate(Vec2(1, 0));
    timer->setMidpoint(Vec2(1, 0));
    addChild(timer);
    timer->setPercentage(100);
    
}
ProgressBar::~ProgressBar()
{
}
void ProgressBar::setBarChangeRate(cocos2d::Vec2 r)
{
    timer->setBarChangeRate(r);
}
void ProgressBar::setMidpoint(cocos2d::Vec2 m)
{
    timer->setMidpoint(m);
}
void ProgressBar::setBarPositon(cocos2d::Vec2 point)
{
    timer->setPosition(point);
}
void ProgressBar::updatePercent(float per)
{
    timer->setPercentage(per);
}

void ProgressBar::setBarLeft()
{
    timer->setMidpoint(Vec2(1, 0));
}
void ProgressBar::setBarRight()
{
    timer->setMidpoint(Vec2(0, 0));
}
void ProgressBar::setBarUp()
{
    timer->setMidpoint(Vec2(0, 1));
}
void ProgressBar::setBarDown()
{
    timer->setMidpoint(Vec2(0, 0));
}

