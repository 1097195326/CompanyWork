//
//  PatientModeSelectCharacterScene.h
//  YohoYoho
//
//  Created by  on 12-2-27.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"


// ----------------- 场景背景层 -------------------
@interface PatientModeSelectCharacterBgLayer : CCLayer {
    CGMutablePathRef    pathForPatient1_;        // 病人1选区
    CGMutablePathRef    pathForPatient2_;        // 病人2选区
    CGMutablePathRef    pathForPatient3_;        // 病人3选区
    CGMutablePathRef    pathForPatient4_;        // 病人4选区
}

@property (nonatomic, assign) CGMutablePathRef    pathForPatient1;
@property (nonatomic, assign) CGMutablePathRef    pathForPatient2;
@property (nonatomic, assign) CGMutablePathRef    pathForPatient3;
@property (nonatomic, assign) CGMutablePathRef    pathForPatient4;

@end


// --------------------- 人物描述层 ------------------------
@interface PatientModeSelectCharacterDescriptionLayer : CCLayerColor

// 初始化方法
- (id) initWithPatientId:(int)patientId;

@end


// ------------------- 场景 ---------------------
@interface PatientModeSelectCharacterScene : CCScene {
    
}

+ (id) scene;


// 显示人物描述层
- (void) showDescriptionLayerWithPatientId:(int)patientId;

// 选择人物
- (void) selectPatientWithPatientId:(int)patientId;

@end
