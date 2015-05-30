//
//  GameScrollHeadlerView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#ifndef __SwampAttack__GameScrollHeadlerView__
#define __SwampAttack__GameScrollHeadlerView__

#include "GameScrollView.h"
#include "GameScrollHeadler.h"
#include "GameScrollHeadlerTargetInterface.h"

enum ScrollOritation
{
    s_vertical,
    s_horizontal,
};

class GameScrollHeadlerView : public GameScrollView{
protected:
    std::map<int,GameScrollHeadler *> m_headlerData;
    float   m_itemWidth;
    float   m_itemHeight;
    Vec2    m_perOffSet;
    int     m_totalCount;
    int     m_verticalViewCount;
    int     m_horizontalViewCount;
    int     m_viewCount;
    int     m_currentIndex;
    ScrollOritation m_oritation;
    
    GameScrollHeadlerTargetInterface * m_target;
    
private:
    void    updateItems(float data);
    void    addHeadlerByIndex(int index);
    GameScrollHeadler * getHeadlerWithIndex(int index);
public:
    void    setGetHeadlerTarget(GameScrollHeadlerTargetInterface * getHeadlerTarget);
    void    initView();
    void    reSetView();
    void    reSetTotalCount(int num);
    void    moveToViewAtIndex(int index);
    void    moveAddView();
    void    moveMinusView();
    bool    canMoveAddView();
    bool    canMoveMinusView();
    virtual void setScrollOritation() = 0;
public:
    GameScrollHeadlerView(float viewWidth ,
                                  float viewHeight,
                                  float itemWidth,
                                  float itemHeight,
                                  int   totalCount);
    ~GameScrollHeadlerView();
};


#endif /* defined(__SwampAttack__GameScrollHeadlerView__) */
