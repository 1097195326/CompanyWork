//
//  ShopScene.h
//  YohoYoho
//
//  Created by  on 12-5-21.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "cocos2d.h"
@class GoodsDefinitionDM;

// --------------------- 商店层 ------------------------
@interface ShopLayer : CCLayerColor {
    GoodsDefinitionDM   *goodsDefinitionDM_;
    CCLabelTTF          *labelForCoins_;                // 金钱余额
    CCSprite            *goodsBarBg_;                   // 道具栏背景
}

@property (nonatomic, retain) GoodsDefinitionDM     *goodsDefinitionDM;
@property (nonatomic, retain) CCLabelTTF            *labelForCoins;

// 买道具（扣钱、给道具）
- (void) buyGoodsWithGoodsId:(int)goodsId;

@end


// --------------------- 提示层（金钱不足，购买失败） ------------------------
@interface NoticeLayer : CCLayerColor {
    
}

@end


// --------------------- 商店道具描述层 ------------------------
@interface ShopGoodsDescriptionLayer : CCLayerColor

// 初始化方法
- (id) initWithGoodsId:(int)goodsId;

@end