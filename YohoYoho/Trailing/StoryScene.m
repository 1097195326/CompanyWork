//
//  StoryScene.m
//  YohoYoho
//
//  Created by  on 12-7-10.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "StoryScene.h"
#import "AppDelegate.h"


// ------------------- 故事背景层 ---------------------
@implementation StoryBgLayer

- (id) init {
    if (self = [super init]) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        self.isTouchEnabled = YES;
        
        
        // 添加背景
        CCSprite *bg = [CCSprite spriteWithFile:@"story_bg.png"];
        bg.anchorPoint = ccp(0.0f, 0.0f);
        bg.position = ccp(0, -winSize.height);
        [self addChild:bg];
        
        
        // 动作
        CGPoint point1 = ccpAdd(bg.position, ccp(-100, 100));               // 左上角
        CGPoint point2 = ccp(-winSize.width, -winSize.height);              // 右上角1
        CGPoint point3 = ccpAdd(point2, ccp(0, 250));                       // 右上角2
        CGPoint point4 = ccp(0, 0);                                         // 左下角
        CGPoint point5 = ccp(-winSize.width + 300, 0);                            // 右下角
        
        float moveAroundDistance = 15.0f;
        id actMoveAround = [CCSequence actions:[CCMoveBy actionWithDuration:1.2f position:ccp(moveAroundDistance, moveAroundDistance)],
                                               [CCMoveBy actionWithDuration:1.2f position:ccp(-moveAroundDistance, moveAroundDistance)],
//                                               [CCMoveBy actionWithDuration:1.0f position:ccp(-moveAroundDistance, -moveAroundDistance)],
//                                               [CCMoveBy actionWithDuration:0.8f position:ccp(moveAroundDistance, -moveAroundDistance)],
                            nil];
        id actMoveTo1 = [CCMoveTo actionWithDuration:1.5f position:point1];
        id actMoveTo2 = [CCMoveTo actionWithDuration:0.2f position:point2];
        id actMoveTo3 = [CCMoveTo actionWithDuration:0.2f position:point3];
        id actMoveTo4 = [CCMoveTo actionWithDuration:0.2f position:point4];
//        id actMoveTo5 = [CCMoveTo actionWithDuration:0.2f position:point5];
        id actMoveTo5 = [CCSpawn actions:[CCMoveTo actionWithDuration:0.2f position:point5],
                                         [CCScaleTo actionWithDuration:0.2f scale:0.90f],
                         nil];
        id actScaleTo = [CCSpawn actions:[CCScaleTo actionWithDuration:5.0f scale:1.0f],
                                         [CCMoveTo actionWithDuration:5.0f position:ccp(-winSize.width + 100, 0)],
                         nil];
        
        id actSeq = [CCSequence actions:actMoveTo1, actMoveAround, actMoveTo2, actMoveAround, actMoveTo3, actMoveAround, actMoveTo4, actMoveAround, actMoveTo5, actScaleTo, nil];
        [bg runAction:actSeq];
    }
    
    return self;
}


// 注册点击事件
- (void) registerWithTouchDispatcher {
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self
													 priority:kCCMenuTouchPriority
											  swallowsTouches:YES];
}


// 点击开始
- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event {
    
    // 跳转到选择模式场景
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToSelectModeScene];
    
	return YES;
}


@end


// ------------------- 场景 ---------------------
@implementation StoryScene

+ (id) scene {
    StoryScene *scene = [StoryScene node];
    
    StoryBgLayer *bgLayer = [StoryBgLayer node];
    [scene addChild:bgLayer];
    
    return scene;
}

@end
