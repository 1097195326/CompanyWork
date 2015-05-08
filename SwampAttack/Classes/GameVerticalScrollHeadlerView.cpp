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
GameVerticalScrollView(viewWidth,viewHeight),
m_itemWidth(itemWidth),
m_itemHeight(itemHeight),
m_totalCount(totalCount)
{
    m_viewCount = m_viewHeight / m_itemHeight + 1;
//    log("view count : %d",m_viewCount);
    for (int i = 0; i < m_viewCount; ++i)
    {
        addHeadlerByIndex(i);
    }
    m_currentIndex = 0;
    
    schedule(CC_SCHEDULE_SELECTOR(GameVerticalScrollHeadlerView::updateItems), 1/60);
}
GameVerticalScrollHeadlerView::~GameVerticalScrollHeadlerView()
{
    
}
void GameVerticalScrollHeadlerView::updateItems(float data)
{
    M_Vec2f offSet = m_scrollController->getOffSet();
    float offSetY = std::abs(offSet.y);
    int index = ((int)offSetY / (int)m_itemHeight);
    
    if (index < 0 || index > m_totalCount - m_viewCount) {
//        log("scroll data yue jie");
//        log("index :%d",index);
        return;
    }
    if (index > m_currentIndex)
    {
//        log("xia hua");
//        log("index :%d",index);
        GameScrollHeadler * headler = m_headlerData[m_currentIndex];
//        if (headler) {
            headler->removeFromParentAndCleanup(true);
            addHeadlerByIndex(m_currentIndex + m_viewCount);
            m_currentIndex = index;
//        }
    }
    else if (index < m_currentIndex && m_currentIndex > 0)
    {
//        log("shang hua");
//        log("index :%d",index);
        m_currentIndex = index;
        GameScrollHeadler * headler = m_headlerData[m_currentIndex + m_viewCount];
//        if (headler) {
            headler->removeFromParentAndCleanup(true);
            addHeadlerByIndex(m_currentIndex);
//        }
        
    }
}
void GameVerticalScrollHeadlerView::addHeadlerByIndex(int index)
{
    GameScrollHeadler * headler = getHeadlerWithIndex(index);
    Vec2 v_p = Vec2(m_itemWidth * 0.5, 0.0 - m_itemHeight * (index + 1) + m_viewHeight + m_itemHeight * 0.5);
    headler->setPosition(v_p);
    addChildToScrollView(headler);

    m_headlerData[index] = headler;
}
GameScrollHeadler * GameVerticalScrollHeadlerView::getHeadlerWithIndex(int index)
{
    GameScrollHeadler * headler = new GameScrollHeadler();
    return headler;
}
void GameVerticalScrollHeadlerView::setHeadlersData()
{
    
}