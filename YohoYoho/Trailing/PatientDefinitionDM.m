//
//  PatientDefinitionDM.m
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-19.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "PatientDefinitionDM.h"

@implementation PatientDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"PatientDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 用关卡ID获取单条关卡定义数据
- (id) singlePatientDefWithPatientId:(int)patientId {
    NSString *key = [NSString stringWithFormat:@"%i", patientId];
    NSDictionary *singleDef = [self.data objectForKey:key];
    
    return singleDef;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}

@end
