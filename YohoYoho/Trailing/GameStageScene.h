//
//  GameStageScene.h
//  YohoYoho
//
//  Created by  on 12-3-10.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "StageDefinitionDM.h"
#import "PatientDefinitionDM.h"
#import "GoodsDefinitionDM.h"
#import "Doctor.h"
#import "Patient.h"
#import "AttackGoods.h"


// ----------------- 场景背景层 -------------------
@interface GameStageBgLayer : CCLayerColor {
    Doctor          *doctor_;                       // 医生对象
    NSMutableArray  *leftWalls_;                    // 左侧墙壁数组
    NSMutableArray  *rightWalls_;                   // 右侧墙壁数组
    NSMutableArray  *leftFloorGoods_;               // 左侧地面道具数组
    NSMutableArray  *rightFloorGoods_;              // 右侧地面道具数组
    NSMutableArray  *middleCeilGoods_;              // 中间天花板道具数组
    NSMutableArray  *leftCeilGoods_;                // 左侧天花板道具数组
    NSMutableArray  *rightCeilGoods_;               // 右侧天花板道具数组
    CGPoint         goalPoint_;                     // 走廊尽头的点
    CGPoint         wallMovePointRatio_;            // 墙壁点移动量与缩放值的比值
    CGPoint         floorGoodsMovePointRatio_;      // 地面道具点移动量与缩放值的比值
    CGPoint         middleCeilGoodsMovePointRatio_; // 地面道具点移动量与缩放值的比值
    CGPoint         ceilGoodsMovePointRatio_;       // 天花板两侧道具点移动量与缩放值的比值
    float           movedDistance_;                 // 移动的距离，用于计算添加地面道具的时机
    float           totalMoveDistance_;             // 总移动距离，用于计算上下颠簸位置
}

@property (nonatomic, retain) Doctor          *doctor;
@property (nonatomic, retain) NSMutableArray  *leftWalls;
@property (nonatomic, retain) NSMutableArray  *rightWalls;
@property (nonatomic, retain) NSMutableArray  *leftFloorGoods;
@property (nonatomic, retain) NSMutableArray  *rightFloorGoods;
@property (nonatomic, retain) NSMutableArray  *middleCeilGoods;
@property (nonatomic, retain) NSMutableArray  *leftCeilGoods;
@property (nonatomic, retain) NSMutableArray  *rightCeilGoods;
@property (nonatomic, assign) CGPoint         goalPoint;
@property (nonatomic, assign) CGPoint         wallMovePointRatio;
@property (nonatomic, assign) CGPoint         floorGoodsMovePointRatio;
@property (nonatomic, assign) CGPoint         middleCeilGoodsMovePointRatio;
@property (nonatomic, assign) CGPoint         ceilGoodsMovePointRatio;
@property (nonatomic, assign) float           movedDistance;
@property (nonatomic, assign) float           totalMoveDistance;


// 加载层内容，初始化变量
- (void) loadContentsOfLayer;

@end


// ----------------- 操作层 -------------------
@interface GameStagePlayLayer : CCLayer {
    CGPoint             startPoint_;                // 点击滑动的开始点
    CGPoint             prePoint_;                  // 点击滑动时的前一个点
    NSTimeInterval      moveStartTime_;             // 开始滑动的时间戳
}

@property (nonatomic, assign) CGPoint           startPoint;
@property (nonatomic, assign) CGPoint           prePoint;
@property (nonatomic, assign) NSTimeInterval    moveStartTime;

@end


// ----------------- 菜单层 -------------------
@interface GameStageMenuLayer : CCLayer {
    CCSprite            *pointer_;                   // 钟表指针
    CCSprite            *patientIcon_;               // 距离条上的病人图标
    Patient             *patient_;                   // 吊瓶内的病人
}

@property (nonatomic, retain) CCSprite            *pointer;
@property (nonatomic, retain) CCSprite            *patientIcon;
@property (nonatomic, retain) Patient             *patient;

// 更新钟表指针角度
- (void) updatePointerRotationWithTimeRatio:(float)timeRatio;

// 更新距离条中病人图标位置
- (void) updatePatientIconPositionWithDistanceRatio:(float)distanceRatio;

@end


// --------------------- 游戏场景打击层 ------------------------
@interface GameStageAttackLayer : CCLayer {
    CCSprite                *cursor_;                       // 打击光标
}

@property (nonatomic, retain) CCSprite      *cursor;

@end


// --------------------- 游戏场景暂停层 ------------------------
@interface GameStagePauseLayer : CCLayerColor

@end


// --------------------- 游戏场景设置层 ------------------------
@interface GameStageConfigLayer : CCLayerColor

@end


// --------------------- 游戏场景结果层（胜利或失败） ------------------------
@interface GameStageResultLayer : CCLayer {
    CCSprite        *winBg2_;           // 胜利背景2
}

@property (nonatomic, retain) CCSprite        *winBg2;

@end


// ------------------- 场景 ---------------------
@interface GameStageScene : CCScene {
    GameStageBgLayer        *bgLayer_;                      // 背景层
    GameStageMenuLayer      *menuLayer_;                    // 菜单层
    
    StageDefinitionDM       *stageDefinitionDM_;            // 关卡定义数据模型
    PatientDefinitionDM     *patientDefinitionDM_;          // 病人定义数据模型
    GoodsDefinitionDM       *goodsDefinitionDM_;            // 道具定义
    NSArray                 *doctorActionProbabilityDef_;   // 医生动作概率定义
    int                     time_;                          // 游戏时间
    int                     timeLimit_;                     // 时间限制
//    int                     speedUpToWalk_;                 // 站到走需要滑动的次数
//    int                     speedUpToRun_;                  // 走到跑需要滑动的次数
//    int                     speedDownToWalk_;               // 跑到走需要滑动的次数
//    int                     speedDownToStand_;              // 走到停需要滑动的次数
//    int                     stepLength_;                    // 步长
//    float                   walkTimePerStep_;               // 每走一步花费的时间
//    float                   runTimePerStep_;                // 每跑一步花费的时间
    float                   swipeDistancePerMoveDistance_;  // 每移动一个距离需要滑动屏幕的距离
    int                     patientStatus_;                 // 病人状态：站、走、跑
    int                     swipeValue_;                    // 滑动值，用于计算状态，向上滑动则加，向下滑动则减
    BOOL                    isMoving_;                      // 正在移动
    float                   distance_;                      // 医生与病人的距离
    BOOL                    attackMode_;                    // 打击模式（接近医生时进入打击模式）
    BOOL                    isGameOver_;                    // 游戏已结束
}

@property (nonatomic, retain) GameStageBgLayer      *bgLayer;
@property (nonatomic, retain) GameStageMenuLayer    *menuLayer;
@property (nonatomic, retain) StageDefinitionDM     *stageDefinitionDM;
@property (nonatomic, retain) PatientDefinitionDM   *patientDefinitionDM;
@property (nonatomic, retain) GoodsDefinitionDM     *goodsDefinitionDM;
@property (nonatomic, retain) NSArray               *doctorActionProbabilityDef;
@property (nonatomic, assign) int                   time;
@property (nonatomic, assign) int                   timeLimit;
//@property (nonatomic, assign) int                   speedUpToWalk;
//@property (nonatomic, assign) int                   speedUpToRun;
//@property (nonatomic, assign) int                   speedDownToWalk;
//@property (nonatomic, assign) int                   speedDownToStand;
//@property (nonatomic, assign) int                   stepLength;
//@property (nonatomic, assign) float                 walkTimePerStep;
//@property (nonatomic, assign) float                 runTimePerStep;
@property (nonatomic, assign) float                 swipeDistancePerMoveDistance;
@property (nonatomic, assign) int                   patientStatus;
@property (nonatomic, assign) int                   swipeValue;
@property (nonatomic, assign) BOOL                  isMoving;
@property (nonatomic, assign) float                 distance;
@property (nonatomic, assign) BOOL                  attackMode;
@property (nonatomic, assign) BOOL                  isGameOver;


+ (id) scene;

// 开始游戏（启动计划任务，设置界面点击等）
- (void) startGame;

// 检查时候被发现，用于医生回头的回调函数
- (void) checkFound;

// 检查高速移动（快速滑动），引起医生立即回头
- (void) checkDoctorMoveWithSwipeSpeed:(double)speed;

// 增加距离
- (void) addDistanceOfPatientAndDoctor:(float)distance;

// 病人移动
- (void) moveWithDistance:(int)distance;

/*
// 加速
- (void) speedUp;

// 减速
- (void) speedDown;
*/

// 暂停
- (void) pause;

// 取消暂停
- (void) resume;

// 显示配置
- (void) showConfig;

// 关闭配置
- (void) closeConfig;

// 显示帮助
- (void) showHelp;

// 打击失败
- (void) attackMiss;

// 病人开始移动（移动病人，开始滑动屏幕时）
- (void) patientMoveBegan;

// 病人停止（吊瓶内的动画）
- (void) patientStay;

// 病人急停（吊瓶内的动画）
- (void) patientBrake;

// 游戏结束
- (void) gameOverWithGameOverId:(int)gameOverId;

// 胜利
- (void) win;

// 使用道具
- (void) useGoodsWithGoodsId:(int)goodsId;

@end
