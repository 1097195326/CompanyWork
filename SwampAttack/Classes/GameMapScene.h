//
//  GameMapScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/5.
//
//

#ifndef __SwampAttack__GameMapScene__
#define __SwampAttack__GameMapScene__

#include "BaseCode.h"
#include "GameScrollHeadlerTargetInterface.h"
#include "GameHorizontalScrollHeadlerView.h"
#include "UserDelegatLayer.h"


class GameMapScene : public UserDelegateLayer,
public GameScrollHeadlerTargetInterface
{
private:
    MenuItem * m_leftItem ;
    MenuItem * m_rightItem;
    GameHorizontalScrollHeadlerView * m_scrollView;
    
    
public:
    CREATE_SCENE_FUNC(GameMapScene);
    CREATE_FUNC(GameMapScene);
    
    virtual bool    init();
    
    GameScrollHeadler * getHeadlerByIndex(int index,int viewTag);
    
    
    void    homeButtonFuc(Ref * psender);
    void    shopButtonFuc(Ref * psender);
    void    leftButtonFuc(Ref * psender);
    void    rightButtonFuc(Ref * psender);
    
    void    moveToEndCall();
    
    
};


#endif /* defined(__SwampAttack__GameMapScene__) */
