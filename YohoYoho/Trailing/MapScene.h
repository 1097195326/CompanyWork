//
//  MapScene.h
//  YohoYoho
//
//  Created by Young Leon on 12-3-3.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "StageDefinitionDM.h"


// ----------------- 场景背景层 -------------------
@interface MapBgLayer : CCLayer {
    
}

@end


// ----------------- 场景菜单层 -------------------
@interface MapMenuLayer : CCLayer {

}


// 加载层内容，初始化变量
- (void) loadContentsOfLayer;


@end


// ------------------- 场景 ---------------------
@interface MapScene : CCScene {
    StageDefinitionDM   *stageDefinitionDM_;        // 关卡定义数据模型
}

@property (nonatomic, retain) StageDefinitionDM   *stageDefinitionDM;

+ (id) scene;

// 显示商店
- (void) showShop;

@end
