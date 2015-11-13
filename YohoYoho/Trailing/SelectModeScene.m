//
//  SelectModeScene.m
//  YohoYoho
//
//  Created by  on 12-2-22.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "SelectModeScene.h"
#import "AppDelegate.h"
#import "GameConfig.h"
#import "HelpLayer.h"
#import "CoverLayer.h"


// ----------------- Logo场景背景层 -------------------
@implementation SelectModeBgLayer

@synthesize pathForPatientMode = pathForPatientMode_;

CCSprite *bg;

- (id) init {
    if (self = [super init]) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加底层背景
        CCSprite *underBg = [CCSprite spriteWithFile:@"select_mode_bg_2.png"];
        underBg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:underBg];
        
        // 添加背景
        bg = [CCSprite spriteWithFile:@"select_mode_bg.png"];
        bg.position = ccp(winSize.width / 2, -bg.contentSize.height / 2);
        [self addChild:bg];
        
        // 背景动作
        id actMoveTo = [CCEaseIn actionWithAction:[CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, bg.contentSize.height / 2)] rate:0.5f];
        id actJumpBy = [CCJumpBy actionWithDuration:0.2f position:ccp(0, 0) height:-15 jumps:1];
        id actSeq = [CCSequence actions:actMoveTo, actJumpBy, nil];
        [bg runAction:actSeq];
        
        
        // 设置病人模式选区
        CGPoint centrialPoint = ccp(winSize.width / 2, winSize.height / 2);
        self.pathForPatientMode = CGPathCreateMutable();
        CGPathMoveToPoint(self.pathForPatientMode, NULL, centrialPoint.x - 360.0f, centrialPoint.y + 202.0f);
        CGPathAddLineToPoint(self.pathForPatientMode, NULL, centrialPoint.x + 42.0f, centrialPoint.y + 207.0f);
        CGPathAddLineToPoint(self.pathForPatientMode, NULL, centrialPoint.x - 56.0f, centrialPoint.y - 297.0f);
        CGPathAddLineToPoint(self.pathForPatientMode, NULL, centrialPoint.x - 352.0f, centrialPoint.y - 305.0f);
        CGPathCloseSubpath(self.pathForPatientMode);

        
        // 添加医生模式锁
        CCSprite *lock = [CCSprite spriteWithFile:@"lock_on_select_mode_scene.png"];
        lock.position = ccp(700, 220);
        [bg addChild:lock];
        
/*        
        // 添加病人模式按钮
        CCSprite *spriteForPatientModeMenuItemNormal = [CCSprite spriteWithFile:@"btn_patient_mode_normal.png"];
        CCSprite *spriteForPatientModeMenuItemSelected = [CCSprite spriteWithFile:@"btn_patient_mode_normal.png"];
        CCMenuItem *menuItemPatientMode = [CCMenuItemSprite itemFromNormalSprite:spriteForPatientModeMenuItemNormal
                                                                  selectedSprite:spriteForPatientModeMenuItemSelected
                                                                          target:self
                                                                        selector:@selector(onPatientModeBtnSelected:)
                                    ];
        CCMenu *menuPatientMode = [CCMenu menuWithItems:menuItemPatientMode, nil];
        menuPatientMode.position = ccp(winSize.width / 2 - 200, winSize.height / 2);
        [self addChild:menuPatientMode];
        
        
        // 添加医生模式按钮
        CCSprite *spriteForDoctorModeMenuItemNormal = [CCSprite spriteWithFile:@"btn_doctor_mode_normal.png"];
        CCSprite *spriteForDoctorModeMenuItemSelected = [CCSprite spriteWithFile:@"btn_doctor_mode_normal.png"];
        CCMenuItem *menuItemDoctorMode = [CCMenuItemSprite itemFromNormalSprite:spriteForDoctorModeMenuItemNormal
                                                                  selectedSprite:spriteForDoctorModeMenuItemSelected
                                                                          target:self
                                                                        selector:@selector(onDoctorModeBtnSelected:)
                                           ];
        CCMenu *menuDoctorMode = [CCMenu menuWithItems:menuItemDoctorMode, nil];
        menuDoctorMode.position = ccp(winSize.width / 2 + 200, winSize.height / 2);
        [self addChild:menuDoctorMode];
*/
        
        // 添加返回按钮
        CCSprite *spriteForReturnMenuItemNormal = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
        CCSprite *spriteForReturnMenuItemSelected = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
        CCMenuItem *menuItemReturn = [CCMenuItemSprite itemFromNormalSprite:spriteForReturnMenuItemNormal
                                                             selectedSprite:spriteForReturnMenuItemSelected
                                                                     target:self
                                                                   selector:@selector(onReturnBtnSelected:)
                                          ];
        CCMenu *menuReturn = [CCMenu menuWithItems:menuItemReturn, nil];
        menuReturn.position = ccp(60, 710);
        [self addChild:menuReturn];
        
        
        // 添加帮助按钮
        CCMenuItem *menuItemHelp = [CCMenuItemImage itemFromNormalImage:@"btn_help_normal.png"
                                                          selectedImage:@"btn_help_normal.png"
                                                                  block:^(id sender) {
                                                                      HelpLayer *helpLayer = [HelpLayer node];
                                                                      [self addChild:helpLayer];
                                                                  }];
        CCMenu *menuHelp = [CCMenu menuWithItems:menuItemHelp, nil];
        menuHelp.position = ccp(160, 710);
        [self addChild:menuHelp];
        
        
        // 设置允许点击
        self.isTouchEnabled = YES;
    }
    
    return self;
}


// 当病人模式按钮按下
- (void) onPatientModeBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 显示遮罩层
    CoverLayer *coverLayer = [CoverLayer node];
    [self addChild:coverLayer z:9999];
    
    // 设置游戏模式
    delegate.delegateLogic.gameMode = GAME_MODE_PATIENT;
    
    // 跳转到选择人物画面
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        [delegate.delegateLogic goToPatientModeSelectCharacterScene];
    }];
    [self bgMoveOutWithFinishAction:actCallBlock];
}


// 当医生模式按钮按下
- (void) onDoctorModeBtnSelected:(id)sender {
    NSLog(@"doctor mode selected.");
}


// 当医生模式按钮按下
- (void) onReturnBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToTitleScene];
}


// 背景滑下
- (void) bgMoveOutWithFinishAction:(id)act {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    
    id actJump = [CCJumpBy actionWithDuration:0.2f
                                      position:ccp(0, 0)
                                        height:-20
                                         jumps:2];
    id actMoveTo = [CCEaseOut actionWithAction:[CCMoveBy actionWithDuration:0.5f
                                                                    position:ccp(0, -winSize.height)]
                                            rate:0.5f];
    id actSeq = [CCSequence actions:actJump, actMoveTo, act, nil];
    [bg runAction:actSeq];
}


- (void) registerWithTouchDispatcher {	
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self
                                                     priority:kCCMenuTouchPriority
                                              swallowsTouches:YES];
}


- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event {
	CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];
    
    // 点击病人模式
    if (CGPathContainsPoint(self.pathForPatientMode, NULL, touchPoint, NO)) {
        [self onPatientModeBtnSelected:self];
    }
    
	return YES;
}


- (void) dealloc {
    CGPathRelease(self.pathForPatientMode);
    [super dealloc];
}


@end


// ------------------- Logo场景 ---------------------
@implementation SelectModeScene

+ (id) scene {
    CCScene *selectModeScene = [SelectModeScene node];
    
    SelectModeBgLayer *selectModeBgLayer = [SelectModeBgLayer node];
    
    [selectModeScene addChild:selectModeBgLayer];
    
    return selectModeScene;
}

@end