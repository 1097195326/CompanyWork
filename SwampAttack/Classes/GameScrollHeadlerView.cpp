//
//  GameScrollHeadlerView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#include "GameScrollHeadlerView.h"


GameScrollHeadlerView::GameScrollHeadlerView(float viewWidth ,
                                                             float viewHeight,
                                                             float itemWidth,
                                                             float itemHeight,
                                                             int   totalCount):
GameScrollView(viewWidth,viewHeight),
m_itemWidth(itemWidth),
m_itemHeight(itemHeight),
m_totalCount(totalCount)
{
    m_verticalViewCount = m_viewHeight / m_itemHeight + 2;
    m_horizontalViewCount = m_viewWidth / m_itemWidth + 2;
    //    log("view count : %d",m_viewCount);
    
    m_currentIndex = 0;
    
    schedule(CC_SCHEDULE_SELECTOR(GameScrollHeadlerView::updateItems), 1/60);
}
GameScrollHeadlerView::~GameScrollHeadlerView()
{
    
}
void GameScrollHeadlerView::initView()
{
    
    for (int i = 0; i < m_viewCount; ++i)
    {
        addHeadlerByIndex(i);
    }
}
void GameScrollHeadlerView::reSetView()
{
    m_currentIndex = 0;
    removeAllChildFromScrollView();
    //    std::map<int,GameScrollHeadler *>::iterator iter;
    //    for (iter = m_headlerData.begin(); iter != m_headlerData.end(); ++iter)
    //    {
    //        iter->second->removeFromParentAndCleanup(true);
    //    }
    m_headlerData.clear();
    initView();
    
}
void GameScrollHeadlerView::reSetTotalCount(int num)
{
    m_totalCount = num;
}
void GameScrollHeadlerView::updateItems(float data)
{
    M_Vec2f offSet = m_scrollController->getOffSet();
    int index = 0;
    
    switch (m_oritation) {
        case s_vertical:
        {
            float offSetY = std::abs(offSet.y);
            index = ((int)offSetY / (int)m_itemHeight);
        }
            break;
        case s_horizontal:
        {
            float offSetX = std::abs(offSet.x);
            index = ((int)offSetX / (int)m_itemWidth);
        }
            break;
        default:
            break;
    }
    
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
void GameScrollHeadlerView::addHeadlerByIndex(int index)
{
    GameScrollHeadler * headler = getHeadlerWithIndex(index);
    
    Vec2 v_p;
    
    switch (m_oritation) {
        case s_vertical:
        {
            v_p = Vec2(m_itemWidth * 0.5, 0.0 - m_itemHeight * (index + 1) + m_viewHeight + m_itemHeight * 0.5);
        }
            break;
        case s_horizontal:
        {
            v_p = Vec2(m_itemHeight * 0.5, m_itemWidth * (index + 1) - m_itemWidth * 0.5);
        }
            break;
        default:
            break;
    }
    addChildToScrollView(headler);
    headler->setPosition(v_p);
    m_headlerData[index] = headler;
}
GameScrollHeadler * GameScrollHeadlerView::getHeadlerWithIndex(int index)
{
    assert(m_target);
    GameScrollHeadler * headler = m_target->getHeadlerByIndex(index,getTag());
    return headler;
}
void GameScrollHeadlerView::setGetHeadlerTarget(GameScrollHeadlerTargetInterface * getHeadlerTarget)
{
    m_target = getHeadlerTarget;
}