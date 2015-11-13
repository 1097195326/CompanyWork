//
//  PatientActionDefinitionDM.h
//  YohoYoho
//
//  Created by  on 12-5-15.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

@interface PatientActionDefinitionDM : NSObject {
    NSDictionary    *data_;            // 数据
}

@property (nonatomic, retain) NSDictionary  *data;

// 用病人ID获取单条病人动作定义数据
- (id) singlePatientActionDefWithPatientId:(int)patientId;

@end