//
//  DoctorActionDefinitionDM.h
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-21.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DoctorActionDefinitionDM : NSObject {
    NSDictionary    *data_;            // 数据
}

@property (nonatomic, retain) NSDictionary  *data;

// 用关卡ID获取单条关卡定义数据
- (id) singleDoctorActionDefWithDoctorId:(int)doctorId;

@end
