//
//  PropManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__PropManager__
#define __SwampAttack__PropManager__

#include "Prop.h"


class PropManager {
private:
    std::map<string,Prop *> m_propData;
    std::map<int,std::string> m_hashHead;
public:
    Prop *   getPropByIndex(int index);
    int     getPropNum();
public:
    static PropManager * getInstance();
    PropManager();
    ~PropManager();
};

#endif /* defined(__SwampAttack__PropManager__) */
