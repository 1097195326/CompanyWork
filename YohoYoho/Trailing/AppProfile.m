//
//  AppProfile.m
//  YohoYoho
//
//  Created by  on 12-3-7.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "AppProfile.h"


@implementation AppProfile

#define PROFILE_KEY_SETTING @"setting"                              // 设置
#define PROFILE_KEY_SETTING_BGM @"bgm"                                  // bgm音量
#define PROFILE_KEY_SETTING_SE @"se"                                    // se音量
#define PROFILE_KEY_STAGE_LOCK @"stageLock"                         // 关卡锁定
#define PROFILE_KEY_PATIENT_LOCK @"patientLock"                     // 角色锁定
#define PROFILE_KEY_GOODS @"goods"                                  // 所持道具
#define PROFILE_KEY_COINS @"coins"                                  // 金币数量

// 构造方法
- (id) initWithFileName:(NSString *)fileName {
	if ((self = [super initWithFileName:fileName])) {
		
		// 初始化设置
		if ([self.profile objectForKey:PROFILE_KEY_SETTING] == nil) {
			[self.profile setObject:[NSMutableDictionary dictionary] forKey:PROFILE_KEY_SETTING];
		}
		
        // 初始化关卡锁定
		if ([self.profile objectForKey:PROFILE_KEY_STAGE_LOCK] == nil) {
			[self.profile setObject:[NSMutableDictionary dictionary] forKey:PROFILE_KEY_STAGE_LOCK];
		}
        
        // 初始化角色锁定
		if ([self.profile objectForKey:PROFILE_KEY_PATIENT_LOCK] == nil) {
			[self.profile setObject:[NSMutableDictionary dictionary] forKey:PROFILE_KEY_PATIENT_LOCK];
		}
        
        // 初始化所持道具
		if ([self.profile objectForKey:PROFILE_KEY_GOODS] == nil) {
			[self.profile setObject:[NSMutableDictionary dictionary] forKey:PROFILE_KEY_GOODS];
		}
        
        // 初始化金币数量
		if ([self.profile objectForKey:PROFILE_KEY_COINS] == nil) {
			[self.profile setObject:[NSNumber numberWithInt:0] forKey:PROFILE_KEY_COINS];
		}
	}
	
	return self;
}


// 更新BGM音量
- (void) updateBgm:(BOOL)bgm {
    NSMutableDictionary *setting = [self.profile objectForKey: PROFILE_KEY_SETTING];
	[setting setObject:[NSNumber numberWithBool:bgm] forKey: PROFILE_KEY_SETTING_BGM];
}


// 获取BGM音量
- (BOOL) bgm {
    NSMutableDictionary *setting = [self.profile objectForKey: PROFILE_KEY_SETTING];
    if ([setting objectForKey:PROFILE_KEY_SETTING_BGM] == nil) {
        [setting setObject:[NSNumber numberWithBool: YES] forKey:PROFILE_KEY_SETTING_BGM];
    }
	return [[setting objectForKey:PROFILE_KEY_SETTING_BGM] boolValue];
}


// 更新SE音量
- (void) updateSe:(BOOL)se {
    NSMutableDictionary *setting = [self.profile objectForKey: PROFILE_KEY_SETTING];
	[setting setObject:[NSNumber numberWithBool:se] forKey: PROFILE_KEY_SETTING_SE];
}


// 获取SE音量
- (BOOL) se {
    NSMutableDictionary *setting = [self.profile objectForKey: PROFILE_KEY_SETTING];
    if ([setting objectForKey:PROFILE_KEY_SETTING_SE] == nil) {
        [setting setObject:[NSNumber numberWithBool: YES] forKey:PROFILE_KEY_SETTING_SE];
    }
	return [[setting objectForKey:PROFILE_KEY_SETTING_SE] boolValue];
}


// 更新关卡锁定
- (void) updateStageLock:(BOOL)lock
               difficult:(int)difficult
                   stage:(int)stage {
    NSString *key = [NSString stringWithFormat:@"%i_%i", difficult, stage];
    NSMutableDictionary *stageLock = [self.profile objectForKey: PROFILE_KEY_STAGE_LOCK];
    [stageLock setObject:[NSNumber numberWithBool:lock] forKey:key];
}


// 获取关卡锁定
- (BOOL) stageLockWithDifficult:(int)difficult
                          stage:(int)stage {
    NSString *key = [NSString stringWithFormat:@"%i_%i", difficult, stage];
    NSMutableDictionary *stageLock = [self.profile objectForKey: PROFILE_KEY_STAGE_LOCK];
    if ([stageLock objectForKey:key] == nil) {
        
        // 第一关默认值为不锁定，其余为锁定
        BOOL locked = YES;
        if (stage == 1) {
            locked = NO;
        }
        
        [stageLock setObject:[NSNumber numberWithBool:locked] forKey:key];
    }
    
    return [[stageLock objectForKey:key] boolValue];
}


// 更新角色锁定
- (void) updatePatientLock:(BOOL)lock
                   patientId:(int)patientId {
    NSString *key = [NSString stringWithFormat:@"%i", patientId];
    NSMutableDictionary *patientLock = [self.profile objectForKey: PROFILE_KEY_PATIENT_LOCK];
    [patientLock setObject:[NSNumber numberWithBool:lock] forKey:key];
}


// 获取角色锁定
- (BOOL) patientLockWithPatientId:(int)patientId {
    NSString *key = [NSString stringWithFormat:@"%i", patientId];
    NSMutableDictionary *patientLock = [self.profile objectForKey: PROFILE_KEY_PATIENT_LOCK];
    if ([patientLock objectForKey:key] == nil) {
        
        // 第一个角色默认值为不锁定，其余为锁定
        BOOL locked = YES;
        if (patientId == 1) {
            locked = NO;
        }
        
        [patientLock setObject:[NSNumber numberWithBool:locked] forKey:key];
    }
    
    return [[patientLock objectForKey:key] boolValue];
}


// 更新金币数量
- (void) updateCoins:(int)coins {
    [self.profile setObject:[NSNumber numberWithInt:coins] forKey:PROFILE_KEY_COINS];
}


// 获取金币数量
- (int) coins {
	return [[self.profile objectForKey:PROFILE_KEY_COINS] intValue];
}


// 道具 ----------------------------------------------------------------------------------
// 更新单个道具数量
- (void) updateGoodsWithAmount:(int)amount
                       goodsId:(int)goodsId {
    NSString *key = [NSString stringWithFormat:@"%i", goodsId];
    NSMutableDictionary *goods = [self.profile objectForKey: PROFILE_KEY_GOODS];
    [goods setObject:[NSNumber numberWithInt:amount] forKey:key];
}


// 删除单个道具
- (void) deleteGoodsWithGoodsId:(int)goodsId {
    NSString *key = [NSString stringWithFormat:@"%i", goodsId];
    NSMutableDictionary *goods = [self.profile objectForKey: PROFILE_KEY_GOODS];
    [goods removeObjectForKey:key];
}


// 获取单个道具数量
- (int) goodsAmountWithGoodsId:(int)goodsId {
    NSString *key = [NSString stringWithFormat:@"%i", goodsId];
    NSMutableDictionary *goods = [self.profile objectForKey: PROFILE_KEY_GOODS];
    int goodsAmount = 0;
    NSNumber *singleGoods = [goods objectForKey:key];
    if (singleGoods != nil) {
        goodsAmount = [singleGoods intValue];
    }
    
    return goodsAmount;
}


// 获取所有道具信息
- (NSDictionary *) goods {
    return [self.profile objectForKey: PROFILE_KEY_GOODS];
}


@end
