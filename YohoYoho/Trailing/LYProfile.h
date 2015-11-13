//
//  LYProfile.h
//  AirBattle
//
//  Created by Leon on 11-10-27.
//  Copyright 2011 Leon Young. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface LYProfile : NSObject {
	NSString			*profilePath_;		// 存档路径
	NSMutableDictionary *profile_;			// 存档文件
}

@property (nonatomic, retain) NSString				*profilePath;
@property (nonatomic, retain) NSMutableDictionary	*profile;


// 初始化存档文件
- (id) initWithFileName:(NSString *)fileName;

// 保存存档
- (BOOL) save;

// 获取文件路径
//+ (NSString *) profilePath:(NSString *)fileName;

@end
