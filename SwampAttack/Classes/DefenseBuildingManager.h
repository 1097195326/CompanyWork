//
//  DefenseBuildingManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#ifndef __SwampAttack__DefenseBuildingManager__
#define __SwampAttack__DefenseBuildingManager__

#include "DefenseBuilding.h"

using namespace std;

class DefenseBuildingManager {
private:
    std::map<string,DefenseBuilding *> m_buildingData;
    std::map<int,std::string> m_hashHead;
    
public:
    DefenseBuilding *   getBuildingByIndex(int index);
    int     getBuildingNum();
    
public:
    DefenseBuildingManager();
    ~DefenseBuildingManager();
    static DefenseBuildingManager * getInstance();

public:
    
};

#endif /* defined(__SwampAttack__DefenseBuildingManager__) */
