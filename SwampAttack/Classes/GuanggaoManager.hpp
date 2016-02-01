//
//  GuanggaoManager.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#ifndef GuanggaoManager_hpp
#define GuanggaoManager_hpp

#include "GuanggaoModel.hpp"

#define _Gg_M_ GuanggaoManager::getIntantse()

class GuanggaoManager
{
private:
    std::map<std::string,GuanggaoModel *> m_guanggaoData;
    std::map<int,std::string> m_hashHead;
    
    
    GuanggaoManager();
    
public:
    static GuanggaoManager * getIntantse();
    
    GuanggaoModel * getGuangggaoModelByIndex(int index);
    ~GuanggaoManager();
};

#endif /* GuanggaoManager_hpp */
