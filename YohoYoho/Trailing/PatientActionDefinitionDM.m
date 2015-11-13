//
//  PatientActionDefinitionDM.m
//  YohoYoho
//
//  Created by  on 12-5-15.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "PatientActionDefinitionDM.h"

@implementation PatientActionDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"PatientActionDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 用病人ID获取单条病人动作定义数据
- (id) singlePatientActionDefWithPatientId:(int)patientId {
    NSString *key = [NSString stringWithFormat:@"%i", patientId];
    NSDictionary *singleDef = [self.data objectForKey:key];
    
    return singleDef;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}

@end