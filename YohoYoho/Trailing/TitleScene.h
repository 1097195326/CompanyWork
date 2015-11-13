//
//  TitleScene.h
//  Trailing
//
//  Created by  on 12-2-14.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "WBEngine.h"
#import "WBSendView.h"


// ----------------- 标题场景背景层 -------------------
@interface TitleBgLayer : CCLayer {
    
}

@end


// --------------------- 标题选项层 ------------------------
@interface TitleOptionLayer : CCLayerColor

@end


// ------------------- 标题场景 ---------------------
@interface TitleScene : CCScene <WBEngineDelegate, WBSendViewDelegate> {
    WBEngine    *weiboEngine_;      // 新浪微博客户端类
}

@property (nonatomic, retain) WBEngine    *weiboEngine;

+ (id) scene;

// 显示选项
- (void) showOption;

// 关闭选项
- (void) closeOption:(id)sender;

// 显示weibo分享
- (void) showShare;

@end
