//
//  UserGuideManager.hpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/26.
//
//

#ifndef UserGuideManager_hpp
#define UserGuideManager_hpp

#include "GameObject.h"
#include "GuideBaseModel.hpp"


class UserGuideManager : public GameObject {
private:
    
public:
    static UserGuideManager * getInstance();
    
    UserGuideManager();
    ~UserGuideManager();
    
    void gameLoop(float dlay);
    
public:
    
};

#endif /* UserGuideManager_hpp */
