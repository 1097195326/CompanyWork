//
//  HelpLayer.m
//  YohoYoho
//
//  Created by  on 12-7-1.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "HelpLayer.h"


@implementation HelpLayer


// 初始化方法
- (id) init {
	if (self = [super init]) {
		CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        
		// 添加背景 ----------------------------------------------
        CCSprite* bg = [CCSprite spriteWithFile:@"help.png"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
        
		// 设置允许点击
		self.isTouchEnabled = YES;
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
    [self removeFromParentAndCleanup:YES];
	return YES;
}


@end