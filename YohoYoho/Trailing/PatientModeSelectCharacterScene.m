//
//  PatientModeSelectCharacterScene.m
//  YohoYoho
//
//  Created by  on 12-2-27.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "PatientModeSelectCharacterScene.h"
#import "AppDelegate.h"
#import "AppProfile.h"
#import "GameConfig.h"
#import "CoverLayer.h"

// ----------------- 场景背景层 -------------------
@implementation PatientModeSelectCharacterBgLayer

@synthesize pathForPatient1 = pathForPatient1_;
@synthesize pathForPatient2 = pathForPatient2_;
@synthesize pathForPatient3 = pathForPatient3_;
@synthesize pathForPatient4 = pathForPatient4_;

CCSprite *bg;

- (id) init {
    if( self = [super init] ){
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加底层背景
        CCSprite *underBg = [CCSprite spriteWithFile:@"select_mode_bg_2.png"];
        underBg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:underBg];
        
        // 添加背景
        bg = [CCSprite spriteWithFile:@"patient_mode_select_character_bg.png"];
        bg.position = ccp(winSize.width / 2, -bg.contentSize.height / 2);
        [self addChild:bg];
        
        // 背景动作
        id actMoveTo = [CCEaseIn actionWithAction:[CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, bg.contentSize.height / 2)] rate:0.5f];
        id actJumpBy = [CCJumpBy actionWithDuration:0.2f position:ccp(0, 0) height:-15 jumps:1];
        id actSeq = [CCSequence actions:actMoveTo, actJumpBy, nil];
        [bg runAction:actSeq];
        
        
        // 设置病人1选区（左）
        CGPoint centrialPoint = ccp(winSize.width / 2, winSize.height / 2);
        self.pathForPatient1 = CGPathCreateMutable();
        CGPathMoveToPoint(self.pathForPatient1, NULL, centrialPoint.x - 371.0f, centrialPoint.y + 211.0f);
        CGPathAddLineToPoint(self.pathForPatient1, NULL, centrialPoint.x - 299.0f, centrialPoint.y + 212.0f);
        CGPathAddLineToPoint(self.pathForPatient1, NULL, centrialPoint.x - 94.0f, centrialPoint.y - 300.0f);
        CGPathAddLineToPoint(self.pathForPatient1, NULL, centrialPoint.x - 356.0f, centrialPoint.y - 304.0f);
        CGPathCloseSubpath(self.pathForPatient1);
        
        // 病人1锁定
        BOOL locked = [delegate.delegateLogic.appProfile patientLockWithPatientId:E_PATIENT_ID_NOBLE];
        if (locked == YES) {
            
            // 添加锁
            CCSprite *lock = [CCSprite spriteWithFile:@"lock.png"];
            lock.position = ccp(centrialPoint.x - 250.0f, centrialPoint.y - 111.0f);
            [bg addChild:lock];
        }
        
        
        // 设置病人2选区（上）
        self.pathForPatient2 = CGPathCreateMutable();
        CGPathMoveToPoint(self.pathForPatient2, NULL, centrialPoint.x - 277.0f, centrialPoint.y + 215.0f);
        CGPathAddLineToPoint(self.pathForPatient2, NULL, centrialPoint.x + 84.0f, centrialPoint.y + 228.0f);
        CGPathAddLineToPoint(self.pathForPatient2, NULL, centrialPoint.x + 131.0f, centrialPoint.y + 111.0f);
        CGPathAddLineToPoint(self.pathForPatient2, NULL, centrialPoint.x - 161.0f, centrialPoint.y - 80.0f);
        CGPathCloseSubpath(self.pathForPatient2);
        
        
        // 设置病人3选区（右）
        self.pathForPatient3 = CGPathCreateMutable();
        CGPathMoveToPoint(self.pathForPatient3, NULL, centrialPoint.x + 105.0f, centrialPoint.y + 227.0f);
        CGPathAddLineToPoint(self.pathForPatient3, NULL, centrialPoint.x + 365.0f, centrialPoint.y + 233.0f);
        CGPathAddLineToPoint(self.pathForPatient3, NULL, centrialPoint.x + 390.0f, centrialPoint.y - 277.0f);
        CGPathAddLineToPoint(self.pathForPatient3, NULL, centrialPoint.x + 303.0f, centrialPoint.y - 287.0f);
        CGPathCloseSubpath(self.pathForPatient3);
        
        // 病人3锁定
        locked = [delegate.delegateLogic.appProfile patientLockWithPatientId:E_PATIENT_ID_DEPRESSION];
        if (locked == YES) {
            
            // 添加锁
            CCSprite *lock = [CCSprite spriteWithFile:@"lock.png"];
            lock.position = ccp(centrialPoint.x + 300.0f, centrialPoint.y + 60.0f);
            [bg addChild:lock];
        }
        
        
        // 设置病人4选区（下）
        self.pathForPatient4 = CGPathCreateMutable();
        CGPathMoveToPoint(self.pathForPatient4, NULL, centrialPoint.x - 156.0f, centrialPoint.y - 95.0f);
        CGPathAddLineToPoint(self.pathForPatient4, NULL, centrialPoint.x + 139.0f, centrialPoint.y + 94.0f);
        CGPathAddLineToPoint(self.pathForPatient4, NULL, centrialPoint.x + 283.0f, centrialPoint.y - 289.0f);
        CGPathAddLineToPoint(self.pathForPatient4, NULL, centrialPoint.x - 74.0f, centrialPoint.y - 302.0f);
        CGPathCloseSubpath(self.pathForPatient4);
        
        // 病人4锁定
        locked = [delegate.delegateLogic.appProfile patientLockWithPatientId:E_PATIENT_ID_FAT];
        if (locked == YES) {
            
            // 添加锁
            CCSprite *lock = [CCSprite spriteWithFile:@"lock.png"];
            lock.position = ccp(centrialPoint.x + 80.0f, centrialPoint.y - 120.0f);
            [bg addChild:lock];
        }
        
        
        //row 1, col 1
//        -371.0, 211.0
//        -299.0, 212.0
//        -94.0, -300.0
//        -356.0, -304.0
        
        //row 1, col 1
//        -277.0, 215.0
//        84.0, 228.0
//        131.0, 111.0
//        -161.0, -80.0
        
        //row 1, col 1
//        105.0, 227.0
//        365.0, 233.0
//        390.0, -277.0
//        303.0, -287.0
        
        //row 1, col 1
//        -156.0, -95.0
//        139.0, 94.0
//        283.0, -289.0
//        -74.0, -302.0
        
/*        
        // 添加病人模式人物按钮
        CCMenu *menu = [CCMenu menuWithItems:nil];
        for (int i = 1; i <= 4; i++) {
            CCSprite *spriteForMenuItemNormal = [CCSprite spriteWithFile:[NSString stringWithFormat:@"patient_mode_character_%i_normal.png", i]];
            CCSprite *spriteForMenuItemSelected = [CCSprite spriteWithFile:[NSString stringWithFormat:@"patient_mode_character_%i_normal.png", i]];
            CCMenuItem *menuItem = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemNormal
                                                           selectedSprite:spriteForMenuItemSelected
                                                                   target:self
                                                                 selector:@selector(onCharacterSelected:)
                                    ];
            
            // 使用tag设置角色ID
            menuItem.tag = i;
            
            // 添加menuItem到menu
            [menu addChild:menuItem];
        }
        
        menu.position = ccp(winSize.width / 2, winSize.height / 2);
        [menu alignItemsHorizontallyWithPadding:30];
        [self addChild:menu];
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
        
        
        // 设置允许点击
        self.isTouchEnabled = YES;
    }
    
    return self;
}


// 选择人物
- (void) onCharacterSelected:(int)patientId {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 检查是否被锁定
    BOOL locked = [delegate.delegateLogic.appProfile patientLockWithPatientId:patientId];
    if (locked == YES) {
        return;
    }
    
    // 显示病人描述
    [(PatientModeSelectCharacterScene *)[self parent] showDescriptionLayerWithPatientId:patientId];
}


// 当返回按钮按下
- (void) onReturnBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
//    [delegate.delegateLogic goToSelectModeScene];
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
    
    // 点击病人
    if (CGPathContainsPoint(self.pathForPatient1, NULL, touchPoint, NO)) {
        [self onCharacterSelected:E_PATIENT_ID_NOBLE];
    } else if (CGPathContainsPoint(self.pathForPatient2, NULL, touchPoint, NO)) {
        [self onCharacterSelected:E_PATIENT_ID_GIRL];
    } else if (CGPathContainsPoint(self.pathForPatient3, NULL, touchPoint, NO)) {
        [self onCharacterSelected:E_PATIENT_ID_DEPRESSION];
    } else if (CGPathContainsPoint(self.pathForPatient4, NULL, touchPoint, NO)) {
        [self onCharacterSelected:E_PATIENT_ID_FAT];
    }
    CCLOG(@"touched.");
	return YES;
}


- (void) dealloc {
    CGPathRelease(self.pathForPatient1);
    CGPathRelease(self.pathForPatient2);
    CGPathRelease(self.pathForPatient3);
    CGPathRelease(self.pathForPatient4);
    [super dealloc];
}


@end


// --------------------- 人物描述层 ------------------------
@implementation PatientModeSelectCharacterDescriptionLayer

// 初始化方法
- (id) initWithPatientId:(int)patientId {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
//        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        
        
        // 添加描述
        NSString *fileName = [NSString stringWithFormat:@"patient_%i_description.png", patientId];
        CCSprite *description = [CCSprite spriteWithFile:fileName];
        description.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:description];
		
        
        // 添加进入按钮
        CCMenuItem *menuItemForEnter = [CCMenuItemImage itemFromNormalImage:@"btn_enter_normal.png"
                                                              selectedImage:@"btn_enter_normal.png"
                                                                      block:^(id sender) {
                                                                          
                                                                          // 执行选择病人逻辑
                                                                          [(PatientModeSelectCharacterScene *)[self parent] selectPatientWithPatientId:patientId];
                                                                          
                                                                          // 清除本层
                                                                          [self removeFromParentAndCleanup:YES];
                                                                      }];
        CCMenu *menu = [CCMenu menuWithItems:menuItemForEnter, nil];
        menu.position = ccp(description.contentSize.width - 60, 40);
        [description addChild:menu];
        
        
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


// ------------------- 场景 ---------------------
@implementation PatientModeSelectCharacterScene

+ (id) scene {
    PatientModeSelectCharacterScene *scene = [PatientModeSelectCharacterScene node];
    PatientModeSelectCharacterBgLayer *bgLayer = [PatientModeSelectCharacterBgLayer node];
    bgLayer.tag = 1001;
    [scene addChild:bgLayer];
    
    return scene;
}


// 显示人物描述层
- (void) showDescriptionLayerWithPatientId:(int)patientId {
    PatientModeSelectCharacterDescriptionLayer *descriptionLayer = [[[PatientModeSelectCharacterDescriptionLayer alloc] initWithPatientId:patientId] autorelease];
    [self addChild:descriptionLayer];
}


// 选择人物
- (void) selectPatientWithPatientId:(int)patientId {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 显示遮罩层
    CoverLayer *coverLayer = [CoverLayer node];
    [self addChild:coverLayer z:9999];
    
    // 设置病人角色
    delegate.delegateLogic.patientCharacter = patientId;
    
    // 跳转到选择难度
    id actCallBlock = [CCCallBlock actionWithBlock:^{
//        [delegate.delegateLogic goToSelectDifficultScene];
        [delegate.delegateLogic goToGameStageScene];
    }];
    
    // 执行跳转动画
    PatientModeSelectCharacterBgLayer *bgLayer = (id)[self getChildByTag:1001];
    [bgLayer bgMoveOutWithFinishAction:actCallBlock];
}


@end
