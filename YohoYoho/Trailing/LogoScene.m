//
//  LogoScene.m
//  YohoYoho
//
//  Created by  on 12-2-16.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "LogoScene.h"


// ----------------- Logo场景背景层 -------------------
@implementation LogoBgLayer

- (id) init {
    if (self = [super init]) {
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        CCSprite *bg = [CCSprite spriteWithFile:@"logo.jpg"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
        
        // 一定时间后跳转到主画面
        id actDelay = [CCDelayTime actionWithDuration:2.0f];
        id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
            [delegate.delegateLogic goToTitleScene];
        }];
        id actSeq = [CCSequence actions:actDelay, actCallBlockN, nil];
        [self runAction:actSeq];
    }
    
    return self;
}

@end


// ------------------- Logo场景 ---------------------
@implementation LogoScene

+ (id) scene {
    CCScene *logoScene = [LogoScene node];
    
    LogoBgLayer *logoBgLayer = [LogoBgLayer node];
    
    [logoScene addChild:logoBgLayer];
    
    return logoScene;
}

@end