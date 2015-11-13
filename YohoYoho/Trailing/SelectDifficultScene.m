//
//  SelectDifficultScene.m
//  YohoYoho
//
//  Created by  on 12-2-28.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "SelectDifficultScene.h"
#import "GameConfig.h"
#import "AppDelegate.h"


// ----------------- 场景背景层 -------------------
@implementation SelectDifficultBgLayer


- (id) init {
    if ( self = [super init] ) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加底层背景
        CCSprite *underBg = [CCSprite spriteWithFile:@"select_mode_bg_2.png"];
        underBg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:underBg];
        
        // 添加背景
        CCSprite *bg = [CCSprite spriteWithFile:@"select_difficult_bg.png"];
        bg.position = ccp(winSize.width / 2, -bg.contentSize.height / 2);
        [self addChild:bg];
        
        // 背景动作
        id actMoveTo = [CCEaseIn actionWithAction:[CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, bg.contentSize.height / 2)] rate:0.5f];
        id actJumpBy = [CCJumpBy actionWithDuration:0.2f position:ccp(0, 0) height:-15 jumps:1];
        id actSeq = [CCSequence actions:actMoveTo, actJumpBy, nil];
        [bg runAction:actSeq];
        
        
        // 添加简单难度按钮
        CCSprite *spriteForDifficultEasyMenuItemNormal = [CCSprite spriteWithFile:@"difficult_easy_normal.png"];
        CCSprite *spriteForDifficultEasyMenuItemSelected = [CCSprite spriteWithFile:@"difficult_easy_normal.png"];
        CCMenuItem *menuItemDifficultEasy = [CCMenuItemSprite itemFromNormalSprite:spriteForDifficultEasyMenuItemNormal
                                                                 selectedSprite:spriteForDifficultEasyMenuItemSelected
                                                                         target:self
                                                                       selector:@selector(onDifficultBtnSelected:)
                                          ];
        menuItemDifficultEasy.tag = DIFFICULT_EASY;
        CCMenu *menuDifficultEasy = [CCMenu menuWithItems:menuItemDifficultEasy, nil];
        menuDifficultEasy.position = ccp(winSize.width / 2 + 20, winSize.height / 2 + 20);
        [bg addChild:menuDifficultEasy];
        
        
        // 添加普通难度按钮
        CCSprite *spriteForDifficultNormalMenuItemNormal = [CCSprite spriteWithFile:@"difficult_normal_normal.png"];
        CCSprite *spriteForDifficultNormalMenuItemSelected = [CCSprite spriteWithFile:@"difficult_normal_normal.png"];
        CCMenuItem *menuItemDifficultNormal = [CCMenuItemSprite itemFromNormalSprite:spriteForDifficultNormalMenuItemNormal
                                                                    selectedSprite:spriteForDifficultNormalMenuItemSelected
                                                                            target:self
                                                                          selector:@selector(onDifficultBtnSelected:)
                                             ];
        menuItemDifficultNormal.tag = DIFFICULT_NORMAL;
        CCMenu *menuDifficultNormal = [CCMenu menuWithItems:menuItemDifficultNormal, nil];
        menuDifficultNormal.position = ccpAdd(menuDifficultEasy.position, ccp(10, -80));
        [bg addChild:menuDifficultNormal];
        
        
        // 添加困难难度按钮
        CCSprite *spriteForDifficultHardMenuItemNormal = [CCSprite spriteWithFile:@"difficult_hard_normal.png"];
        CCSprite *spriteForDifficultHardMenuItemSelected = [CCSprite spriteWithFile:@"difficult_hard_normal.png"];
        CCMenuItem *menuItemDifficultHard = [CCMenuItemSprite itemFromNormalSprite:spriteForDifficultHardMenuItemNormal
                                                                      selectedSprite:spriteForDifficultHardMenuItemSelected
                                                                              target:self
                                                                            selector:@selector(onDifficultBtnSelected:)
                                               ];
        menuItemDifficultHard.tag = DIFFICULT_HARD;
        CCMenu *menuDifficultHard = [CCMenu menuWithItems:menuItemDifficultHard, nil];
        menuDifficultHard.position = ccpAdd(menuDifficultNormal.position, ccp(10, -80));
        [bg addChild:menuDifficultHard];
        
        
        // 添加返回按钮
        CCSprite *spriteForReturnMenuItemNormal = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
        CCSprite *spriteForReturnMenuItemSelected = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
        CCMenuItem *menuItemReturn = [CCMenuItemSprite itemFromNormalSprite:spriteForReturnMenuItemNormal
                                                             selectedSprite:spriteForReturnMenuItemSelected
                                                                     target:self
                                                                   selector:@selector(onReturnBtnSelected:)
                                      ];
        CCMenu *menuReturn = [CCMenu menuWithItems:menuItemReturn, nil];
//        menuReturn.position = ccp(230, 130);
        menuReturn.position = ccp(60, 710);
        [self addChild:menuReturn];
    }
    
    return self;
}


// 难度按钮按下
- (void) onDifficultBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 设置难度
    delegate.delegateLogic.difficult = ((CCMenuItem *)sender).tag;
    
    // 跳转到地图
    [delegate.delegateLogic goToMapScene];
}


// 当返回按钮按下
- (void) onReturnBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToPatientModeSelectCharacterScene];
}


@end


// ------------------- 场景 ---------------------
@implementation SelectDifficultScene


+ (id) scene {
    SelectDifficultScene *scene = [SelectDifficultScene node];
    SelectDifficultBgLayer *bgLayer = [SelectDifficultBgLayer node];
    [scene addChild:bgLayer];
    
    return scene;
}


@end
