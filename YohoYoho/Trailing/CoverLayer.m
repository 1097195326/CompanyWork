//
//  CoverLayer.m
//  YohoYoho
//
//  Created by  on 12-7-16.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "CoverLayer.h"


@implementation CoverLayer


- (id) init {
    if (self = [super init]) {
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
	return YES;
}


@end
