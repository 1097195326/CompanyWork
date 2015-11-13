//
//  SelectModeScene.h
//  YohoYoho
//
//  Created by  on 12-2-22.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"


// ----------------- 场景背景层 -------------------
@interface SelectModeBgLayer : CCLayer {
    CGMutablePathRef    pathForPatientMode_;        // 病人模式选区
}

@property (nonatomic, assign) CGMutablePathRef    pathForPatientMode;

@end


// ------------------- 场景 ---------------------
@interface SelectModeScene : CCScene {
    
}

+ (id) scene;

@end