//
//  LYProfile.m
//  AirBattle
//
//  Created by Leon on 11-10-27.
//  Copyright 2011 Leon Young. All rights reserved.
//

#import "LYProfile.h"


@implementation LYProfile

@synthesize profilePath = profilePath_;
@synthesize profile = profile_;


// 初始化存档文件
- (id) initWithFileName:(NSString *)fileName {
	if ((self = [super init])) {
		
		// 获取存档文件路径
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex:0];
		self.profilePath = [documentsDirectory stringByAppendingPathComponent:fileName];
		
		// 读取存档文件
		self.profile = [NSMutableDictionary dictionaryWithContentsOfFile:self.profilePath];
		
		// 如果存档不存在，初始化存档，并写入文件
		if (self.profile == nil) {
			
			// 创建存档文件
			self.profile = [NSMutableDictionary dictionary];
			
			// 写入存档
			[self save];
		}
	}
	
	return self;
}

// 保存存档
- (BOOL) save {
	BOOL rtn = YES;
	
	if ([self.profile writeToFile:self.profilePath atomically:YES] == NO) {
		rtn = NO;
		NSLog(@"write failed");
	}
	
	return rtn;
}


- (void) dealloc {
	self.profilePath = nil;
	self.profile = nil;
	[super dealloc];
}

@end
