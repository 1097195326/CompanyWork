//
//  Patient.m
//  YohoYoho
//
//  Created by  on 12-5-15.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "Patient.h"
#import "AppDelegate.h"
#import "PatientActionDefinitionDM.h"


// 动作ID
enum E_ACTION_ID{
    E_ACTION_ID_STAY,
    E_ACTION_ID_RUN,
    E_ACTION_ID_BRAKE,
};


@implementation Patient

@synthesize singlePatientActionDef = singlePatientActionDef_;
@synthesize patientSpriteBatchNode = patientSpriteBatchNode_;
@synthesize currentActionId = currentActionId_;


// 初始化方法
- (id) init {
    if (self = [super init]) {
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        int patientId = delegate.delegateLogic.patientCharacter;
        
        // 创建病人动作定义数据模型对象
        PatientActionDefinitionDM *patientActionDefinitionDM = [[[PatientActionDefinitionDM alloc] init] autorelease];
        
        // 获取单个病人动作定义
        self.singlePatientActionDef = [patientActionDefinitionDM singlePatientActionDefWithPatientId:patientId];
        
        // 初始化医生图像为停止
        self.currentActionId = E_ACTION_ID_STAY;
        NSString *fileName = [NSString stringWithFormat:@"patient_%i_stay.png", patientId];
        self.patientSpriteBatchNode = [CCSpriteBatchNode batchNodeWithFile:fileName];
        
        // 设置医生位置
        CCSprite *spriteForPatient = [CCSprite spriteWithFile:fileName];
        [self.patientSpriteBatchNode addChild:spriteForPatient];
    }
    
    return self;
}


// 停止
- (void) stay {
    
    // 如果当前正在做此动作，退出
    if (self.currentActionId == E_ACTION_ID_STAY) {
        return;
    }
    self.currentActionId = E_ACTION_ID_STAY;
    
    
    // 清除所有帧
    [self.patientSpriteBatchNode removeAllChildrenWithCleanup:YES];
    
    // 设置Texture
    NSString *fileName = [self.singlePatientActionDef objectForKey:@"stay"];
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
    [self.patientSpriteBatchNode setTexture:texture];
    
    CCSprite *spriteForPatient = [CCSprite spriteWithFile:fileName];
    [self.patientSpriteBatchNode addChild:spriteForPatient];
}


// 跑步
- (void) run {
    
    // 如果当前正在做此动作，退出
    if (self.currentActionId == E_ACTION_ID_RUN) {
        return;
    }
    self.currentActionId = E_ACTION_ID_RUN;
    
    
    // 清除所有帧
    [self.patientSpriteBatchNode removeAllChildrenWithCleanup:YES];
    /*
     // 释放内存
     [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
     [[CCTextureCache sharedTextureCache] removeUnusedTextures];
     */

    // 设置Texture
    NSDictionary *animationInfo = [self.singlePatientActionDef objectForKey:@"run"];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.patientSpriteBatchNode setTexture:texture];
    
    
    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
    for(int i = 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 创建动画对象
    float walkTime = [[animationInfo objectForKey:@"time"] floatValue];
    float delayTime = walkTime / frameCount;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *patientSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    [self.patientSpriteBatchNode addChild:patientSprite];
    
    // 动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    id actRepeatForever = [CCRepeatForever actionWithAction:actAnimate];
    [patientSprite runAction:actRepeatForever];
}


// 急停
- (void) brake {
    
    // 如果当前正在做此动作，退出
    if (self.currentActionId == E_ACTION_ID_BRAKE) {
        return;
    }
    self.currentActionId = E_ACTION_ID_BRAKE;
    
    
    // 清除所有帧
    [self.patientSpriteBatchNode removeAllChildrenWithCleanup:YES];
    /*
     // 释放内存
     [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
     [[CCTextureCache sharedTextureCache] removeUnusedTextures];
     */
    
    // 设置Texture
    NSDictionary *animationInfo = [self.singlePatientActionDef objectForKey:@"brake"];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.patientSpriteBatchNode setTexture:texture];
    
    
    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
    for(int i = 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 创建动画对象
    float time = [[animationInfo objectForKey:@"time"] floatValue];
    float delayTime = time / frameCount;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *patientSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    [self.patientSpriteBatchNode addChild:patientSprite];
    
    // 动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        self.currentActionId = E_ACTION_ID_STAY;
    }];
    id actSeq = [CCSequence actions:actAnimate, actCallBlock, nil];
    [patientSprite runAction:actSeq];
}


// 检查是否为静止状态
- (BOOL) isSafe {
    return self.currentActionId != E_ACTION_ID_RUN;
}


- (void) dealloc {
    self.singlePatientActionDef = nil;
    self.patientSpriteBatchNode = nil;
    [super dealloc];
}


@end
