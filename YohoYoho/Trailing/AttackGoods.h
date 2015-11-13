//
//  AttackGoods.h
//  YohoYoho
//
//  Created by  on 12-6-2.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface AttackGoods : CCSpriteBatchNode {
    NSDictionary        *singleGoodsDef_;               // 单个道具定义
//    CCSpriteBatchNode   *spriteBatchNode_;              // 动画图像
//    int                 currentActionId_;             // 病人当前的动作
}

@property (nonatomic, retain) NSDictionary          *singleGoodsDef;
//@property (nonatomic, retain) CCSpriteBatchNode     *spriteBatchNode;
//@property (nonatomic, assign) int                   currentActionId;


// 初始化方法
- (id) initWithGoodsId:(int)goodsId;

// 破碎
- (void) crash;

// 飞行后破碎
- (void) flyAndCrashWithPosition:(CGPoint)position
                           scale:(float)scale
                          target:(id)target
                        selector:(SEL)selecor;

// 跑步
//- (void) run;

// 急停
//- (void) brake;

// 检查是否为静止状态
//- (BOOL) isStay;

@end