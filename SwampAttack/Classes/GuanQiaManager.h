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
    
    string  m_currentGuanqiaId;
    
public:
    GuanqiaModel *   getGuanqiaByIndex(int index);
    GuanqiaModel *   getGuanqiaById(string guanqiaId);
    int     getGuanqiaNum();
    
    
    void    setCurrentGuanqiaId(string guanqiaId);
    GuanqiaModel * getCurrentGuanqia();
public:
    static GuanQiaManager * getInstance();
    GuanQiaManager();
    ~GuanQiaManager();
};

#endif /* defined(__SwampAttack__GuanQiaManager__) */