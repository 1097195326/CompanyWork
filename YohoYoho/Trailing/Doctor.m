//
//  Doctor.m
//  YohoYoho
//
//  Created by 杨 帆 on 12-3-21.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "Doctor.h"
#import "GameConfig.h"
#import "DoctorActionDefinitionDM.h"
#import "GameStageScene.h"


@implementation Doctor

@synthesize singleDoctorActionDef = singleDoctorActionDef_;
@synthesize doctorSpriteBatchNode = doctorSpriteBatchNode_;
@synthesize startPoint = startPoint_;
@synthesize endPoint = endPoint_;
@synthesize minScale = minScale_;
@synthesize maxScale = maxScale_;
@synthesize isMoving = isMoving_;
@synthesize isMovingForJustTurnAround = isMovingForJustTurnAround_;

int preIndexForFeint = 0;
int preIndexForTurnAround = 0;

// 初始化方法
- (id) initWithDoctorId:(int)doctorId {
    if (self = [super init]) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 初始化变量
        self.startPoint = ccp(winSize.width / 2, winSize.height / 2 + 50);
        self.endPoint = ccp(winSize.width / 2, winSize.height / 2 - 400);
        self.minScale = 0.25f;
        self.maxScale = 1.25f;
        self.isMoving = NO;
        
        // 创建医生动作定义数据模型对象
        DoctorActionDefinitionDM *doctorActionDefinitionDM = [[[DoctorActionDefinitionDM alloc] init] autorelease];
        
        // 获取单个医生定义
        self.singleDoctorActionDef = [doctorActionDefinitionDM singleDoctorActionDefWithDoctorId:doctorId];
        
        // 加载动画数据 - 走
//        NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_WALK]];
//        for (NSDictionary *animationInfo in animationInfos) {
//            NSString *fileName = [animationInfo objectForKey:@"fileName"];
//            NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
//            NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
//            
//            // 添加帧缓冲
//            [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
//        }
        
        // 加载动画数据 - 假动作
//        animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_FEINT]];
//        for (NSDictionary *animationInfo in animationInfos) {
//            NSString *fileName = [animationInfo objectForKey:@"fileName"];
//            NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
//            NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
//            
//            // 添加帧缓冲
//            [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
//        }
        
        // 初始化医生图像为停止
        NSString *fileName = [NSString stringWithFormat:@"doctor_%i_stay_1.png", doctorId];
        self.doctorSpriteBatchNode = [CCSpriteBatchNode batchNodeWithFile:fileName];
//        self.doctorSpriteBatchNode.position = self.startPoint;
//        self.doctorSpriteBatchNode.scale = self.minScale;

        // 设置医生位置
//        [self setDoctorPositionWithDistance:DISTANCE_INIT];
        
        CCSprite *spriteForDoctor = [CCSprite spriteWithFile:fileName];
        spriteForDoctor.anchorPoint = ccp(0.5f, 0.0f);
        [self.doctorSpriteBatchNode addChild:spriteForDoctor];
    }
    
    return self;
}


// 设置医生的位置和缩放
- (void) setDoctorPositionWithDistance:(float)distance {
//    float percent = distance / DISTANCE_MAX;
//    
//    float newPositionY = self.endPoint.y + (self.startPoint.y - self.endPoint.y) * percent;
//    self.doctorSpriteBatchNode.position = ccp(self.startPoint.x, newPositionY);
//    
//    float newScale = self.minScale + (self.maxScale - self.minScale) * (1 - percent);
//    self.doctorSpriteBatchNode.scale = newScale;
    
    self.doctorSpriteBatchNode.position = [self doctorPositionWithDistance:distance];
    self.doctorSpriteBatchNode.scale = [self doctorScaleWithDistance:distance];
}


// 医生位置（根据距离计算）
- (CGPoint) doctorPositionWithDistance:(float)distance {
    float percent = distance / DISTANCE_MAX;
    
    float newPositionY = self.endPoint.y + (self.startPoint.y - self.endPoint.y) * percent;
    return ccp(self.startPoint.x, newPositionY);
}


// 医生缩放（根据距离计算）
- (float) doctorScaleWithDistance:(float)distance {
    float percent = distance / DISTANCE_MAX;
    
    float newScale = self.minScale + (self.maxScale - self.minScale) * (1 - percent);
    return newScale;
}


// 停止
- (void) stayWithMoving:(BOOL)moving {

    // 清除所有帧
    [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
    
    // 设置Texture
    NSString *fileName = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_STAY]];
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:fileName];
    [self.doctorSpriteBatchNode setTexture:texture];

    CCSprite *spriteForDoctor = [CCSprite spriteWithFile:fileName];
    spriteForDoctor.anchorPoint = ccp(0.5f, 0.0f);
    [self.doctorSpriteBatchNode addChild:spriteForDoctor];
    
    // 动作
    id actDelay = [CCDelayTime actionWithDuration:2.0f];
    id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        self.isMoving = moving;
    }];
    id actSeq = [CCSequence actions:actDelay, actCallBlockN, nil];
    [spriteForDoctor runAction:actSeq];
}


// 行走
- (void) walkWithCallback:(id)object
                     fast:(BOOL)fast {

    // 清除所有帧
    [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
    /*
    // 释放内存
    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
    [[CCTextureCache sharedTextureCache] removeUnusedTextures];
    */
    // 设置Texture
    NSDictionary *animationInfo = [[self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_WALK]] objectAtIndex:0];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.doctorSpriteBatchNode setTexture:texture];
    

    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
    for(int i = 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 创建动画对象
    float walkTime = [[animationInfo objectForKey:@"time"] floatValue];
    if (fast == YES) {
        walkTime = walkTime / 2.0f;
    }
    float delayTime = walkTime / frameCount;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
    [self.doctorSpriteBatchNode addChild:doctorSprite];
    
    // 动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    
    id actDelay = [CCDelayTime actionWithDuration:delayTime];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        [(GameStageScene *)object addDistanceOfPatientAndDoctor:1.5f];
    }];
    id actSeq1 = [CCSequence actions:actDelay, actCallBlock, nil];
    id actRepeat = [CCRepeat actionWithAction:actSeq1 times:frameCount];
    
    id actSpawn = [CCSpawn actions:actAnimate, actRepeat, nil];
    
    id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        self.isMoving = NO;
    }];
    id actSeq = [CCSequence actions:actSpawn, actCallBlockN, nil];
    [doctorSprite runAction:actSeq];
}


// 假动作
- (void) feint {
    
    // 清除所有帧
    [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
    
    // 释放内存
//    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
//    [[CCTextureCache sharedTextureCache] removeUnusedTextures];
    
    // 设置Texture
    NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_FEINT]];
    int randIndex = arc4random() % [animationInfos count];
    
    // 清理上次占用的内存
    if (randIndex != preIndexForFeint) {
        
        // 清理之前的内存
        NSString *fileNameForClear = [[animationInfos objectAtIndex:preIndexForFeint] objectForKey:@"fileName"];
        NSString *cczFileNameForClear = [fileNameForClear stringByAppendingString:@".pvr.ccz"];
        NSString *plistFileNameForClear = [fileNameForClear stringByAppendingString:@".plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFramesFromFile:plistFileNameForClear];
        [[CCTextureCache sharedTextureCache] removeTextureForKey:cczFileNameForClear];
        
        // 记录本次Index
        preIndexForFeint = randIndex;
    }
    
    NSDictionary *animationInfo = [animationInfos objectAtIndex:randIndex];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];

    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];            
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.doctorSpriteBatchNode setTexture:texture];
    
    
    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
    for(int i = 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 创建动画对象
    float delayTime = [[animationInfo objectForKey:@"time"] floatValue] / frameCount;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
    [self.doctorSpriteBatchNode addChild:doctorSprite];
    
    // 动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        self.isMoving = NO;
    }];
    id actSeq = [CCSequence actions:actAnimate, actCallBlockN, nil];
    [doctorSprite runAction:actSeq];
    
    
    
    
    
    /* backup */
    /*
     // 清除所有帧
     [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
     
     // 释放内存
     [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
     [[CCTextureCache sharedTextureCache] removeUnusedTextures];
     
     // 设置Texture
     NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_FEINT]];
     int randIndex = arc4random() % [animationInfos count];
     NSDictionary *animationInfo = [animationInfos objectAtIndex:randIndex];
     NSString *fileName = [animationInfo objectForKey:@"fileName"];
     
     NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
     NSString *plistFileName = [fileName stringByAppendingString:@".plist"];            
     [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
     
     CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
     [self.doctorSpriteBatchNode setTexture:texture];
     
     
     // 将动画帧放入数组
     NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
     int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
     NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
     for(int i = 1; i <= frameCount; i++) {
     [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
     }
     
     // 创建动画对象
     float delayTime = [[animationInfo objectForKey:@"time"] floatValue] / frameCount;
     CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
     
     // 创建用户图像
     NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
     CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
     doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
     [self.doctorSpriteBatchNode addChild:doctorSprite];
     
     // 动作
     id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
     id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
     self.isMoving = NO;
     }];
     id actSeq = [CCSequence actions:actAnimate, actCallBlockN, nil];
     [doctorSprite runAction:actSeq];
     */
    /* backup */
}


// 回头
- (void) turnAroundWithCallback:(id)object {
    
    // 清除所有帧
    [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
    
    // 释放内存
//    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
//    [[CCTextureCache sharedTextureCache] removeUnusedTextures];
    
    // 设置Texture
    NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_TURN_AROUND]];
    int randIndex = arc4random() % [animationInfos count];
    
    // 清理上次占用的内存
    if (randIndex != preIndexForTurnAround) {
        
        // 清理之前的内存
        NSString *fileNameForClear = [[animationInfos objectAtIndex:preIndexForTurnAround] objectForKey:@"fileName"];
        NSString *cczFileNameForClear = [fileNameForClear stringByAppendingString:@".pvr.ccz"];
        NSString *plistFileNameForClear = [fileNameForClear stringByAppendingString:@".plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFramesFromFile:plistFileNameForClear];
        [[CCTextureCache sharedTextureCache] removeTextureForKey:cczFileNameForClear];
        
        // 记录本次Index
        preIndexForTurnAround = randIndex;
    }
    
    NSDictionary *animationInfo = [animationInfos objectAtIndex:randIndex];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];            
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.doctorSpriteBatchNode setTexture:texture];
    
    
    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
    for(int i = 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 创建动画对象
    float delayTime = [[animationInfo objectForKey:@"time"] floatValue] / frameCount;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
    [self.doctorSpriteBatchNode addChild:doctorSprite];
    
    // 动作 ------------------------------------------------------------------------------------
    float foundStartTime = [[animationInfo objectForKey:@"foundStartTime"] floatValue];         // 进行发现判定的开始时间
    float foundEndTime = [[animationInfo objectForKey:@"foundEndTime"] floatValue];             // 进行发现判定的结束时间
    float interval = 0.05f;                                                                     // 执行检查的时间间隔
    int repeatTimes = (foundEndTime - foundStartTime) / interval;                               // 检查次数
    
    // 判定是否发现
    id actDelay = [CCDelayTime actionWithDuration:foundStartTime];
    
    id actDelayForRepeat = [CCDelayTime actionWithDuration:interval];
    id actCallBlockCheckFound = [CCCallBlock actionWithBlock:^{
        [(GameStageScene *)object checkFound];
    }];
    id actSeqForRepeat = [CCSequence actions:actDelayForRepeat, actCallBlockCheckFound, nil];
    id actRepeatForCheckFound = [CCRepeat actionWithAction:actSeqForRepeat times:repeatTimes];
    
    id actSeqCheckFound = [CCSequence actions:actDelay, actRepeatForCheckFound, nil];
    
    // 动画动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    
    // 发现判定 + 动画
    id actSpawn = [CCSpawn actions:actSeqCheckFound, actAnimate, nil];
    
    // 更新标记
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        self.isMoving = NO;
        self.isMovingForJustTurnAround = NO;
    }];
    
    // 整体动作
    id actSeq = [CCSequence actions:actSpawn, actCallBlock, nil];
    [doctorSprite runAction:actSeq];
    
    
    
    
    
    /* backup */
    /*
     
     // 清除所有帧
     [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
     
     // 释放内存
     [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
     [[CCTextureCache sharedTextureCache] removeUnusedTextures];
     
     // 设置Texture
     NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_TURN_AROUND]];
     int randIndex = arc4random() % [animationInfos count];
     NSDictionary *animationInfo = [animationInfos objectAtIndex:randIndex];
     NSString *fileName = [animationInfo objectForKey:@"fileName"];
     
     NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
     NSString *plistFileName = [fileName stringByAppendingString:@".plist"];            
     [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
     
     CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
     [self.doctorSpriteBatchNode setTexture:texture];
     
     
     // 将动画帧放入数组
     NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
     int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
     NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];
     for(int i = 1; i <= frameCount; i++) {
     [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
     }
     
     // 创建动画对象
     float delayTime = [[animationInfo objectForKey:@"time"] floatValue] / frameCount;
     CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
     
     // 创建用户图像
     NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
     CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
     doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
     [self.doctorSpriteBatchNode addChild:doctorSprite];
     
     // 动作
     id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
     id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
     self.isMoving = NO;
     self.isMovingForJustTurnAround = NO;
     [(GameStageScene *)object checkFound];
     }];
     id actSeq = [CCSequence actions:actAnimate, actCallBlockN, nil];
     [doctorSprite runAction:actSeq];
     */
    /* backup */
}


// 被击中
- (void) damageWithCallback:(id)object
                vertigoTime:(int)vertigoTime {
    self.isMovingForJustTurnAround = YES;
    [self.doctorSpriteBatchNode stopAllActions];
    
    // 清除所有帧
    [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
    
    // 设置Texture
    NSArray *animationInfos = [self.singleDoctorActionDef objectForKey:[NSString stringWithFormat:@"%i", DOCTOR_ACTION_ID_DAMAGE]];
    
    NSDictionary *animationInfo = [animationInfos objectAtIndex:0];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
    NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
    NSString *plistFileName = [fileName stringByAppendingString:@".plist"];            
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
    
    CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
    [self.doctorSpriteBatchNode setTexture:texture];
    
    
    // 将动画帧放入数组
    NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
    int frameCount = [[animationInfo objectForKey:@"frameCount"] intValue];                     // 总帧数
    int vertigoFrameStart = [[animationInfo objectForKey:@"vertigoFrameStart"] intValue];       // 眩晕开始帧号
    int vertigoFrameEnd = [[animationInfo objectForKey:@"vertigoFrameEnd"] intValue];           // 眩晕结束帧号
    int foundFrameStart = [[animationInfo objectForKey:@"foundFrameStart"] intValue];           // 发现判定开始帧号
    int foundFrameEnd = [[animationInfo objectForKey:@"foundFrameEnd"] intValue];               // 发现判定结束帧号
    float extendSeconds = vertigoTime;                                                          // 延长的秒数
    NSString *frameNameTemplate = [fileName stringByAppendingString:@"_%i.png"];                // 帧名称模板
    
    // 添加被命中部分（1/3 阶段）
    for(int i = 1; i <= vertigoFrameStart - 1; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    // 添加眩晕部分（2/3 阶段）
    int frameCountForVertigo = extendSeconds * FRAMES_PER_SECOND;
    for(int i = 0; i < frameCountForVertigo; i++) {
        int tempFrameNum = i % (vertigoFrameEnd - vertigoFrameStart + 1) + vertigoFrameStart;
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, tempFrameNum]]];
    }
    
    // 添加回头部分（3/3 阶段）
    for(int i = vertigoFrameEnd + 1; i <= frameCount; i++) {
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:[NSString stringWithFormat:frameNameTemplate, i]]];
    }
    
    
    // 创建动画对象
    float delayTime = 1.0f / 25.0f;
    CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:delayTime];
    
    // 创建用户图像
    NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
    CCSprite *doctorSprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
    doctorSprite.anchorPoint = ccp(0.5f, 0.0f);
    [self.doctorSpriteBatchNode addChild:doctorSprite];
    
    // 动作 ------------------------------------------------------------------------------------
    float foundStartTime = ((vertigoFrameStart - 1) + frameCountForVertigo + (foundFrameStart - vertigoFrameEnd)) * delayTime;   // 进行发现判定的开始时间
    float foundEndTime = ((vertigoFrameStart - 1) + frameCountForVertigo + (foundFrameEnd - vertigoFrameEnd)) * delayTime;       // 进行发现判定的结束时间
    float interval = 0.05f;                                                                                                      // 执行检查的时间间隔
    int repeatTimes = (foundEndTime - foundStartTime) / interval;                                                                // 检查次数
    
    // 判定是否发现
    id actDelay = [CCDelayTime actionWithDuration:foundStartTime];
    
    id actDelayForRepeat = [CCDelayTime actionWithDuration:interval];
    id actCallBlockCheckFound = [CCCallBlock actionWithBlock:^{
        [(GameStageScene *)object checkFound];
    }];
    id actSeqForRepeat = [CCSequence actions:actDelayForRepeat, actCallBlockCheckFound, nil];
    id actRepeatForCheckFound = [CCRepeat actionWithAction:actSeqForRepeat times:repeatTimes];
    
    id actSeqCheckFound = [CCSequence actions:actDelay, actRepeatForCheckFound, nil];
    
    // 动画动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    
    // 发现判定 + 动画
    id actSpawn = [CCSpawn actions:actSeqCheckFound, actAnimate, nil];
    
    // 更新标记
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        self.isMoving = NO;
        self.isMovingForJustTurnAround = NO;
        
        // 清理内存
//        [self.doctorSpriteBatchNode removeAllChildrenWithCleanup:YES];
//        [[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFramesFromFile:plistFileName];
//        [[CCTextureCache sharedTextureCache] removeTextureForKey:cczFileName];
    }];
    
    // 整体动作
    id actSeq = [CCSequence actions:actSpawn, actCallBlock, nil];
    [doctorSprite runAction:actSeq];
}


// 停止，然后假动作
- (void) stayAndFeint {
    if (self.isMovingForJustTurnAround == YES) {
        return;
    }
    
    // 动作
    id actCallBlockN1 = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        [self stayWithMoving:YES];
    }];
    id actDelay = [CCDelayTime actionWithDuration:2.0f];
    id actCallBlockN2 = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        [self feint];
    }];
    id actSeq = [CCSequence actions:actCallBlockN1, actDelay, actCallBlockN2, nil];
    [self.doctorSpriteBatchNode runAction:actSeq];
}


// 停止，然后回头
- (void) stayAndTurnAroundWithCallback:(id)object {
    if (self.isMovingForJustTurnAround == YES) {
        return;
    }
    
    // 动作
    id actCallBlockN1 = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        [self stayWithMoving:YES];
    }];
    id actDelay = [CCDelayTime actionWithDuration:2.0f];
    id actCallBlockN2 = [CCCallBlockN actionWithBlock:^(CCNode *node) {
        [self turnAroundWithCallback:object];
    }];
    id actSeq = [CCSequence actions:actCallBlockN1, actDelay, actCallBlockN2, nil];
    [self.doctorSpriteBatchNode runAction:actSeq];
}


// 立即回头
- (void) justTurnAroundWithCallback:(id)object {
    if (self.isMovingForJustTurnAround == NO) {
        self.isMovingForJustTurnAround = YES;
    
        // 停止所有动作
        [self.doctorSpriteBatchNode stopAllActions];
        
        // 回头
        [self turnAroundWithCallback:object];
    }
}


// 立即停止
- (void) justStand {
    
    // 停止所有动作
    [self.doctorSpriteBatchNode stopAllActions];
    
    // 停止
    [self stayWithMoving:NO];
    self.isMoving = NO;
    self.isMovingForJustTurnAround = NO;
}


- (void) dealloc {
    self.singleDoctorActionDef = nil;
    self.doctorSpriteBatchNode = nil;
    [super dealloc];
}


@end
