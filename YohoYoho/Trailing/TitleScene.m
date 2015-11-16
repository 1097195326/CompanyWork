//
//  TitleScene.m
//  Trailing
//
//  Created by  on 12-2-14.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "TitleScene.h"
#import "AppDelegate.h"
#import "AppProfile.h"
#import "GameConfig.h"
#import "WBSendView.h"


// ----------------- 标题场景背景层 -------------------
@implementation TitleBgLayer

- (id) init {
    if (self = [super init]) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        // 添加背景
        CCSprite *bg = [CCSprite spriteWithFile:@"title_bg.png"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
        // 添加PLAY按钮
        CCSprite *spriteForPlayMenuItemNormal = [CCSprite spriteWithFile:@"btn_play_normal.png"];
        CCSprite *spriteForPlayMenuItemSelected = [CCSprite spriteWithFile:@"btn_play_normal.png"];
        CCMenuItem *menuItemPlay = [CCMenuItemSprite itemFromNormalSprite:spriteForPlayMenuItemNormal
                                                           selectedSprite:spriteForPlayMenuItemSelected
                                                                    target:self
                                                                 selector:@selector(onPlayBtnSelected:)
                                    ];
        CCMenu *menuPlay = [CCMenu menuWithItems:menuItemPlay, nil];
        menuPlay.position = ccp(690, 150);
        [self addChild:menuPlay];
        
        // 添加OPTION按钮
        CCSprite *spriteForOptionMenuItemNormal = [CCSprite spriteWithFile:@"btn_option_normal.png"];
        CCSprite *spriteForOptionMenuItemSelected = [CCSprite spriteWithFile:@"btn_option_normal.png"];
        CCMenuItem *menuItemOption = [CCMenuItemSprite itemFromNormalSprite:spriteForOptionMenuItemNormal
                                                           selectedSprite:spriteForOptionMenuItemSelected
                                                                   target:self
                                                                 selector:@selector(onOptionBtnSelected)
                                    ];
        CCMenu *menuOption = [CCMenu menuWithItems:menuItemOption, nil];
        menuOption.position = ccp(870, 455);
        [self addChild:menuOption];
        
        // 添加SHARE按钮
        CCMenuItem *menuItemShare = [CCMenuItemImage itemFromNormalImage:@"btn_share_normal.png"
                                                           selectedImage:@"btn_share_normal.png"
                                                                  target:self
                                                                selector:@selector(onShareBtnSelected)];
        CCMenu *menuShare = [CCMenu menuWithItems:menuItemShare, nil];
        menuShare.position = ccp(870, 370);
        [self addChild:menuShare];
    }
    
    return self;
}


// 当Play按钮按下
- (void) onPlayBtnSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToStoryScene];
    
}


// 当Option按钮按下
- (void) onOptionBtnSelected {
    [(id)[self parent] showOption];
}


// 当Share按钮按下
- (void) onShareBtnSelected {
    [((TitleScene *)self.parent) showShare];
}


@end


// --------------------- 标题选项层 ------------------------
@implementation TitleOptionLayer

// 初始化方法
- (id) init {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        
		
		// 添加菜单 ----------------------------------------------
        // BGM开关按钮
		CCMenuItem *menuItemForBGMOn = [CCMenuItemImage itemFromNormalImage:@"btn_bgm_on_normal.png"
                                                              selectedImage:@"btn_bgm_on_normal.png"];
		
		CCMenuItem *menuItemForBGMOff = [CCMenuItemImage itemFromNormalImage:@"btn_bgm_off_normal.png"
                                                               selectedImage:@"btn_bgm_off_normal.png"];
        
        CCMenuItemToggle *menuItemForBGM = [CCMenuItemToggle itemWithTarget:self
                                                                   selector:@selector(onBGMSelected:)
                                                                      items:menuItemForBGMOn, menuItemForBGMOff, nil];
        
        // 设置当前选中的项目
        if ([delegate.delegateLogic.appProfile bgm] == NO) {
            menuItemForBGM.selectedIndex = 1;
        }
        
        CCMenu *menuForBGM = [CCMenu menuWithItems:menuItemForBGM, nil];
        menuForBGM.position = ccp(winSize.width / 2 - 50, winSize.height / 2);
        [self addChild:menuForBGM];
        
        
        // SE开关按钮
		CCMenuItem *menuItemForSEOn = [CCMenuItemImage itemFromNormalImage:@"btn_se_on_normal.png"
                                                             selectedImage:@"btn_se_on_normal.png"];
		
		CCMenuItem *menuItemForSEOff = [CCMenuItemImage itemFromNormalImage:@"btn_se_off_normal.png"
                                                              selectedImage:@"btn_se_off_normal.png"];
        
        CCMenuItemToggle *menuItemForSE = [CCMenuItemToggle itemWithTarget:self
                                                                  selector:@selector(onSESelected:)
                                                                     items:menuItemForSEOn, menuItemForSEOff, nil];
        
        // 设置当前选中的项目
        if ([delegate.delegateLogic.appProfile se] == NO) {
            menuItemForSE.selectedIndex = 1;
        }
        
        CCMenu *menuForSE = [CCMenu menuWithItems:menuItemForSE, nil];
        menuForSE.position = ccp(winSize.width / 2 + 50, winSize.height / 2);
        [self addChild:menuForSE];
        
        
		// 设置允许点击
		self.isTouchEnabled = YES;
	}
	
	return self;
}


// 按下BGM开关
- (void) onBGMSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    CCMenuItemToggle *menuItemToggle = (CCMenuItemToggle *)sender;
    BOOL bgm = YES;
    
    // 检查选中的项目
    if (menuItemToggle.selectedIndex == 1) {
        bgm = NO;
    }
    
    // 更新BGM
    [delegate.delegateLogic updateBgm:bgm];
}


// 按下SE开关
- (void) onSESelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    CCMenuItemToggle *menuItemToggle = (CCMenuItemToggle *)sender;
    BOOL se = YES;
    
    // 检查选中的项目
    if (menuItemToggle.selectedIndex == 1) {
        se = NO;
    }
    
    // 更新SE
    [delegate.delegateLogic updateSe:se];
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


// ------------------- 标题场景 ---------------------
@implementation TitleScene

@synthesize weiboEngine = weiboEngine_;

+ (id) scene {
    TitleScene *titleScene = [TitleScene node];
    
    TitleBgLayer *titleBgLayer = [TitleBgLayer node];
    
    [titleScene addChild:titleBgLayer];
    
    return titleScene;
}


- (void) dealloc {
    self.weiboEngine = nil;
    [super dealloc];
}


// 显示选项
- (void) showOption {

    // 添加配置层
	TitleOptionLayer *optionLayer = [TitleOptionLayer node];
	[self addChild:optionLayer];
}


// 关闭选项
- (void) closeOption:(id)sender {
	
	// 清除设置层
    [sender removeFromParentAndCleanup:YES];
}


// 显示weibo分享
- (void) showShare {
    
    
    
//    // 显示weibo登陆
//    if (self.weiboEngine == nil) {
//        self.weiboEngine = [[[WBEngine alloc] initWithAppKey:WEIBO_APP_KEY
//                                                   appSecret:WEIBO_APP_SECRET] autorelease];
////        [self.weiboEngine setRootViewController:self];
//        [self.weiboEngine setDelegate:self];
//        [self.weiboEngine setRedirectURI:@"http://"];
//        [self.weiboEngine setIsUserExclusive:NO];
//    }
//
//    [self.weiboEngine logIn];
}


// 显示发送weibo画面
- (void) showWeiboSendView {
    WBSendView *sendView = [[[WBSendView alloc] initWithAppKey:WEIBO_APP_KEY
                                                    appSecret:WEIBO_APP_SECRET
                                                         text:@"test"
                                                        image:[UIImage imageNamed:@"share_1.jpg"]] autorelease];
    [sendView setDelegate:self];
    [sendView show:YES];    
}


#pragma mark - WBEngineDelegate Methods

// Log in successfully.
- (void)engineDidLogIn:(WBEngine *)engine {
    [self showWeiboSendView];
}


#pragma mark - WBSendViewDelegate Methods

- (void)sendViewDidFinishSending:(WBSendView *)view {
    [view hide:YES];
}


- (void)sendView:(WBSendView *)view didFailWithError:(NSError *)error {
    [view hide:YES];
    UIAlertView* alertView = [[UIAlertView alloc]initWithTitle:nil 
													   message:@"微博发送失败！" 
													  delegate:nil
											 cancelButtonTitle:@"确定" 
											 otherButtonTitles:nil];
	[alertView show];
	[alertView release];
}


@end
