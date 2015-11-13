//
//  StageDefinitionDM.m
//  YohoYoho
//
//  Created by  on 12-3-8.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "StageDefinitionDM.h"

@implementation StageDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"StageDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 用关卡ID获取单条关卡定义数据
- (id) singleStageDefWithStage:(int)stage {
    NSString *key = [NSString stringWithFormat:@"%i", stage];
    NSDictionary *singleStageDef = [self.data objectForKey:key];
    
    return singleStageDef;
}


// 用关卡ID获取医生ID
- (int) doctorIdWithStage:(int)stage {
    return [[[self singleStageDefWithStage:stage] objectForKey:@"doctorId"] intValue];
}


// 用关卡ID和难度ID获取时间限制
- (int) timeLimitWithStage:(int)stage
                 difficult:(int)difficult {
    NSDictionary *singleStageDef = [self singleStageDefWithStage:stage];
    int timeLimit = [[[singleStageDef objectForKey:@"timeLimit"] objectForKey:[NSString stringWithFormat:@"%i", difficult]] intValue];
    
    return timeLimit;
}


// 获取金币奖励（条件：关卡ID、难度ID、下标）
- (int) coinRewardAmountWithStage:(int)stage
                        difficult:(int)difficult
                            index:(int)index {
    NSDictionary *singleStageDef = [self singleStageDefWithStage:stage];
    int coinRewardAmount = [[[[singleStageDef objectForKey:@"coinRewardAmount"] objectForKey:[NSString stringWithFormat:@"%i", difficult]] objectAtIndex:index] intValue];
    
    return coinRewardAmount;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}


@end
