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


class GameMapScene : public cocos2d::LayerColor
{
private:
    
    
public:
    CREATE_SCENE_FUNC(GameMapScene);
//    static Scene * scene()
//    {
//        Scene * scene = Scene::create();
//        LayerColor * layer = GameMapScene::create();
//        
//        scene->addChild(layer);
//        layer->setContentSize(Size(200, 400));
//        layer->setColor(Color3B(200, 0, 0));
//        return scene;
//    }
    CREATE_FUNC(GameMapScene);
    
    virtual bool    init();
    
    bool    touchBegan(Touch * touch, Event * event);
    void    touchMoved(Touch * touch, Event * event);
    void    touchEnd(Touch * touch, Event * event);
};


#endif /* defined(__SwampAttack__GameMapScene__) */
