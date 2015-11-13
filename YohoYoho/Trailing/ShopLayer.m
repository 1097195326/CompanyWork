//
//  ShopScene.m
//  YohoYoho
//
//  Created by  on 12-5-21.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "ShopLayer.h"
#import "GoodsDefinitionDM.h"
#import "AppDelegate.h"
#import "AppProfile.h"


// --------------------- 商店层 ------------------------
@implementation ShopLayer

@synthesize goodsDefinitionDM = goodsDefinitionDM_;
@synthesize labelForCoins = labelForCoins_;

// 初始化方法
- (id) init {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        self.goodsDefinitionDM = [[[GoodsDefinitionDM alloc] init] autorelease];
        
        
        // 添加背景 ------------------------------------------------------------
        CCSprite *bg = [CCSprite spriteWithFile:@"shop_bg.png"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
        
        // 添加金钱余额 ------------------------------------------------------------
        // 金钱数额背景
        CCSprite *bgForCoins = [CCSprite spriteWithFile:@"coins_bg.png"];
        bgForCoins.position = ccp(940, 690);
        [self addChild:bgForCoins];
        
        // 金钱数量
        int coins = [delegate.delegateLogic.appProfile coins];
        NSString *coinsStr = [NSString stringWithFormat:@"%i", coins];
        self.labelForCoins = [CCLabelTTF labelWithString:coinsStr
                                                       fontName:@"impact"
                                                       fontSize:32];
        self.labelForCoins.position = ccp(bgForCoins.contentSize.width / 2, bgForCoins.contentSize.height / 2 - 20);
        self.labelForCoins.color = ccc3(71, 21, 18);
        [bgForCoins addChild:self.labelForCoins];
        
        
        // 添加道具按钮 ------------------------------------------------------------
        CCMenu *menuForGoods = [CCMenu menuWithItems: nil];
        for (int i = 1; i <= 12; i++) {
            NSString *fileName = [NSString stringWithFormat:@"goods_%i_big_normal.png", i];
            CCMenuItem *menuItem = nil;
            
            // 只保留前两个道具，剩余道具暂时不开放
            if (i <= 2) {
                menuItem = [CCMenuItemImage itemFromNormalImage:fileName
                                                  selectedImage:fileName
                                                         target:self
                                                       selector:@selector(onGoodsSelected:)];
                
                // 设置道具信息
                menuItem.userData = (NSDictionary *)[self.goodsDefinitionDM singleGoodsDefWithGoodsId:i];
                
                // 设置道具ID
                menuItem.tag = i;
                
                // 添加价格
                NSString *fileNameForPrice = [NSString stringWithFormat:@"goods_%i_price_normal.png", i];
                CCSprite *price = [CCSprite spriteWithFile:fileNameForPrice];
                price.anchorPoint = ccp(0.0f, 0.5f);
                price.position = ccp(20, 160);
                [menuItem addChild:price];
                
            } else {
                menuItem = [CCMenuItemImage itemFromNormalImage:fileName
                                                  selectedImage:fileName];
            }
            
            // 将菜单项放入菜单
            [menuForGoods addChild:menuItem];
        }
        
        // 将菜单放入场景
        [menuForGoods alignItemsInColumns:[NSNumber numberWithInt:4],
                                          [NSNumber numberWithInt:4],
                                          [NSNumber numberWithInt:4],
        nil];
        [self addChild:menuForGoods];
        
        
        // 添加道具栏 --------------------------------------------------
        [self showGoodsBar];
        
        
		// 设置允许点击
		self.isTouchEnabled = YES;
	}
	
	return self;
}


// 当道具被按下
- (void) onGoodsSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    CCMenuItem *menuItemForGoods = (CCMenuItem *)sender;
    NSDictionary *goodsInfo = menuItemForGoods.userData;
    int price = [[goodsInfo objectForKey:@"price"] intValue];              // 道具价格
    int coins = [delegate.delegateLogic.appProfile coins];                 // 用户金钱余额
    int goodsId = menuItemForGoods.tag;                                    // 道具ID
    
    // 验证金钱余额
    if (coins < price) {
        
        // 显示金钱不足
        NoticeLayer *noticeLayer = [NoticeLayer node];
        [self addChild:noticeLayer];
    } else {
        
        // 显示道具描述
        ShopGoodsDescriptionLayer *goodsDescriptionLayer = [[[ShopGoodsDescriptionLayer alloc] initWithGoodsId:goodsId] autorelease];
        [self addChild:goodsDescriptionLayer];
    }
}


// 买道具（扣钱、给道具）
- (void) buyGoodsWithGoodsId:(int)goodsId {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 扣钱 ----------------------------------------------------------------------------------------------
    NSDictionary *singleGoodsDef = [self.goodsDefinitionDM singleGoodsDefWithGoodsId:goodsId];
    int price = [[singleGoodsDef objectForKey:@"price"] intValue];
    [delegate.delegateLogic addCoins:-price justSave:YES];
    
    // 给道具
    [delegate.delegateLogic addGoodsWithGoodsId:goodsId amount:1];
    
    // 保存存档
    [delegate.delegateLogic.appProfile save];
    
    // 更新画面显示（金钱余额）
    int coins = [delegate.delegateLogic.appProfile coins];
    NSString *coinsStr = [NSString stringWithFormat:@"%i", coins];
    [self.labelForCoins setString:coinsStr];
    
    // 更新画面显示（道具栏）
    [self showGoodsBar];
}


// 显示道具栏
- (void) showGoodsBar {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    if (goodsBarBg_ != nil) {
        [goodsBarBg_ removeFromParentAndCleanup:YES];
    }
    
    // 添加道具栏背景
    goodsBarBg_ = [CCSprite spriteWithFile:@"goods_bar_bg.png"];
    goodsBarBg_.position = ccp(winSize.width / 2, 40);
    [self addChild:goodsBarBg_];
    
    // 添加道具
    NSDictionary *goods = [delegate.delegateLogic.appProfile goods];        // 用户道具信息
    CCMenu *menuForGoods = [CCMenu menuWithItems: nil];                     // 道具菜单
    NSArray *goodsKeys = [goods allKeys];
    for (int i = 0; i < 4; i++) {
        if (i + 1 <= [goodsKeys count]) {
            NSString *key = [goodsKeys objectAtIndex:i];
            int goodsId = [key intValue];
            NSString *goodsAmountStr = [[goods objectForKey:key] stringValue];          // 道具数量
            
            // 道具菜单项
            NSString *goodsFileName = [NSString stringWithFormat:@"goods_%i_small_normal.png", goodsId];
            CCMenuItem *menuItemForGoods = [CCMenuItemImage itemFromNormalImage:goodsFileName
                                                                  selectedImage:goodsFileName];
            
            // 将道具ID写入tag
//            menuItemForGoods.tag = goodsId;
            
            // 添加道具数量显示
            CCLabelTTF *labelForGoodsAmount = [CCLabelTTF labelWithString:goodsAmountStr
                                                                 fontName:@"impact"
                                                                 fontSize:32];
            labelForGoodsAmount.color = ccc3(71, 21, 18);
            labelForGoodsAmount.position = ccp(55, 25);
            labelForGoodsAmount.tag = 1;
            [menuItemForGoods addChild:labelForGoodsAmount];
            
            // 将菜单项加入菜单
            [menuForGoods addChild:menuItemForGoods];
            
        } else {
            
            // 添加空槽菜单项
            CCMenuItem *menuItemForGoods = [CCMenuItemImage itemFromNormalImage:@"goods_none_small_normal.png"
                                                                  selectedImage:@"goods_none_small_normal.png"];
            
            // 将菜单项加入菜单
            [menuForGoods addChild:menuItemForGoods];
        }
    }
    
    [menuForGoods alignItemsHorizontally];
    menuForGoods.position = ccp(goodsBarBg_.contentSize.width / 2, 50);
    [goodsBarBg_ addChild:menuForGoods];
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


- (void) dealloc {
    self.goodsDefinitionDM = nil;
    self.labelForCoins = nil;
    [super dealloc];
}


@end



// --------------------- 提示层（金钱不足，购买失败） ------------------------
@implementation NoticeLayer


- (id) init {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        
        // 添加金钱不足提示框
        CCSprite *notice = [CCSprite spriteWithFile:@"notice_coins_not_enough.png"];
        notice.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:notice];
        
        
        // 添加关闭按钮
		CCMenuItem *menuItemForClose = [CCMenuItemImage itemFromNormalImage:@"btn_close_for_notice_normal.png"
                                                              selectedImage:@"btn_close_for_notice_normal.png"
                                                                      block:^(id sender) {
                                                                          [self removeFromParentAndCleanup:YES];
                                                                      }];
		CCMenu *menu = [CCMenu menuWithItems:menuItemForClose, nil];
        menu.position = ccpAdd(notice.position, ccp(130, 70));
		[self addChild:menu];
        
        
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
	return YES;
}

@end


// --------------------- 商店道具描述层 ------------------------
@implementation ShopGoodsDescriptionLayer

// 初始化方法
- (id) initWithGoodsId:(int)goodsId {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        CGSize winSize = [[CCDirector sharedDirector] winSize];
//        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        
        
        // 添加描述
        NSString *fileName = [NSString stringWithFormat:@"goods_%i_description.png", goodsId];
        CCSprite *description = [CCSprite spriteWithFile:fileName];
        description.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:description];
		
        
        // 添加购买按钮
        CCMenuItem *menuItemForBuy = [CCMenuItemImage itemFromNormalImage:@"btn_buy_normal.png"
                                                              selectedImage:@"btn_buy_normal.png"
                                                                      block:^(id sender) {
                                                                          
                                                                          // 扣钱、给道具
                                                                          [(ShopLayer *)[self parent] buyGoodsWithGoodsId:goodsId];
                                                                          
                                                                          // 清除描述层
                                                                          [self removeFromParentAndCleanup:YES];
                                                                      }];
        CCMenu *menu = [CCMenu menuWithItems:menuItemForBuy, nil];
        menu.position = ccp(description.contentSize.width - 80, 45);
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