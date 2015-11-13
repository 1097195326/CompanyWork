//
//  StageDefinitionDM.h
//  YohoYoho
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface StageDefinitionDM : NSObject {
    NSDictionary    *data_;            // 数据
}

@property (nonatomic, retain) NSDictionary  *data;

// 用关卡ID获取单条关卡定义数据
- (id) singleStageDefWithStage:(int)stage;

// 用关卡ID获取医生ID
- (int) doctorIdWithStage:(int)stage;

// 用关卡ID和难度ID获取时间限制
- (int) timeLimitWithStage:(int)stage
                 difficult:(int)difficult;

// 获取金币奖励（条件：关卡ID、难度ID、下标）
- (int) coinRewardAmountWithStage:(int)stage
                        difficult:(int)difficult
                            index:(int)index;

@end
