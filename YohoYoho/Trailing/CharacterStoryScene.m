//
//  CharacterStory.m
//  YohoYoho
//
//  Created by Young Leon on 12-3-2.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "CharacterStoryScene.h"
#import "AppDelegate.h"


// ----------------- 场景背景层 -------------------
@implementation CharacterStoryBgLayer


- (id) init {
    if ( self = [super init] ) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加背景
        CCSprite *bg = [CCSprite spriteWithFile:@"character_story_bg.jpg"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
        
        // 添加返回按钮
        CCSprite *spriteForSkipMenuItemNormal = [CCSprite spriteWithFile:@"btn_return_on_select_mode_scene_normal.png"];
        CCSprite *spriteForSkipMenuItemSelected = [CCSprite spriteWithFile:@"btn_return_on_select_mode_scene_normal.png"];
        CCMenuItem *menuItemSkip = [CCMenuItemSprite itemFromNormalSprite:spriteForSkipMenuItemNormal
                                                             selectedSprite:spriteForSkipMenuItemSelected
                                                                     target:self
                                                                   selector:@selector(onSkipBtnSelected:)
                                      ];
        CCMenu *menuSkip = [CCMenu menuWithItems:menuItemSkip, nil];
        menuSkip.position = ccp(900, 50);
        [self addChild:menuSkip];
    }
    
    return self;
}


// 跳过按钮按下
- (void) onSkipBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToMapScene];
}


@end


// ------------------- 场景 ---------------------
@implementation CharacterStoryScene


+ (id) scene {
    CharacterStoryScene *scene = [CharacterStoryScene node];
    CharacterStoryBgLayer *bgLayer = [CharacterStoryBgLayer node];
    [scene addChild:bgLayer];
    
    return scene;
}


@end
