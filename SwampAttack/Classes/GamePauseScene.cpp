//
//  GamePauseScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/21.
//
//

#include "GamePauseScene.h"

Scene * GamePauseScene::scene(RenderTexture * rt)
{
    Scene * scene = Scene::create();
    GamePauseScene * layer = GamePauseScene::create();
    scene->addChild(layer,1);
    
    Sprite * bg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    bg->setPosition(visibleSize.width * 0.5,visibleSize.height * 0.5);
    bg->setFlippedY(true);
    bg->setColor(Color3B::GRAY);
    scene->addChild(bg);
    
    return scene;
}

bool GamePauseScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Sprite * bg = Sprite::create(ImagePath("pauseScene_bg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                    visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    
    return true;
}