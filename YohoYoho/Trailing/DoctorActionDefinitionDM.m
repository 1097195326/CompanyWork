//
//  DoctorActionDefinitionDM.m
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-21.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "DoctorActionDefinitionDM.h"

@implementation DoctorActionDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"DoctorActionDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 用医生ID获取单条关卡定义数据
- (id) singleDoctorActionDefWithDoctorId:(int)doctorId {
    NSString *key = [NSString stringWithFormat:@"%i", doctorId];
    NSDictionary *singleDef = [self.data objectForKey:key];
    
    return singleDef;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}

@end
