//
//  GameVerticalScrollHeadlerView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#include "GameVerticalScrollHeadlerView.h"

GameVerticalScrollHeadlerView::GameVerticalScrollHeadlerView(float viewWidth ,
                                                             float viewHeight,
                                                             float itemWidth,
                                                             float itemHeight,
                                                             int   totalCount):
GameScrollHeadlerView(viewWidth,viewHeight,itemWidth,itemHeight,totalCount)
{
    setScrollVertical(true);
    setScrollOritation();
    m_viewCount = m_oritation == s_vertical ? m_verticalViewCount : m_horizontalViewCount;
    
}
GameVerticalScrollHeadlerView::~GameVerticalScrollHeadlerView()
{
    
}
void GameVerticalScrollHeadlerView::setScrollOritation()
{
    m_oritation = s_vertical;
}