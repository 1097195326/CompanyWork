//
//  AppProfile.h
//  YohoYoho
//
//  Created by  on 12-3-7.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LYProfile.h"


@interface AppProfile : LYProfile {
    
}

// 更新BGM音量
- (void) updateBgm:(BOOL)bgm;

// 获取BGM音量
- (BOOL) bgm;

// 更新SE音量
- (void) updateSe:(BOOL)se;

// 获取SE音量
- (BOOL) se;

// 更新关卡锁定
- (void) updateStageLock:(BOOL)lock
               difficult:(int)difficult
                   stage:(int)stage;

// 获取关卡锁定
- (BOOL) stageLockWithDifficult:(int)difficult
                          stage:(int)stage;

// 更新角色锁定
- (void) updatePatientLock:(BOOL)lock
                 patientId:(int)patientId;

// 获取角色锁定
- (BOOL) patientLockWithPatientId:(int)patientId;

// 更新金币数量
- (void) updateCoins:(int)coins;

// 获取金币数量
- (int) coins;


// 道具 ----------------------------------------------------------------------------------
// 更新单个道具数量
- (void) updateGoodsWithAmount:(int)amount
                       goodsId:(int)goodsId;

// 删除单个道具
- (void) deleteGoodsWithGoodsId:(int)goodsId;

// 获取单个道具数量
- (int) goodsAmountWithGoodsId:(int)goodsId;

// 获取所有道具信息
- (NSDictionary *) goods;

@end
