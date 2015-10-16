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
    
    m_verticalViewCount = m_verticalViewCount > m_totalCount ? m_totalCount : m_verticalViewCount;
    m_horizontalViewCount = m_horizontalViewCount > m_totalCount ? m_totalCount : m_horizontalViewCount;
    
    m_perOffSet = {0.0f,0.0f};
    m_currentIndex = 0;
    
    schedule(CC_SCHEDULE_SELECTOR(GameScrollHeadlerView::updateItems), 1/60);
}
GameScrollHeadlerView::~GameScrollHeadlerView()
{
    
}
void GameScrollHeadlerView::initView(int index)
{
//    if (index < 0)
//    {
//        index = 0;
//    }
//    if (index >= m_viewCount)
//    {
//        index = m_viewCount - 1;
//    }
    for (int i = 0; i < m_viewCount; ++i)
    {
        addHeadlerByIndex(i);
    }
//    m_currentIndex = index;
//    moveToViewAtIndex(m_currentIndex,true);

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
void GameScrollHeadlerView::moveToViewAtIndex(int index, bool direct)
{
//    log("m_currentIndex index :%d",m_currentIndex);
//    log("move to index :%d",index);
    if ((m_oritation == s_horizontal && m_viewWidth == m_itemWidth) ||
        (m_oritation == s_vertical && m_viewHeight == m_itemHeight))
    {
        if (index < 0)
        {
            index = 0;
        }else if ( index > m_totalCount)
        {
            index = m_totalCount;
        }
    }else
    {
        if (index < 0)
        {
            index = 0;
        }else if (index + m_viewCount > m_totalCount)
        {
            index = m_totalCount - m_viewCount;
        }
    }
    
    float toX = 0.0f;
    float toY = 0.0f;
    switch (m_oritation) {
        case s_vertical:
            toY = m_itemHeight * index;
//            if (m_currentIndex > index)
//            {
//                toY *= -1;
//            }
            break;
        case s_horizontal:
            toX = -m_itemWidth * index;
//            if (m_currentIndex < index)
//            {
//                toX *= -1;
//            }
            break;
    }
//    log("---:%f",toX);
//    log("---:%f",toY);
    if (direct)
    {
        m_scrollController->toOffSet(toX, toY);
    }else
    {
        m_scrollController->moveToOffSet(toX, toY);
    }
    
}
void GameScrollHeadlerView::moveAddView()
{
//    log("add view:%d",m_currentIndex);
    int index = m_currentIndex + 1;
    moveToViewAtIndex(index);
}
void GameScrollHeadlerView::moveMinusView()
{
//    log("minu view:%d",m_currentIndex);
    int index = m_currentIndex - 1;
    moveToViewAtIndex(index);
}
bool GameScrollHeadlerView::canMoveAddView()
{
    log("can add view:%d",m_currentIndex);
    if ((m_oritation == s_horizontal && m_viewWidth == m_itemWidth) ||
        (m_oritation == s_vertical && m_viewHeight == m_itemHeight))
    {
        return m_currentIndex < m_totalCount - 1;
    }
    return m_currentIndex + m_viewCount < m_totalCount  ;
}
bool GameScrollHeadlerView::canMoveMinusView()
{
    log("can minus view:%d",m_currentIndex);
    return m_currentIndex > 0;
}
void GameScrollHeadlerView::updateItems(float data)
{
    M_Vec2f offSet = m_scrollController->getOffSet();
    Vec2 offSetV = {offSet.x,offSet.y};
//    log("off set:%f:::%d",offSet.y,m_currentIndex);
    int index = m_currentIndex;
    
    switch (m_oritation) {
        case s_vertical:
        {
            int i = ((int)offSetV.y - (int)m_perOffSet.y)/(int)m_itemHeight;
            if (std::abs(i) >= 1)
            {
                index += i;
            }
        }
            break;
        case s_horizontal:
        {
//            int i = (int)((m_perOffSet.x - offSetV.x)/m_itemWidth);
//            if (std::abs(i) >= 1)
//            {
//                index += i;
//            }
            int i = ((int)(-offSetV.x) / m_itemWidth) - m_currentIndex;
            
            if (i > 0)
            {
                index += i;
            }else if (i < 0)
            {
                index += i;
            }
            
        }
            break;
        default:
            break;
    }
    
    if (index == m_currentIndex)
    {
        return;
    }
//    log("index :%d",index);
//    log("m_currentIndex :%d",m_currentIndex);
    
    if ((m_oritation == s_horizontal && m_viewWidth == m_itemWidth) ||
        (m_oritation == s_vertical && m_viewHeight == m_itemHeight)
        )
    {
        if (index < 0 || index > m_totalCount -1) {
            //        log("scroll data yue jie");
            //        log("index :%d",index);
            return;
        }
    }else
    {
        if (index < 0 || index > m_totalCount - m_viewCount) {
            //        log("scroll data yue jie");
            //        log("index :%d",index);
            return;
        }
    }
    
    if (index > m_currentIndex)
    {
        //        log("xia hua");
        //        log("index :%d",index);
        if (m_currentIndex >= 1)
        {
            GameScrollHeadler * headler = m_headlerData[m_currentIndex - 1];
            headler->removeFromParentAndCleanup(true);
        }
        if (m_currentIndex + m_viewCount < m_totalCount)
        {
            addHeadlerByIndex(m_currentIndex + m_viewCount);
        }
        
        m_currentIndex = index;
        m_perOffSet = offSetV;
    }
    else if (index < m_currentIndex && m_currentIndex > 0)
    {
        //        log("shang hua");
        //        log("index :%d",index);
        m_currentIndex = index;
        m_perOffSet = offSetV;
        if (m_currentIndex + m_viewCount < m_totalCount)
        {
            GameScrollHeadler * headler = m_headlerData[m_currentIndex + m_viewCount];
            headler->removeFromParentAndCleanup(true);
        }
        if (m_currentIndex >= 1)
        {
            addHeadlerByIndex(m_currentIndex - 1);
        }
    }
    m_target->moveToEndCall();
}
void GameScrollHeadlerView::addHeadlerByIndex(int index)
{
    GameScrollHeadler * headler = getHeadlerWithIndex(index);
    
//    Vec2 v_p;
//    
//    switch (m_oritation) {
//        case s_vertical:
//        {
//            v_p = Vec2(m_itemWidth * 0.5, 0.0 - m_itemHeight * (index + 1) + m_viewHeight + m_itemHeight * 0.5);
//        }
//            break;
//        case s_horizontal:
//        {
//            v_p = Vec2(m_itemWidth * (index + 1) - m_itemWidth * 0.5, m_itemHeight * 0.5);
//        }
//            break;
//        default:
//            break;
//    }
    addChildToScrollView(headler);
//    headler->setPosition(v_p);
    m_headlerData[index] = headler;
}
GameScrollHeadler * GameScrollHeadlerView::getHeadlerWithIndex(int index)
{
    assert(m_target);
    GameScrollHeadler * headler = m_target->getHeadlerByIndex(index,getTag());
    return headler;
}
void GameScrollHeadlerView::setHeadlerSelect(int index)
{
    GameScrollHeadler * headler = m_headlerData[index];
    if (headler) {
        headler->setHealderSelect();
    }
}
void GameScrollHeadlerView::setGetHeadlerTarget(GameScrollHeadlerTargetInterface * getHeadlerTarget)
{
    m_target = getHeadlerTarget;
}
void GameScrollHeadlerView::moveToEndCall()
{
    m_target->moveToEndCall();
}