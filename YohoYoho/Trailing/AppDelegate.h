//
//  AppDelegate.h
//  Trailing
//
//  Created by  on 12-2-13.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DelegateLogic.h"

@class RootViewController;

@interface AppDelegate : NSObject <UIApplicationDelegate> {
	UIWindow			*window;
	RootViewController	*viewController;
    DelegateLogic       *delegateLogic_;
}

@property (nonatomic, retain) UIWindow      *window;
@property (nonatomic, retain) DelegateLogic *delegateLogic;

@end
