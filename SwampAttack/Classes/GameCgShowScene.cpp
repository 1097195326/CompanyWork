//
//  GameCgShowScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/10.
//
//

#include "GameCgShowScene.h"
#include "GameHomeScene.h"

#include "ConfigManager.h"


Scene * GameCgShowScene::scene()
{
    Scene * scene = Scene::create();
    GameCgShowScene * layer = GameCgShowScene::create();
    scene->addChild(layer);
    
    return scene;
}
GameCgShowScene::~GameCgShowScene()
{
    //    log("home scene release");
    unschedule(CC_SCHEDULE_SELECTOR(GameCgShowScene::updateCg));
}
bool GameCgShowScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    GCCsvHelper * cgHelper = _C_M->getCsvHelperByName("cgText");
    std::map<int,std::string> m_hashHead = cgHelper->getHashHead();
    Json::Value data = cgHelper->getJsonData();
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        std::string cgId = iter->second;
        Json::Value d1 = data[cgId];
        std::string cgStrId = d1["SceneID"].asString();
        std::string cgStr = _C_M->getTranslateById(cgStrId);
//        log("cg str:%s",cgStr.c_str());
        cgText.push_back(cgStr);
    }
    
    m_index = 2;
    
    m_spr1 = Sprite::create(ImagePath("CG01.jpg"));
    m_spr1->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5 - 40);
    addChild(m_spr1);
    m_spr1->setScale(1.35);
    
    m_text = Label::createWithTTF(cgText[0], "fonts/mimi.ttf", 30);
    m_text->setLineHeight(35);
    m_text->setDimensions(m_visibleSize.width * 0.8, m_visibleSize.height * 0.18);
    m_text->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                        m_visibleOrigin.y + m_visibleSize.height * 0.15);
    addChild(m_text);
    
    MenuItem * toHomeItem = MenuItemImage::create(ImagePath("cgSkip.png"),
                                                 ImagePath("cgSkip.png"),
                                                 CC_CALLBACK_1(GameCgShowScene::skipToHomeScene, this));
    
    toHomeItem->setPosition(m_visibleOrigin.x + m_visibleSize.width - 150,
                           m_visibleOrigin.y + 60);
    Menu * buttonMenu = Menu::create(toHomeItem, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    schedule(CC_SCHEDULE_SELECTOR(GameCgShowScene::updateCg), 3, 4, 3);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath("cgSceneMus.mp3")).c_str(),true);
    
    return true;
}
void GameCgShowScene::updateCg(float data)
{
//    m_spr2 = Sprite::create(ImagePath(StringUtils::format("CG%002d.jpg",m_index)));
//    m_spr2->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
//                        m_visibleOrigin.y + m_visibleSize.height * 0.5);
//    addChild(m_spr2);

    if (m_index == 5)
    {
        skipToHomeScene(NULL);
    }else
    {
        m_spr1->setTexture(ImagePath(StringUtils::format("CG%002d.jpg",m_index)));
        m_spr1->setOpacity(0);
        m_spr1->runAction(FadeIn::create(0.5));
        m_text->setString(cgText[m_index-1]);
        m_text->setOpacity(0);
        m_text->runAction(Sequence::create(DelayTime::create(0.5),
                                           FadeIn::create(0.5),
                                           NULL));
        
        ++m_index;
    }
    
}
void GameCgShowScene::swapEnd()
{
    
}
void GameCgShowScene::skipToHomeScene(cocos2d::Ref *pSender)
{
//    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameHomeScene::scene());
}