//
//  GameOverScene.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#include "GameOverScene.h"
#include "GameMapScene.h"
#include "GameShopScene.h"
#include "GameLoadingScene.h"

#include "GuanQiaManager.h"
#include "GunManager.h"
#include "PropManager.h"
#include "GunManager.h"
#include "DefenseBuildingManager.h"

#include "GameDirector.h"
#include "GameUser.h"
#include "House.h"

#include "MobClickCpp.h"
#include "BaseUtil.h"


//#include "GameDirector.h"
//#include "EnemyManager.h"
//#include "GameLoading.h"


Scene * GameOverScene::scene(GameOverStatus status,RenderTexture * rt)
{
    Scene * scene = Scene::create();
    GameOverScene * layer = new GameOverScene(status,rt);
    layer->autorelease();
    layer->init();
    scene->addChild(layer,1);
    
    return scene;
}
GameOverScene::GameOverScene(GameOverStatus status, RenderTexture * rt)
{
    m_overStatus = status;
    
    Sprite * scenebg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    scenebg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
    scenebg->setFlippedY(true);
    scenebg->setColor(Color3B::GRAY);
    addChild(scenebg);
}
GameOverScene::~GameOverScene()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();

    LayerColor * layerColor = LayerColor::create(Color4B(0, 0, 0, 200));
    addChild(layerColor);
//    layerColor->runAction(FadeTo::create(0.3, 200));
    
    Sprite * bg = Sprite::create(ImagePath("overScene_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    int canGetGold = _G_D->getGoldNum();;
    
    Sprite * title = NULL;
    
    GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    int starNum = House::getInstance()->getStarNum();
    
    if (m_overStatus == o_win)
    {
        umeng::MobClickCpp::finishLevel(curGuanqia->getId().c_str());
        
        title = Sprite::create(ImagePath("overScene_winTitle.png"));
        
        curGuanqia->setGuanqiaWin();
        if (starNum > curGuanqia->getStarNum())
        {
            curGuanqia->setStarNum(starNum);
        }
        GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
        
        GunManager::getInstance()->checkUnlock(this);
        PropManager::getInstance()->checkUnlock(this);
        DefenseBuildingManager::getInstance()->checkUnlock(this);
        
        if (nextGuanqia && !nextGuanqia->isUnlock())
        {
//            log("scene index:%d",nextGuanqia->getSceneIndex());
//            log(" index:%d",nextGuanqia->getCheckPoint());
            nextGuanqia->unlockGuanqia();
            _G_U->setLastSceneIndex(nextGuanqia->getSceneIndex());
            _G_U->setLastGuanqiaIndex(nextGuanqia->getCheckPoint());
        }
//        if (nextGuanqia)
//        {
//            nextGuanqia->unlockGuanqia();
//        }
        
//        GuanQiaManager::getInstance()->set(++guanqiaIndex);
        
        canGetGold += curGuanqia->getThroughGold();
    }else
    {
        umeng::MobClickCpp::failLevel(curGuanqia->getId().c_str());
        
        title = Sprite::create(ImagePath("overScene_failTitle.png"));
        
        if (!(_G_U->isHaveGuide()))
        {
            _G_U->setIsGuiding(true);
        }
    }
    title->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                       m_visibleOrigin.y + m_visibleSize.height * 0.7);
    addChild(title);
    
    for (int i = 1; i <= 3; ++i)
    {
        string starName;
        if (i <= starNum)
        {
            starName = "overScene_lightStar.png";
        }else
        {
            starName = "overScene_grayStar.png";
        }
        Sprite * star = Sprite::create(ImagePath(starName));
        Vec2 starPoint = Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                              m_visibleOrigin.y + m_visibleSize.height * 0.53);
        star->setPosition(starPoint + Vec2(-80 + 80 * (i-1), 30 - i%2 * 10));
        addChild(star);
    }
    
    
    int widthOffset = 120;
    MenuItemImage * gotoMapButton = MenuItemImage::create(ImagePath("overScene_tomap.png"),
                                                       ImagePath("overScene_tomap.png"),
                                                       CC_CALLBACK_1( GameOverScene::gotoMap, this));
    MenuItemImage * restartButton = MenuItemImage::create(ImagePath("overScene_restart.png"),
                                                          ImagePath("overScene_restart.png"),
                                                          CC_CALLBACK_1( GameOverScene::restartGame, this));
    Sprite * getIcon = Sprite::create(ImagePath("over_get_icon.png"));
    getIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.41,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    addChild(getIcon);
    
    Label * goldLabel = Label::createWithTTF(StringUtils::format("%d",canGetGold),
                                             "fonts/Arial Black.ttf",
                                             40);
    goldLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.52,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    goldLabel->setAdditionalKerning(-3);
    goldLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    addChild(goldLabel);
    
    Sprite * jinbiIcon = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbiIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.6,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    addChild(jinbiIcon);
    
    int userGold = _G_U->getUserGold() + canGetGold;
    _G_U->setUserGold(userGold);
    
    Menu * buttonMenu = NULL;
    
    MenuItemImage * gotoShopButton = MenuItemImage::create(ImagePath("overScene_toShop.png"),
                                                       ImagePath("overScene_toShop.png"),
                                                       CC_CALLBACK_1( GameOverScene::gotoShop, this));
    gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset,
                               m_visibleOrigin.y + m_visibleSize.height * 0.22);
    restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + m_visibleSize.height * 0.22);
    gotoShopButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset + 10,
                            m_visibleOrigin.y + m_visibleSize.height * 0.24 - 13);

    buttonMenu = Menu::create(gotoMapButton,restartButton,gotoShopButton, NULL);
    
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    
    GunManager::getInstance()->saveBullet();
    
    _G_D->resetGameData();
    
    if (_G_U->isGuiding())
    {
        guideIndex = 0;
        GCCsvHelper * cgHelper = _C_M->getCsvHelperByName("userGuide");
        std::map<int,std::string> m_hashHead = cgHelper->getHashHead();
        Json::Value data = cgHelper->getJsonData();
        std::map<int,std::string>::iterator iter;
        for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
            std::string cgId = iter->second;
            Json::Value d1 = data[cgId];
            std::string cgStrId = d1["GuideID"].asString();
            std::string cgStr = _C_M->getTranslateById(cgStrId);
            guideText.push_back(cgStr);
        }
        auto spriteFrameCache = SpriteFrameCache::getInstance();
        spriteFrameCache->addSpriteFramesWithFile(ImagePath("XinshouYindao.plist"));
        
        schedule(CC_SCHEDULE_SELECTOR(GameOverScene::userGuide), 3, 4, 0.1);
    }
    return true;
}
void GameOverScene::userGuide(float data)
{
    if(guideIndex == 0)
    {
        Sprite * people = Sprite::create(ImagePath("guide_people.png"));
        Size p_size = people->getContentSize();
        people->setPosition(m_visibleOrigin.x + m_visibleSize.width + p_size.width * 0.5,
                            m_visibleOrigin.y + p_size.height * 0.5);
        addChild(people,999);
        people->runAction(MoveBy::create(0.3, Vec2(-p_size.width, 0)));
        
        Sprite * textBg = Sprite::create(ImagePath("guide_textBg.png"));
        Size bg_size = textBg->getContentSize();
        textBg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                            m_visibleOrigin.y - bg_size.height * 0.5);
        addChild(textBg,999);
        textBg->runAction(Sequence::create(DelayTime::create(0.3),
                                           MoveBy::create(0.3, Vec2(0, bg_size.height)),
                                           NULL));
        
        
        guideTextLabel = Label::createWithTTF(guideText[guideIndex], FontPath, 30);
        guideTextLabel->setLineHeight(35);
//        guideTextLabel->setDimensions(m_visibleSize.width * 0.8, m_visibleSize.height * 0.18);
        guideTextLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                    m_visibleOrigin.y - bg_size.height * 0.5);
        addChild(guideTextLabel,999);
        guideTextLabel->runAction(Sequence::create(DelayTime::create(0.3),
                                                   MoveBy::create(0.3, Vec2(0, bg_size.height)),
                                                   NULL));
        
    }else if (guideIndex == 3)
    {
        Action * dianJiAc = RepeatForever::create(Sequence::create(BaseUtil::makeAnimateWithNameAndIndex("shou", 6),
                                                                   DelayTime::create(0.6),
                                                                   NULL));
        Sprite * m_shou = Sprite::create();
        addChild(m_shou,999);
        m_shou->setScale(0.5);
        m_shou->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + 130,
                            m_visibleOrigin.y + m_visibleSize.height * 0.24 - 38);
        m_shou->runAction(dianJiAc);
    }
    else if(guideIndex <=2 && guideIndex >= 1)
    {
        guideTextLabel->setString(guideText[guideIndex]);
        guideTextLabel->setOpacity(0);
        guideTextLabel->runAction(Sequence::create(DelayTime::create(0.5),
                                           FadeIn::create(0.5),
                                           NULL));
    }
    guideIndex += 1;
}
void GameOverScene::restartGame(cocos2d::Ref *pSender)
{
    if (_G_U->isGuiding())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    Director::getInstance()->replaceScene(GameLoadingScene::scene(guanqia->getId()));
}
void GameOverScene::gotoMap(cocos2d::Ref *pSender)
{
    if (_G_U->isGuiding())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
void GameOverScene::gotoShop(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameShopScene::scene());
}
//void GameOverScene::nextGuanqia(cocos2d::Ref *pSender)
//{
//    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
//    GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
//    GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
//    Director::getInstance()->replaceScene(GameLoadingScene::scene(nextGuanqia->getId()));
//}

bool GameOverScene::touchBegan(Touch *touch, Event *event)
{
    return true;
}