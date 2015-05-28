//
//  GameHorizontalScrollHeadlerView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#include "GameHorizontalScrollHeadlerView.h"


GameHorizontalScrollHeadlerView::GameHorizontalScrollHeadlerView(float viewWidth ,
                                                             float viewHeight,
                                                             float itemWidth,
                                                             float itemHeight,
                                                             int   totalCount):
GameScrollHeadlerView(viewWidth,viewHeight,itemWidth,itemHeight,totalCount)
{
    setScrollHorizontal(true);
    setScrollOritation();
    m_viewCount = m_oritation == s_vertical ? m_verticalViewCount : m_horizontalViewCount;
    
}
GameHorizontalScrollHeadlerView::~GameHorizontalScrollHeadlerView()
{
    
}
void GameHorizontalScrollHeadlerView::setScrollOritation()
{
    m_oritation = s_horizontal;
}
