#include "AppDelegate.h"

#include "HelloWorldScene.h"
#include "GameFightScene.h"
#include "GameMapScene.h"
#include "GameShopScene.h"
#include "GameOverScene.h"
#include "GameHomeScene.h"
#include "GameCgShowScene.h"
#include "GameUser.h"

#include "MobClickCpp.h"


USING_NS_CC;


Size m_winSize;
Size m_visibleSize;
Vec2 m_visibleOrigin;

int _G_AddTime = 300;
//extern  Size    winSize;
//extern  Size    visibleSize;
//extern  Vec2    visibleOrigin;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    
    MOBCLICKCPP_START_WITH_APPKEY("56148cf067e58ed28e0058bb");
    
    Size sreenSize = glview->getFrameSize();
    Size sourceSize = {1136, 640};
    Size designSize = {1136.0f, 640.0f};
    
//    director->setContentScaleFactor(1.0f);
//    glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
    
    switch (CC_TARGET_PLATFORM) {
        case CC_PLATFORM_IOS:
        {
            director->setContentScaleFactor(1.0f);
//            glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
            if (sreenSize.width == 960)
            {
                glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_WIDTH);
            }else
            {
                glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
            }
        }
            break;
        case CC_PLATFORM_ANDROID:
        {
            director->setContentScaleFactor(1.0f);
            glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
        }
            break;
        default:
        {
            director->setContentScaleFactor(1.0f);
            glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
        }
            break;
    }
    
    m_winSize = Director::getInstance()->getWinSize();
    m_visibleSize = Director::getInstance()->getVisibleSize();
    m_visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    log("sreenSize size w:%f,h:%f",sreenSize.width,sreenSize.height);
    log("visible size w:%f,h:%f",m_visibleSize.width,m_visibleSize.height);
    log("visible origin w:%f,h:%f",m_visibleOrigin.x,m_visibleOrigin.y);
    
//    Application::getInstance()->getTargetPlatform();
//    CC_TARGET_PLATFORM
    
    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    GameUser::getInstance();
    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
//    auto scene = GameFightScene::scene();
//    auto scene = GameMapScene::scene();
//    auto scene = GameShopScene::scene();
//    auto scene = GameOverScene::scene(o_loss,NULL);
//    auto scene = GameHomeScene::scene();
    auto scene = GameCgShowScene::scene();
    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    _G_U->exitGame();
    umeng::MobClickCpp::applicationDidEnterBackground();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    _G_U->enterGame();
    umeng::MobClickCpp::applicationWillEnterForeground();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
