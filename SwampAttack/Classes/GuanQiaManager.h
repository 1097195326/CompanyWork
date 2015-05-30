//
//  GuanQiaManager.h
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#ifndef __SwampAttack__GuanQiaManager__
#define __SwampAttack__GuanQiaManager__

#include "GuanQiaModel.h"


class GuanQiaManager {
private:
    std::map<string,GuanqiaModel *> m_guanQiaData;
    std::map<int,std::string> m_hashHead;
    
    
public:
    GuanqiaModel *   getGuanqiaByIndex(int index);
    GuanqiaModel *   getGuanqiaById(string guanqiaId);
    int     getGuanqiaNum();
    
    
    void    setShopView(Sprite * shopScene);
    
public:
    static GuanQiaManager * getInstance();
    GuanQiaManager();
    ~GuanQiaManager();
};

#endif /* defined(__SwampAttack__GuanQiaManager__) */
