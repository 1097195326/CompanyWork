//
//  PropManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "PropManager.h"
#include "ConfigManager.h"
#include "ShopPropIcon.h"
#include "DropPropSprite.h"

#include "GameUser.h"


PropManager::PropManager():
m_willTakeUpProp("")
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("daoju");
    m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    int index = 0;
    std::map<int,std::string>::iterator iter;
    for (iter = m_hashHead.begin(); iter != m_hashHead.end(); ++iter) {
        string propId = iter->second;
        Prop * prop = new Prop(data[propId]);
        m_propData[propId] = prop;
        if (prop->isTakeUp()) {
//            log("prop take up index :%d",prop->getTakeUpIndex());
            m_takeUpPropData[propId] = prop;
        }
        prop->setIndex(index);
        ++index;
    }
    
}
PropManager::~PropManager()
{
    
}
PropManager * PropManager::getInstance()
{
    static PropManager manager;
    return &manager;
}
void PropManager::gameLoop(float data)
{
    std::list<Prop *>::iterator iter;
    for (iter = m_usingPropDta.begin(); iter != m_usingPropDta.end();)
    {
        Prop * prop = *iter;
        if (prop->isCanDelete()) {
            delete prop;
            m_usingPropDta.erase(iter++);
        }else
        {
            iter++;
            prop->gameLoop(data);
        }
    }
}
Prop * PropManager::addUsingProp(string propId)
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("daoju");
    Json::Value data = propHelper->getJsonData();
    Prop * prop = new Prop(data[propId]);
    m_usingPropDta.push_back(prop);
    return prop;
}
Prop * PropManager::getPropByIndex(int index)
{
    string propId = m_hashHead[index];
    return m_propData[propId];
}
Prop * PropManager::getPropById(string id)
{
    return m_propData[id];
}
int PropManager::getPropNum()
{
    return (int)m_propData.size();
}

int PropManager::getTakeUpPropNum()
{
    return (int)m_takeUpPropData.size();
}
Prop * PropManager::getTakeUpPropByIndex(int index)
{
    Prop * prop = NULL;
//    int i = 0;
    std::map<string,Prop *>::iterator iter;
    for (iter = m_takeUpPropData.begin(); iter != m_takeUpPropData.end(); ++iter)
    {
        if (index == iter->second->getTakeUpIndex()) {
            prop = iter->second;
            break;
        }
//        ++i;
    }
    return prop;
}
int PropManager::getTakeUpPropIndexByName(string name)
{
    int index = 0;
    std::map<string,Prop *>::iterator iter;
    for (iter = m_takeUpPropData.begin(); iter != m_takeUpPropData.end(); ++iter)
    {
        ++index;
        if (iter->first == name) {
            break;
        }
    }
    return index;
}
std::map<string,Prop *> PropManager::getTakeUpProp()
{
    return m_takeUpPropData;
}
void PropManager::takeUpProp(string propId)
{
    int index = (int)m_takeUpPropData.size();
    Prop * prop = m_propData[propId];
    if (index >= 4)
    {
        Prop * lastProp = getTakeUpPropByIndex(4);
        takeDownProp(lastProp->getId());
        
        prop->takeUp(index);
        m_takeUpPropData[propId] = prop;
        m_propIcons[index -1]->reSetIcon(prop);
    }else
    {
        for (int i = 0; i < 4; ++i)
        {
            if (!m_propIcons[i]->isHaveProp())
            {
                prop->takeUp(i + 1);
                m_takeUpPropData[propId] = prop;
                m_propIcons[i]->reSetIcon(prop);
                break;
            }
        }
    }
    
}
void PropManager::takeDownProp(string propId)
{
    m_propData[propId]->takeDown();
    m_takeUpPropData.erase(propId);
}
void PropManager::setWillTakeUpProp(string propId)
{
    m_willTakeUpProp = propId;
}
string PropManager::getWillTakeUpProp()
{
    return m_willTakeUpProp;
}
void PropManager::takeUpWillProp()
{
    takeUpProp(m_willTakeUpProp);
    m_willTakeUpProp = "";
}
void PropManager::setFightView()
{
    std::map<string,Prop *>::iterator iter;
    for (iter = m_takeUpPropData.begin(); iter != m_takeUpPropData.end(); ++iter)
    {
        iter->second->setFightView();
    }
}
void PropManager::setShopView(Sprite * propItemSprite)
{
    m_propIcons.reserve(4);
    for (int i = 0; i < 4; i++)
    {
        Prop * prop = getTakeUpPropByIndex(i+1);
        ShopPropIcon * icon = new ShopPropIcon(i);
        icon->autorelease();
        icon->reSetIcon(prop);
        propItemSprite->addChild(icon);
        m_propIcons[i] = icon;
    }
}
void PropManager::checkUnlock(Layer * layer)
{
    std::map<string,Prop *>::iterator iter;
    for (iter = m_propData.begin(); iter != m_propData.end(); ++iter)
    {
        Prop * prop = iter->second;
        prop->checkUnlock(layer);
    }
}
bool PropManager::dropProp(string id,Vec2 point)
{
    log("drop prop");
    bool res = false;
    Prop * prop = m_propData[id];
    if (prop->isUnlock() || !_G_U->isHaveXinshouYindao())
    {
        if (!prop->isTakeUp())
        {
            prop->setTakeUpIndex((int)m_takeUpPropData.size() + 1);
            prop->setFightView();
            prop->loadResource();
        }
        DropPropSprite * spr = new DropPropSprite(prop,point);
        spr->autorelease();
        res = true;
//        spr->setPosition(point);
    }
    return res;
}