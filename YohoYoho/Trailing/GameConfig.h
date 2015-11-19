//
//  GameConfig.h
//  Trailing
//
//  Created by  on 12-2-13.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

//
// Supported Autorotations:
//		None,
//		UIViewController,
//		CCDirector
//
#define kGameAutorotationNone 0
#define kGameAutorotationCCDirector 1
#define kGameAutorotationUIViewController 2

//
// Define here the type of autorotation that you want for your game
//

// 3rd generation and newer devices: Rotate using UIViewController. Rotation should be supported on iPad apps.
// TIP:
// To improve the performance, you should set this value to "kGameAutorotationNone" or "kGameAutorotationCCDirector"
#if defined(__ARM_NEON__) || TARGET_IPHONE_SIMULATOR
#define GAME_AUTOROTATION kGameAutorotationUIViewController

// ARMv6 (1st and 2nd generation devices): Don't rotate. It is very expensive
#elif __arm__
#define GAME_AUTOROTATION kGameAutorotationNone


// Ignore this value on Mac
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#else
#error(unknown architecture)
#endif

#endif // __GAME_CONFIG_H



// ------------------------------- 常量 -------------------------------------
// 新浪微博
#define WEIBO_APP_KEY @"1156537733"
#define WEIBO_APP_SECRET @"d927b757b96b95fdf2b38cab64cc9467"

#define PROFILE_NAME @"profile.plist"													// 存档文件名称
#define GAME_MODE_PATIENT 1                                                             // 游戏模式：病人模式
#define GAME_MODE_DOCTOR 2                                                              // 游戏模式：医生模式
#define DIFFICULT_EASY 1                                                                // 游戏难度：病人模式简单难度
#define DIFFICULT_NORMAL 2                                                              // 游戏难度：病人模式普通难度
#define DIFFICULT_HARD 3                                                                // 游戏难度：病人模式困难难度

// 游戏场景
#define WALL_COUNT 7                                                                    // 游戏场景：墙壁个数
#define WALL_MOVE_POINT_X_PER_DISTANCE 1                                                // 游戏场景：每一点直线距离对应墙壁X坐标移动的距离
#define FLOOR_GOODS_ADD_PROBABILITY 5                                                   // 游戏场景：地面道具出现的概率
#define CEIL_GOODS_ADD_PROBABILITY 5                                                    // 游戏场景：天花板道具出现的概率
#define SIDE_LEFT 1                                                                     // 游戏场景：左侧
#define SIDE_RIGHT 2                                                                    // 游戏场景：右侧

// 游戏场景操作
#define CONTROL_SPEED_MIN 100                                                           // 游戏场景：加速减速时滑动的最小距离

// 游戏场景病人状态
#define PATIENT_STATUS_STAND 1                                                          // 游戏场景：病人站立状态
#define PATIENT_STATUS_WALK 2                                                           // 游戏场景：病人走状态
#define PATIENT_STATUS_RUN 3                                                            // 游戏场景：病人跑状态

// 游戏场景医生动作ID
#define DOCTOR_ACTION_ID_WALK 1                                                         // 医生动作ID：走
#define DOCTOR_ACTION_ID_STAY 2                                                         // 医生动作ID：停
#define DOCTOR_ACTION_ID_FEINT 3                                                        // 医生动作ID：假动作
#define DOCTOR_ACTION_ID_TURN_AROUND 4                                                  // 医生动作ID：回头
#define DOCTOR_ACTION_ID_DAMAGE 5                                                       // 医生动作ID：受伤，被击中

// 医生动画播放帧速
#define FRAMES_PER_SECOND 25                                                            // 每秒播放的帧数

// 医生跑动概率，在警戒距离内，医生出现跑步的概率（当判定为走路时，用跑步替代走路）
#define DOCTOR_RUN_PROBABILITY 2                                                        // 医生跑步概率，1/n

// 游戏场景病人和医生的距离
#define DISTANCE_INIT 750                                                               // 初始距离
#define DISTANCE_MAX_TO_GAME_OVER 900                                                   // 导致游戏结束的最大距离
#define DISTANCE_MAX 1750                                                               // 可显示的最大距离
#define DISTANCE_WARNING 300                                                            // 警戒距离

// 游戏场景距离条
#define PATIENT_ICON_X_MIN 30                                                           // 距离条上病人图标X坐标最小值
#define PATIENT_ICON_X_MAX 450                                                          // 距离条上病人图标X坐标最大值

// 关卡及角色
#define PATIENT_MAX 4                                                                   // 病人角色最大编号
#define STAGE_MAX 4                                                                     // 关卡最大编号


// 病人ID
enum E_PATIENT_ID{
    E_PATIENT_ID_GIRL = 1,
    E_PATIENT_ID_NOBLE = 2,
    E_PATIENT_ID_DEPRESSION = 3,
    E_PATIENT_ID_FAT = 4,
};