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

class DefenseBuildingManager : public GameObject{
private:
    std::map<string,DefenseBuilding *> m_buildingData;
    std::vector<DefenseBuilding *> m_showBuildingData;
    
    std::map<int,std::string> m_hashHead;
    
public:
    DefenseBuilding *   getShowBuildingByIndex(int index);
    int     getShowBuildingNum();
    void    addShowBuilding(DefenseBuilding *);
    void    addBuildingJishudian();
    DefenseBuilding *   getBuildingByIndex(int index);
    int     getBuildingNum();
    void    setView();
    void    checkUnlock(Layer * layer);
    std::map<string,DefenseBuilding *> getBuildingData();
    std::vector<DefenseBuilding *>  getShowBuildingData();
public:
    DefenseBuildingManager();
    ~DefenseBuildingManager();
    static DefenseBuildingManager * getInstance();
    void    gameLoop(float data);
public:
    
};

#endif /* defined(__SwampAttack__DefenseBuildingManager__) */
