//
//  MapScene.m
//  YohoYoho
//
//  Created by Young Leon on 12-3-3.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "MapScene.h"
#import "AppDelegate.h"
#import "AppProfile.h"
#import "ShopLayer.h"


// ----------------- 场景背景层 -------------------
@implementation MapBgLayer


- (id) init {
    if ( self = [super init] ) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加背景
        CCSprite *bg = [CCSprite spriteWithFile:@"map_bg.jpg"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
    }
    
    return self;
}


@end


// ----------------- 场景菜单层 -------------------
@implementation MapMenuLayer


// 加载层内容，初始化变量
- (void) loadContentsOfLayer {
    //CGSize winSize = [[CCDirector sharedDirector] winSize];
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 添加关卡按钮
    NSDictionary *stageDef = ((MapScene *)[self parent]).stageDefinitionDM.data;
    NSEnumerator *keyEnumerator = [stageDef keyEnumerator];
    NSString *key;
    while (key = [keyEnumerator nextObject]) {
        NSDictionary *singleStageDef = [stageDef objectForKey:key];
        
        // 检查该关卡是否锁定
        BOOL locked = [delegate.delegateLogic.appProfile stageLockWithDifficult:delegate.delegateLogic.difficult
                                                                          stage:[key intValue]
                       ];
        
        CCSprite *spriteForStageMenuItemNormal = nil;
        CCSprite *spriteForStageMenuItemSelected = nil;
        CCMenuItem *menuItemForStage = nil;
        if (locked == YES) {
            
            // 放置已锁定的按钮，不可点击
            spriteForStageMenuItemNormal = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"mapImageLock"]];
            spriteForStageMenuItemSelected = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"mapImageLock"]];
            menuItemForStage = [CCMenuItemSprite itemFromNormalSprite:spriteForStageMenuItemNormal
                                                                   selectedSprite:spriteForStageMenuItemSelected
                                            ];
        } else {
            
            // 放置未锁定的按钮
            spriteForStageMenuItemNormal = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"mapImageNormal"]];
            spriteForStageMenuItemSelected = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"mapImageNormal"]];
            menuItemForStage = [CCMenuItemSprite itemFromNormalSprite:spriteForStageMenuItemNormal
                                                                   selectedSprite:spriteForStageMenuItemSelected
                                                                           target:self
                                                                         selector:@selector(onStageSelected:)
                                            ];
        }
        
        // 使用关卡号设置tag
        menuItemForStage.tag = [key intValue];
        
        CCMenu *menuForStage = [CCMenu menuWithItems:menuItemForStage, nil];
        int x = [[singleStageDef objectForKey:@"mapImageX"] intValue];
        int y = [[singleStageDef objectForKey:@"mapImageY"] intValue];
        menuForStage.position = ccp(x, y);
        [self addChild:menuForStage];
    }
    
    
    
    // 添加返回按钮 -----------------------------------------------------------------------------
    CCMenuItem *menuItemReturn = [CCMenuItemImage itemFromNormalImage:@"btn_return_on_select_difficult_scene_normal.png"
                                                        selectedImage:@"btn_return_on_select_difficult_scene_normal.png"
                                                                block:^(id sender) {
                                                                    [delegate.delegateLogic goToSelectDifficultScene];
                                                                }];
    CCMenu *menuReturn = [CCMenu menuWithItems:menuItemReturn, nil];
    menuReturn.position = ccp(60, 710);
    [self addChild:menuReturn];
    
    
    // 添加商店按钮 -----------------------------------------------------------------------------
    CCSprite *spriteForMenuItemShopNormal = [CCSprite spriteWithFile:@"btn_shop_normal.png"];
    CCSprite *spriteForMenuItemShopSelected = [CCSprite spriteWithFile:@"btn_shop_normal.png"];
    CCMenuItem *menuItemForShop = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemShopNormal
                                                          selectedSprite:spriteForMenuItemShopSelected
                                                                  target:self
                                                                selector:@selector(onShopSelected:)];
    
    CCMenu *menu = [CCMenu menuWithItems:menuItemForShop, nil];
    menu.position = ccp(200, 700);
    [self addChild:menu];
}


// 关卡被按下
- (void) onStageSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 设置关卡
    delegate.delegateLogic.stage = ((CCMenuItem *)sender).tag;
    
    // 跳转到游戏场景
    [delegate.delegateLogic goToGameStageScene];
}


// 商店被按下
- (void) onShopSelected:(id)sender {
    [(id)[self parent] showShop];
}


@end


// ------------------- 场景 ---------------------
@implementation MapScene

@synthesize stageDefinitionDM = stageDefinitionDM_;


+ (id) scene {
    MapScene *scene = [MapScene node];
    
    MapBgLayer *bgLayer = [MapBgLayer node];
    [scene addChild:bgLayer];
    
    MapMenuLayer *menuLayer = [MapMenuLayer node];
    [scene addChild:menuLayer];
    [menuLayer loadContentsOfLayer];
    
    return scene;
}


- (id) init {
    if (self = [super init]) {
        self.stageDefinitionDM = [[[StageDefinitionDM alloc] init] autorelease];
    }
    
    return self;
}


// 显示商店
- (void) showShop {
    ShopLayer *shopLayer = [ShopLayer node];
    [self addChild:shopLayer];
}


- (void) dealloc {
    self.stageDefinitionDM = nil;
    [super dealloc];
}

@end
