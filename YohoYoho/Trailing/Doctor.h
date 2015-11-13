//
//  Doctor.h
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-21.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface Doctor : CCSprite {
    NSDictionary        *singleDoctorActionDef_;      // 单个医生的动作定义
    CCSpriteBatchNode   *doctorSpriteBatchNode_;      // 医生动画图像
    CGPoint             startPoint_;                  // 医生的开始坐标，距离屏幕较远的点
    CGPoint             endPoint_;                    // 医生的结束坐标，距离屏幕较近的点
    float               minScale_;                    // 医生的最小缩放：处于最远处
    float               maxScale_;                    // 医生的最大缩放：处于最近处
    BOOL                isMoving_;                    // 正在做动作
    BOOL                isMovingForJustTurnAround_;   // 正在做强制回头动作
}

@property (nonatomic, retain) NSDictionary          *singleDoctorActionDef;
@property (nonatomic, retain) CCSpriteBatchNode     *doctorSpriteBatchNode;
@property (nonatomic, assign) CGPoint               startPoint;
@property (nonatomic, assign) CGPoint               endPoint;
@property (nonatomic, assign) float                 minScale;
@property (nonatomic, assign) float                 maxScale;
@property (nonatomic, assign) BOOL                  isMoving;
@property (nonatomic, assign) BOOL                  isMovingForJustTurnAround;

// 初始化方法
- (id) initWithDoctorId:(int)doctorId;

// 设置医生的位置和缩放
- (void) setDoctorPositionWithDistance:(float)distance;

// 停止
- (void) stayWithMoving:(BOOL)moving;

// 行走
- (void) walkWithCallback:(id)object fast:(BOOL)fast;

// 假动作
- (void) feint;

// 回头
- (void) turnAroundWithCallback:(id)object;

// 被击中
- (void) damageWithCallback:(id)object
                vertigoTime:(int)vertigoTime;

// 停止，然后假动作
- (void) stayAndFeint;

// 停止，然后回头
- (void) stayAndTurnAroundWithCallback:(id)object;

// 立即回头
- (void) justTurnAroundWithCallback:(id)object;

// 立即停止
- (void) justStand;

@end
