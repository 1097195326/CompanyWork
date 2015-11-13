//
//  DoctorActionProbabilityDefinitionDM.h
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-23.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DoctorActionProbabilityDefinitionDM : NSObject {
    NSDictionary    *data_;            // 数据
}

@property (nonatomic, retain) NSDictionary  *data;

// 用医生ID和难度ID获取单条定义数据
- (id) singleDefWithDoctorId:(int)doctorId
                 difficultId:(int)difficultId;

@end
