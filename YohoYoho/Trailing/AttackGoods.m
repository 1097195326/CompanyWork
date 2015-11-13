//
//  AttackGoods.m
//  YohoYoho
//
//  Created by  on 12-6-2.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "AttackGoods.h"
#import "GoodsDefinitionDM.h"


@implementation AttackGoods

@synthesize singleGoodsDef = singleGoodsDef_;
//@synthesize spriteBatchNode = spriteBatchNode_;

const int goodsTag = 101;

// 初始化方法
- (id) initWithGoodsId:(int)goodsId {
    if (self = [super initWithTexture:nil capacity:29]) {
        
        // 创建病人动作定义数据模型对象
        GoodsDefinitionDM *goodsDefinitionDM = [[[GoodsDefinitionDM alloc] init] autorelease];
        
        // 获取单个道具定义
        self.singleGoodsDef = [goodsDefinitionDM singleGoodsDefWithGoodsId:goodsId];
        
        // 设置Texture
        NSDictionary *animationInfo = [self.singleGoodsDef objectForKey:@"animation"];
        NSString *fileName = [animationInfo objectForKey:@"fileName"];
        NSString *cczFileName = [fileName stringByAppendingString:@".pvr.ccz"];
        NSString *plistFileName = [fileName stringByAppendingString:@".plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFileName textureFile:cczFileName];
        
        CCTexture2D *texture = [[CCTextureCache sharedTextureCache] addImage:cczFileName];
        [self setTexture:texture];
//        self.spriteBatchNode = [CCSpriteBatchNode batchNodeWithTexture:texture];
             
        // 创建用户图像
        NSString *firstFrameName = [fileName stringByAppendingString:@"_1.png"];
        CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:firstFrameName];
        sprite.tag = goodsTag;
        [self addChild:sprite];
    }
    
    return self;
}


// 破碎
- (void) crash {
    NSDictionary *animationInfo = [self.singleGoodsDef objectForKey:@"animation"];
    NSString *fileName = [animationInfo objectForKey:@"fileName"];
    
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
    
    // 动作
    id actAnimate = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        
        // 清理内存
        [self removeAllChildrenWithCleanup:YES];
        NSString *cczFileNameForClear = [fileName stringByAppendingString:@".pvr.ccz"];
        NSString *plistFileNameForClear = [fileName stringByAppendingString:@".plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] removeSpriteFramesFromFile:plistFileNameForClear];
        [[CCTextureCache sharedTextureCache] removeTextureForKey:cczFileNameForClear];
        
        [self removeFromParentAndCleanup:YES];
    }];
    id actSeq = [CCSequence actions:actAnimate, actCallBlock, nil];
    CCSprite *sprite = (CCSprite *)[self getChildByTag:goodsTag];
    [sprite runAction:actSeq];
}


// 飞行后破碎
- (void) flyAndCrashWithPosition:(CGPoint)position
                           scale:(float)scale
                          target:(id)target
                        selector:(SEL)selector {
    
    float duration = 0.5f;
    id actMoveTo = [CCMoveTo actionWithDuration:duration position:position];
    id actScaleTo = [CCScaleTo actionWithDuration:duration scale:scale];
    id actSpawn = [CCSpawn actions:actMoveTo, actScaleTo, nil];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        
        // 道具破碎动画
        [self crash];
        
        // 调用回调方法
        if ([target respondsToSelector:selector]) {
            [target performSelector:selector];
        }
    }];
    id actSeq = [CCSequence actions:actSpawn, actCallBlock, nil];
    
    [self runAction:actSeq];
}


- (void) dealloc {
    self.singleGoodsDef = nil;
//    self.spriteBatchNode = nil;
    [super dealloc];
}


@end
