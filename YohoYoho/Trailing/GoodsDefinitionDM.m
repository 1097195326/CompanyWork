//
//  GoodsDefinitionDM.m
//  YohoYoho
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "GoodsDefinitionDM.h"

@implementation GoodsDefinitionDM

@synthesize data = data_;


- (id) init {
    if (self = [super init]) {
        
        // 从定义文件获取数据
        NSString *path = [[NSBundle mainBundle] pathForResource:@"GoodsDefinition" ofType:@"plist"];
        self.data = [NSDictionary dictionaryWithContentsOfFile:path];
    }
    
    return self;
}


// 获取单条定义数据（条件：道具ID）
- (id) singleGoodsDefWithGoodsId:(int)goodsId {
    NSString *key = [NSString stringWithFormat:@"%i", goodsId];
    NSDictionary *singleDef = [self.data objectForKey:key];
    
    return singleDef;
}


- (void)dealloc {
    self.data = nil;
    [super dealloc];
}

@end