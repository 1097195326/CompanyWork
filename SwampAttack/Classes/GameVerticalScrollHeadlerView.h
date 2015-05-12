//
//  GameVerticalScrollHeadlerView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#ifndef __SwampAttack__GameVerticalScrollHeadlerView__
#define __SwampAttack__GameVerticalScrollHeadlerView__

#include "GameVerticalScrollView.h"
#include "GameScrollHeadler.h"
#include "GameScrollHeadlerTargetInterface.h"


class GameVerticalScrollHeadlerView : public GameVerticalScrollView{
private:
    std::map<int,GameScrollHeadler *> m_headlerData;
    float   m_itemWidth;
    float   m_itemHeight;
    int     m_totalCount;
    int     m_viewCount;
    int     m_currentIndex;
    
    GameScrollHeadlerTargetInterface * m_target;
    
private:
    void    updateItems(float data);
    void    addHeadlerByIndex(int index);
    GameScrollHeadler * getHeadlerWithIndex(int index);
public:
    void    setGetHeadlerTarget(GameScrollHeadlerTargetInterface * getHeadlerTarget);
    void    initView();
public:
    GameVerticalScrollHeadlerView(float viewWidth ,
                                  float viewHeight,
                                  float itemWidth,
                                  float itemHeight,
                                  int   totalCount);
    ~GameVerticalScrollHeadlerView();
};

#endif /* defined(__SwampAttack__GameVerticalScrollHeadlerView__) */
