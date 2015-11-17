//
//  AppDelegate.h
//  Trailing
//
//  Created by  on 12-2-13.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DelegateLogic.h"
#import "libs/WxSdk/WXApi.h"


@class RootViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate, WXApiDelegate, UIAlertViewDelegate> {
	UIWindow			*window;
	RootViewController	*viewController;
    DelegateLogic       *delegateLogic_;
    enum WXScene _scene;
}

@property (nonatomic, retain) UIWindow      *window;
@property (nonatomic, retain) DelegateLogic *delegateLogic;

- (void) changeScene:(NSInteger)scene;
- (void) sendTextContent;
- (void) sendImageContent;
- (void) sendLinkContent;
- (void) sendMusicContent;
- (void) sendVideoContent;
- (void) sendAppContent;
- (void) sendNonGifContent;
- (void) sendGifContent;
- (void) sendFileContent;

@end
