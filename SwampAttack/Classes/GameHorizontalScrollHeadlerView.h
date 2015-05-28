//
//  GameHorizontalScrollHeadlerView.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#ifndef __SwampAttack__GameHorizontalScrollHeadlerView__
#define __SwampAttack__GameHorizontalScrollHeadlerView__

#include "GameScrollHeadlerView.h"


class GameHorizontalScrollHeadlerView : public GameScrollHeadlerView{
private:
    
public:
    GameHorizontalScrollHeadlerView(float viewWidth ,
                                  float viewHeight,
                                  float itemWidth,
                                  float itemHeight,
                                  int   totalCount);
    ~GameHorizontalScrollHeadlerView();
    
    void setScrollOritation();
};

#endif /* defined(__SwampAttack__GameHorizontalScrollHeadlerView__) */
