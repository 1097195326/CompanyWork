//
//  GameFightScene.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__GameFightScene__
#define __SwampAttack__GameFightScene__

#include "BaseCode.h"
#include "GameObserver.h"

#define _G_V GameFightScene::getInstance()

class GameFightScene : public cocos2d::Layer,public GameObserver
{
private:
    EventListenerTouchOneByOne * m_listener;
    Label  * m_goldNumLabel;
    Vector<Node*>  m_actions;
public:
    static  Scene * scene();
    static  GameFightScene * getInstance();
    GameFightScene();
    ~GameFightScene();
    
    virtual bool    init();
    void    updateData();
    void    showOverLayer();
    void    shopGameActions();
    void    resumeGameActions();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMoved(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
    
    
    void    pauseGame(Ref * pSender);
    void    addBulletTexiao(Vec2 position);
    void    removeBulletTexiao(Node * pSender);
    RenderTexture * getFightSceneTex();
};

#endif /* defined(__SwampAttack__GameFightScene__) */
