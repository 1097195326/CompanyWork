//
//  GameHorizontalScrollView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#include "GameHorizontalScrollView.h"


GameHorizontalScrollView::GameHorizontalScrollView(float width, float height):
GameScrollView(width,height)
{
    setScrollHorizontal(true);
}
GameHorizontalScrollView::~GameHorizontalScrollView()
{
    
}