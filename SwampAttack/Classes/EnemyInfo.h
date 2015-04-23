//
//  EnemyInfo.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#ifndef __SwampAttack__EnemyInfo__
#define __SwampAttack__EnemyInfo__


using namespace std;

struct EnemyInfoData {
    int     attackFrame;
    int     attackFrames;
    int     waitFrames;
    int     walkFrames;
    int     downFrames;
    int     width;
    int     height;
    int     widthOffSet;
    
};
class EnemyInfo {
private:
    map<string,EnemyInfoData> m_data;
    EnemyInfo();
public:
    static EnemyInfo * getInstance();
    EnemyInfoData getInfoByName(string name);
};

#endif /* defined(__SwampAttack__EnemyInfo__) */
