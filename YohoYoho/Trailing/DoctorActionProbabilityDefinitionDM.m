//
//  DoctorActionProbabilityDefinitionDM.m
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-23.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "DoctorActionProbabilityDefinitionDM.h"

@implementation DoctorActionProbabilityDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"DoctorActionProbabilityDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 用医生ID和难度ID获取单条定义数据
- (id) singleDefWithDoctorId:(int)doctorId
                 difficultId:(int)difficultId {
    NSString *key = [NSString stringWithFormat:@"%i_%i", doctorId, difficultId];
    NSDictionary *singleStageDef = [self.data objectForKey:key];
    
    return singleStageDef;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}

@end
