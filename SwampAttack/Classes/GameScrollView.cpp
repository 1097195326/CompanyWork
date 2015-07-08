//
//  GameScrollView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/6.
//
//

#include "GameScrollView.h"


GameScrollView::GameScrollView(float width, float height):
m_viewWidth(width),
m_viewHeight(height),
m_moveV(Vec2(0, 0)),
m_isMove(false)
{
    init();
    
    DrawNode * drawRect = DrawNode::create();
    Vec2 pos[4] = {Vec2(0, 0),Vec2(m_viewWidth, 0),Vec2(m_viewWidth, m_viewHeight),Vec2(0, m_viewHeight)};
    drawRect->drawPolygon(pos, 4, Color4F(0, 0, 0, 0), 0, Color4F(0, 0, 0, 0));
    
    setStencil(drawRect);
    setInverted(false);
    
    m_scrollController = new ScrollController();
    m_scrollController->setViewWidth(m_viewWidth);
    m_scrollController->setViewHeight(m_viewHeight);
    
    m_layer = Layer::create();
//    m_layer = Sprite::create();
    addChild(m_layer,3);
    
    //------ listener --------
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameScrollView::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameScrollView::touchMoved,this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameScrollView::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    schedule(CC_SCHEDULE_SELECTOR(GameScrollView::update), 1/60);
//    scheduleUpdate();
}
GameScrollView::~GameScrollView()
{
    delete m_scrollController;
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}
void GameScrollView::update(float data)
{
    m_scrollController->update(data);
    M_Vec2f vec = m_scrollController->getOffSet();
    m_layer->setPosition( vec.x, vec.y);
}
bool GameScrollView::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_viewWidth, m_viewHeight);
    if (r.containsPoint(p)) {
        return true;
    }
    return false;
}
void GameScrollView::touchMoved(Touch *touch, Event *event)
{
    Vec2 perPoint = touch->getPreviousLocation();
    Vec2 currPoint = touch->getLocation();
    Vec2 c = currPoint - perPoint;
//    m_moveV += c;
//    log("scroll move :%f",m_moveV.length());
//    if (m_moveV.length() < 5)
//    {
//        return;
//    }
    m_scrollController->updateOffSet(c.x, c.y);
    
    m_isMove = true;
}
void GameScrollView::touchEnd(Touch *touch, Event *event)
{
//    m_moveV = Vec2::ZERO;
    if (m_isMove)
    {
        Vec2 perPoint = touch->getPreviousLocation();
        Vec2 currPoint = touch->getLocation();
        Vec2 c = currPoint - perPoint;
        m_scrollController->updateVelocity(c.x, c.y);
        m_isMove = false;
    }
}
void GameScrollView::addChildToScrollView(cocos2d::Node *node,int zOrder)
{
    m_layer->addChild(node,zOrder);
}
void GameScrollView::removeAllChildFromScrollView()
{
    m_layer->removeAllChildrenWithCleanup(true);
}
void GameScrollView::setScrollControllerContentWidth(float width)
{
    m_scrollContentWidth = width;
    m_scrollController->setContentWidth(width);
}
void GameScrollView::setScrollControllerContentHeight(float height)
{
    m_scrollContentHeight = height;
    m_scrollController->setContentHeight(height);
}
void GameScrollView::setScrollHorizontal(bool canH)
{
    m_scrollController->setHorizontal(canH);
}
void GameScrollView::setScrollVertical(bool canV)
{
    m_scrollController->setVertical(canV);
}
void GameScrollView::setScrollUndulate(bool undulate)
{
    m_scrollController->setUndulate(undulate);
}