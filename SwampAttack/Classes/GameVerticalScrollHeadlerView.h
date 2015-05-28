//
//  GameVerticalScrollHeadlerView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/7.
//
//

#ifndef __SwampAttack__GameVerticalScrollHeadlerView__
#define __SwampAttack__GameVerticalScrollHeadlerView__

#include "GameScrollHeadlerView.h"


class GameVerticalScrollHeadlerView : public GameScrollHeadlerView{
private:
    
public:
    GameVerticalScrollHeadlerView(float viewWidth ,
                                  float viewHeight,
                                  float itemWidth,
                                  float itemHeight,
                                  int   totalCount);
    ~GameVerticalScrollHeadlerView();
    
    void setScrollOritation();
};

#endif /* defined(__SwampAttack__GameVerticalScrollHeadlerView__) */
