//
//  DelegateLogic.h
//  YohoYoho
//
//  Created by  on 12-2-16.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
@class AppProfile;

@interface DelegateLogic : NSObject {
    int         gameMode_;              // 游戏模式
    int         patientCharacter_;      // 病人角色
    int         difficult_;             // 难度
    int         stage_;                 // 关卡
    AppProfile  *appProfile_;           // 游戏存档文件
}

@property (nonatomic, assign) int           gameMode;
@property (nonatomic, assign) int           patientCharacter;
@property (nonatomic, assign) int           difficult;
@property (nonatomic, assign) int           stage;
@property (nonatomic, retain) AppProfile    *appProfile;


// 跳转到标题场景
- (void) goToTitleScene;

// 跳转到故事场景
- (void) goToStoryScene;

// 跳转到选择模式场景
- (void) goToSelectModeScene;

// 跳转到病人模式选择人物场景
- (void) goToPatientModeSelectCharacterScene;

// 跳转到选择难度场景
- (void) goToSelectDifficultScene;

// 跳转到个人剧情场景
- (void) goToCharacterStoryScene;

// 跳转到地图场景
- (void) goToMapScene;

// 跳转到游戏场景
- (void) goToGameStageScene;

// 增加或减少金币数量
- (int) addCoins:(int)amount justSave:(BOOL)justSave;

// 设置BGM
- (void) updateBgm:(BOOL)bgm;

// 设置SE
- (void) updateSe:(BOOL)se;

// 增加或减少道具数量
- (void) addGoodsWithGoodsId:(int)goodsId
                      amount:(int)amount;

@end
