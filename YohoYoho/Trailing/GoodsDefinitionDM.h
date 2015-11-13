//
//  GoodsDefinitionDM.h
//  YohoYoho
//
//  Created by  on 12-5-21.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GoodsDefinitionDM : NSObject {
    NSDictionary    *data_;            // 数据
}

@property (nonatomic, retain) NSDictionary  *data;

// 获取单条定义数据（条件：道具ID）
- (id) singleGoodsDefWithGoodsId:(int)goodsId;

@end
