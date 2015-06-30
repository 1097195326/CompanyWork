//
//  GameReliveLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/30.
//
//

#include "GameReliveLayer.h"
#include "GameDirector.h"
#include "GameUser.h"


GameReliveLayer::~GameReliveLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
GameReliveLayer::GameReliveLayer(RenderTexture * rt):
m_time(4)
{
    init();
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameReliveLayer::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    
    
    Sprite * scenebg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    scenebg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
    scenebg->setFlippedY(true);
    scenebg->setColor(Color3B::GRAY);
    addChild(scenebg);
    
    Sprite * bg = Sprite::create(ImagePath("healthShowBg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    
    addChild(bg);
    bg->setScale(0.8);
    
    Size bgSize = bg->getContentSize();
    
    Label * titleTex = Label::createWithTTF("continue ?",
                                             "fonts/Arial Black.ttf",
                                             40);
    titleTex->enableOutline(Color4B(0, 0, 0, 255),3);
    titleTex->setPosition(bgSize.width * 0.5,
                           bgSize.height * 0.65);
    bg->addChild(titleTex);
    
    m_timeLabel = Label::createWithTTF(StringUtils::format("%d",m_time),
                                  "fonts/Arial Black.ttf",
                                  100);
    m_timeLabel->enableOutline(Color4B(0, 0, 0, 255),4);
    m_timeLabel->setPosition(bgSize.width * 0.5, bgSize.height * 0.45);
    bg->addChild(m_timeLabel);
    
    MenuItemImage * continueButton = MenuItemImage::create(ImagePath("fight_relive_button.png"),
                                                           ImagePath("fight_relive_button.png"),
                                                           CC_CALLBACK_1( GameReliveLayer::continueGame, this));
    continueButton->setPosition(bgSize.width * 0.5,
                                bgSize.height * 0.2);
    
    Menu * buttonMenu = Menu::create(continueButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    bg->addChild(buttonMenu);
    
    int num = _G_U->getExpendPropNum();
    Label * buttonTex = Label::createWithTTF(StringUtils::format("%d x",num),
                                            "fonts/Arial Black.ttf",
                                            30);
    buttonTex->enableOutline(Color4B(0, 0, 0, 255),3);
    buttonTex->setPosition(bgSize.width * 0.48,
                          bgSize.height * 0.2);
    bg->addChild(buttonTex);
    
    Sprite * hpIcon = Sprite::create(ImagePath("hp1_icon.png"));
    hpIcon->setPosition(bgSize.width * 0.57,
                        bgSize.height * 0.2);
    hpIcon->setScale(0.5);
    bg->addChild(hpIcon);
    
    schedule(CC_SCHEDULE_SELECTOR(GameReliveLayer::updateTime), 1, 3, 0);
}
void GameReliveLayer::updateTime(float data)
{
    --m_time;
    m_timeLabel->setString(StringUtils::format("%d",m_time));
    if (m_time == 0)
    {
        removeFromParentAndCleanup(true);
        m_fightLayer->showOverLayer();
    }
}
void GameReliveLayer::setFightLayer(GameFightScene *layer)
{
    m_fightLayer = layer;
}
void GameReliveLayer::continueGame(cocos2d::Ref *pSender)
{
    if (_G_U->useExpendProp())
    {
        unschedule(CC_SCHEDULE_SELECTOR(GameReliveLayer::updateTime));
        _G_D->reliveGame();
        _G_D->continueGame();
        m_fightLayer->resumeGameActions();
        removeFromParentAndCleanup(true);
    }
}
bool GameReliveLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}