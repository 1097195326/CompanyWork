//
//  GameStageScene.m
//  YohoYoho
//
//  Created by  on 12-3-10.
//  Copyright 2012年 Leon.Young. All rights reserved.
//

#import "GameStageScene.h"
#import "GameConfig.h"
#import "AppDelegate.h"
#import "AppProfile.h"
#import "DoctorActionProbabilityDefinitionDM.h"
#import "HelpLayer.h"
#import "CoverLayer.h"


// 层的Tag Id
enum E_TAG_ID{
    E_TAG_ID_ATTACK_LAYER = 1000,
	E_TAG_ID_PAUSE_LAYER = 1001,
    E_TAG_ID_CONFIG_LAYER = 1002,
    E_TAG_ID_PLAY_LAYER = 1003,
    E_TAG_ID_COVER_LAYER = 1004,
};


// 层的Z坐标
enum E_Z_ORDER{
    E_Z_ORDER_BG_LAYER,
    E_Z_ORDER_PLAY_LAYER,
    E_Z_ORDER_ATTACK_LAYER,
    E_Z_ORDER_MENU_LAYER,

    E_Z_ORDER_RESULT_LAYER,
    
    E_Z_ORDER_CONFIG_LAYER,
    E_Z_ORDER_HELP_LAYER,
    E_Z_ORDER_PAUSE_LAYER,
};


// action tag Id
enum E_ACTION_TAG_ID{
    E_ACTION_TAG_ID_SLIDE_ON_PLAY_LAYER = 101,
};


// 游戏结束方式
enum E_GAME_OVER_ID{
    E_GAME_OVER_ID_WIN,                 // 胜利
    E_GAME_OVER_ID_LOSE,                // 失败
    E_GAME_OVER_ID_LOSE_BY_FOUND,       // 失败（被发现）
};


// ----------------- 场景背景层 -------------------
@implementation GameStageBgLayer

@synthesize doctor = doctor_;
@synthesize leftWalls = leftWalls_;
@synthesize rightWalls = rightWalls_;
@synthesize leftFloorGoods = leftFloorGoods_;
@synthesize rightFloorGoods = rightFloorGoods_;
@synthesize middleCeilGoods = middleCeilGoods_;
@synthesize leftCeilGoods = leftCeilGoods_;
@synthesize rightCeilGoods = rightCeilGoods_;
@synthesize goalPoint = goalPoint_;
@synthesize wallMovePointRatio = wallMovePointRatio_;
@synthesize floorGoodsMovePointRatio = floorGoodsMovePointRatio_;
@synthesize middleCeilGoodsMovePointRatio = middleCeilGoodsMovePointRatio_;
@synthesize ceilGoodsMovePointRatio = ceilGoodsMovePointRatio_;
@synthesize movedDistance = movedDistance_;
@synthesize totalMoveDistance = totalMoveDistance_;


// 加载层内容，初始化变量
- (void) loadContentsOfLayer {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    int stage = delegate.delegateLogic.stage;                               // 关卡
    int yOffsetFactor = 80;                                                // 用于计算Y坐标位移的计算因子
    self.leftWalls = [NSMutableArray arrayWithCapacity:WALL_COUNT];
    self.rightWalls = [NSMutableArray arrayWithCapacity:WALL_COUNT];
    self.leftFloorGoods = [NSMutableArray array];
    self.rightFloorGoods = [NSMutableArray array];
    self.middleCeilGoods = [NSMutableArray arrayWithCapacity:WALL_COUNT];
    self.leftCeilGoods = [NSMutableArray array];
    self.rightCeilGoods = [NSMutableArray array];
    self.movedDistance = 0.0f;
    self.totalMoveDistance = 0.0f;
    self.goalPoint = ccp(winSize.width / 2, winSize.height / 2 + 140);
    self.wallMovePointRatio = ccp(1.5f * 261, yOffsetFactor);
    self.floorGoodsMovePointRatio = ccp(1.5f * 261 * 2, (yOffsetFactor + 450) * 2);
    self.middleCeilGoodsMovePointRatio = ccp(0, yOffsetFactor + 250);
    self.ceilGoodsMovePointRatio = ccp(1.5f * 261 * 2, (yOffsetFactor + 250) * 2);
    
    // 获取关卡定义数据
    NSDictionary *singleStageDef = [((GameStageScene *)[self parent]).stageDefinitionDM singleStageDefWithStage:stage];
    
    
    // 添加天花板和地面
    CCSprite *ceilAndFloor = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"ceilAndFloorImage"]];
    ceilAndFloor.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:ceilAndFloor z:1];
    
    
    // 添加墙壁 --------------------------------------------------------------------
    // 添加左侧墙壁
    NSArray *leftWallImage = [singleStageDef objectForKey:@"leftWallImage"];             // 左侧墙壁文件名数组
    CGPoint prePosition = self.goalPoint;                                                // 前一面墙的坐标
    int indexForLeftWallImage = 0;                                                       // 下标
    for (int i = 1; i <= WALL_COUNT; i++) {
        NSString *wallSpriteFileName = [leftWallImage objectAtIndex:indexForLeftWallImage];
        CCSprite *wall = [CCSprite spriteWithFile:wallSpriteFileName];
        wall.scale = 0.02f * powf(2.0f, (float)(i - 1));
//        int xOffset = -(wall.contentSize.width / 2) * wall.scale * 1.5f;
//        int yOffset = -wall.scale * yOffsetFactor;
        
        // 第一面墙位于视觉尽头点
        int xOffset = 0;
        int yOffset = 0;
        if (i != 1) {
            xOffset = -self.wallMovePointRatio.x * (wall.scale / 2.0f);
            yOffset = -self.wallMovePointRatio.y * (wall.scale / 2.0f);
        }
        wall.position = ccpAdd(prePosition, ccp(xOffset, yOffset));
        prePosition = wall.position;
        
        // 放入场景
        [self addChild:wall z:0];
        
        // 放入数组
        [self.leftWalls addObject:wall];
        
        // 设置墙壁图像下标
        if (indexForLeftWallImage + 1 >= [leftWallImage count]) {
            indexForLeftWallImage = 0;
        } else {
            indexForLeftWallImage++;
        }
    }
    
    // 添加右侧墙壁
    NSArray *rightWallImage = [singleStageDef objectForKey:@"rightWallImage"];             // 右侧墙壁文件名数组
    CGPoint prePositionForRightWall = self.goalPoint;                                      // 前一面墙的坐标
    int indexForRightWallImage = 0;                                                        // 下标
    for (int i = 1; i <= WALL_COUNT; i++) {
        NSString *wallSpriteFileName = [rightWallImage objectAtIndex:indexForRightWallImage];
        CCSprite *wall = [CCSprite spriteWithFile:wallSpriteFileName];
        wall.scale = 0.02f * powf(2.0f, (float)(i - 1));
//        int xOffset = (wall.contentSize.width / 2) * wall.scale * 1.5f;
//        int yOffset = -wall.scale * yOffsetFactor;
        
        // 第一面墙位于视觉尽头点
        int xOffset = 0;
        int yOffset = 0;
        if (i != 1) {
            xOffset = self.wallMovePointRatio.x * (wall.scale / 2.0f);
            yOffset = -self.wallMovePointRatio.y * (wall.scale / 2.0f);
        }
        wall.position = ccpAdd(prePositionForRightWall, ccp(xOffset, yOffset));
        prePositionForRightWall = wall.position;
        
        // 放入场景
        [self addChild:wall z:0];
        
        // 放入数组
        [self.rightWalls addObject:wall];
        
        // 设置墙壁图像下标
        if (indexForRightWallImage + 1 >= [rightWallImage count]) {
            indexForRightWallImage = 0;
        } else {
            indexForRightWallImage++;
        }
    }
    
    
    // 添加地面道具 --------------------------------------------------------------------
    // 添加左侧地面道具
    NSArray *floorLeftGoodsImage = [singleStageDef objectForKey:@"floorLeftGoods"];      // 左侧地面道具文件名数组
    CGPoint nextPosition = self.goalPoint;                                               // 下一个位置的坐标
    float nextScale = 0.01f;
    if ([floorLeftGoodsImage count] > 0) {
        while (nextPosition.y > 0) {
            
            // 1 / 3 的概率出现道具
            if (arc4random() % FLOOR_GOODS_ADD_PROBABILITY == 0) {
                int index = arc4random() % [floorLeftGoodsImage count];
                NSString *fileName = [floorLeftGoodsImage objectAtIndex:index];
                CCSprite *floorGoods = [CCSprite spriteWithFile:fileName];
                floorGoods.scale = nextScale;
                floorGoods.position = nextPosition;
                
                // 放入场景
                [self addChild:floorGoods z:2];
                
                // 放入数组
                [self.leftFloorGoods addObject:floorGoods];
            }
            
            int nextPositionX = nextPosition.x - self.floorGoodsMovePointRatio.x * nextScale;
            int nextPositionY = nextPosition.y - self.floorGoodsMovePointRatio.y * nextScale;
            nextPosition = ccp(nextPositionX, nextPositionY);
            
            nextScale = nextScale * 2.0f;
        }
    }

    // 添加右侧地面道具
    NSArray *floorRightGoodsImage = [singleStageDef objectForKey:@"floorRightGoods"];      // 右侧地面道具文件名数组
    nextPosition = self.goalPoint;                                                         // 下一个位置的坐标
    nextScale = 0.01f;
    if ([floorRightGoodsImage count] > 0) {
        while (nextPosition.y > 0) {
            
            // 1 / 3 的概率出现道具
            if (arc4random() % FLOOR_GOODS_ADD_PROBABILITY == 0) {
                int index = arc4random() % [floorRightGoodsImage count];
                NSString *fileName = [floorRightGoodsImage objectAtIndex:index];
                CCSprite *floorGoods = [CCSprite spriteWithFile:fileName];
                floorGoods.scale = nextScale;
                floorGoods.position = nextPosition;
                
                // 放入场景
                [self addChild:floorGoods z:2];
                
                // 放入数组
                [self.rightFloorGoods addObject:floorGoods];
            }
            
            int nextPositionX = nextPosition.x + self.floorGoodsMovePointRatio.x * nextScale;
            int nextPositionY = nextPosition.y - self.floorGoodsMovePointRatio.y * nextScale;
            nextPosition = ccp(nextPositionX, nextPositionY);
            
            nextScale = nextScale * 2.0f;
        }
    }
    
    
    // 添加天花板道具 --------------------------------------------------------------------
/*    // 添加天花板中间道具
    NSArray *ceilMiddleGoodsImage = [singleStageDef objectForKey:@"ceilMiddleGoods"];    // 天花板中间道具文件名数组
    prePosition = self.goalPoint;                                                        // 前一个道具的坐标
    int indexForCeilMiddleGoodsImage = 0;                                                // 下标
    for (int i = 1; i <= WALL_COUNT; i++) {
        NSString *spriteFileName = [ceilMiddleGoodsImage objectAtIndex:indexForCeilMiddleGoodsImage];
        CCSprite *goods = [CCSprite spriteWithFile:spriteFileName];
        goods.scale = 0.01f * powf(2.0f, (float)(i - 1));
        
        // 第一面墙位于视觉尽头点
        int xOffset = 0;
        int yOffset = 0;
        if (i != 1) {
            xOffset = self.middleCeilGoodsMovePointRatio.x * (goods.scale / 2.0f);
            yOffset = self.middleCeilGoodsMovePointRatio.y * (goods.scale / 2.0f);
        }
        goods.position = ccpAdd(prePosition, ccp(xOffset, yOffset));
        prePosition = goods.position;
        
        // 放入场景
        [self addChild:goods z:2];
        
        // 放入数组
        [self.middleCeilGoods addObject:goods];
        
        // 设置墙壁图像下标
        if (indexForCeilMiddleGoodsImage + 1 >= [ceilMiddleGoodsImage count]) {
            indexForCeilMiddleGoodsImage = 0;
        } else {
            indexForCeilMiddleGoodsImage++;
        }
    }*/
    
    // 添加左侧天花板道具
    NSArray *ceilLeftGoodsImage = [singleStageDef objectForKey:@"ceilLeftGoods"];      // 左侧天花板道具文件名数组
    nextPosition = self.goalPoint;                                                     // 下一个位置的坐标
    nextScale = 0.01f;
    if ([ceilLeftGoodsImage count] > 0) {
        while (nextPosition.y < winSize.height) {
            
            // 1 / 3 的概率出现道具
            if (arc4random() % CEIL_GOODS_ADD_PROBABILITY == 0) {
                int index = arc4random() % [ceilLeftGoodsImage count];
                NSString *fileName = [ceilLeftGoodsImage objectAtIndex:index];
                CCSprite *goods = [CCSprite spriteWithFile:fileName];
                goods.scale = nextScale;
                goods.position = nextPosition;
                
                // 放入场景
                [self addChild:goods z:2];
                
                // 放入数组
                [self.leftCeilGoods addObject:goods];
            }
            
            int nextPositionX = nextPosition.x - self.ceilGoodsMovePointRatio.x * nextScale;
            int nextPositionY = nextPosition.y + self.ceilGoodsMovePointRatio.y * nextScale;
            nextPosition = ccp(nextPositionX, nextPositionY);
            
            nextScale = nextScale * 2.0f;
        }
    }
    
    // 添加右侧天花板道具
    NSArray *ceilRightGoodsImage = [singleStageDef objectForKey:@"ceilRightGoods"];      // 右侧天花板道具文件名数组
    nextPosition = self.goalPoint;                                                       // 下一个位置的坐标
    nextScale = 0.01f;
    if ([ceilRightGoodsImage count] > 0) {
        while (nextPosition.y < winSize.height) {
            
            // 1 / 3 的概率出现道具
            if (arc4random() % CEIL_GOODS_ADD_PROBABILITY == 0) {
                int index = arc4random() % [ceilRightGoodsImage count];
                NSString *fileName = [ceilRightGoodsImage objectAtIndex:index];
                CCSprite *goods = [CCSprite spriteWithFile:fileName];
                goods.scale = nextScale;
                goods.position = nextPosition;
                
                // 放入场景
                [self addChild:goods z:2];
                
                // 放入数组
                [self.rightCeilGoods addObject:goods];
            }
            
            int nextPositionX = nextPosition.x + self.ceilGoodsMovePointRatio.x * nextScale;
            int nextPositionY = nextPosition.y + self.ceilGoodsMovePointRatio.y * nextScale;
            nextPosition = ccp(nextPositionX, nextPositionY);
            
            nextScale = nextScale * 2.0f;
        }
    }
    
    
    // 添加走廊尽头的光 --------------------------------------------------------------
    CCSprite *spriteForGoal = [CCSprite spriteWithFile:[singleStageDef objectForKey:@"goalImage"]];
    spriteForGoal.position = ccpAdd(self.goalPoint, ccp(0, -15));
    [self addChild:spriteForGoal z:3];
    
    
    // 添加医生 ---------------------------------------------------------------------
    int doctorId = [[singleStageDef objectForKey:@"doctorId"] intValue];
    self.doctor = [[[Doctor alloc] initWithDoctorId:doctorId] autorelease];
    [self setDoctorPositionWithDistance:DISTANCE_INIT];
    [self addChild:self.doctor.doctorSpriteBatchNode z:4];
    
    //test
//    [self schedule:@selector(doctorAction) interval:5.0f];
}


// 设置医生的位置和缩放，使用地面道具的移动比率
- (void) setDoctorPositionWithDistance:(float)distance {
    
    // 医生距离走廊尽头的距离
    float distanceFromDoctorToGoal = DISTANCE_MAX - distance;
    
    // 将距离换算成移动像素（X轴）
    float movePointDistanceX = [self floorGoodsMovePointWithDistance:distanceFromDoctorToGoal];
    
    // 计算Y坐标上的移动像素
    float movePointDistanceY = movePointDistanceX * self.floorGoodsMovePointRatio.y / self.floorGoodsMovePointRatio.x;

    // 新的缩放比例
//    float scale = (movePointDistanceX / self.floorGoodsMovePointRatio.x + 1.0f) * 0.01f;
    float scale = powf(2.0f, movePointDistanceX / self.floorGoodsMovePointRatio.x) * 0.01f;

    CGPoint newPosition = ccpAdd(self.goalPoint, ccp(0, -movePointDistanceY * scale / 2));
    self.doctor.doctorSpriteBatchNode.position = newPosition;
    
    float newScale = powf(2.0f, movePointDistanceX / self.floorGoodsMovePointRatio.x * 1.60f) * 0.01f;
    self.doctor.doctorSpriteBatchNode.scale = newScale;
}


// 向前移动（景物后退）
- (void) goForwardWithDistance:(float)distance {
    
    // 添加屏幕跳动
    [self screenJumpWithDistance:distance];
    
    
    [self wallGoBackwardWithDistance:distance];

    [self floorGoodsGoBackwardWithDistance:distance];
//    [self ceilMiddleGoodsGoBackwardWithDistance:distance duration:duration];
    [self ceilGoodsGoBackwardWithDistance:distance];

    // 累计移动距离
    self.movedDistance += distance;
    
    // 移动一定距离后，检查添加地面和天花板道具
    if (self.movedDistance >= 500.0f) {
        self.movedDistance = 0.0f;
        
        // 检查地面道具，删除画面外的，添加新的
        [self checkLeftFloorGoods];
        [self checkRightFloorGoods];
        
        // 检查地面道具，删除画面外的，添加新的
        [self checkLeftCeilGoods];
        [self checkRightCeilGoods];
    }
}


// 屏幕跳动
- (void) screenJumpWithDistance:(float)distance {
//    id actJump = [CCJumpBy actionWithDuration:duration position:ccp(0, 0) height:-5 jumps:1];
//    [self runAction:actJump];
    
    int jumpHeight = 5;                         // 颠簸的最大高度
    int distancePerJumpHeight = 15;             // 每颠簸一个点对应的移动距离
    self.totalMoveDistance += distance;
    int height = (int)(self.totalMoveDistance / distancePerJumpHeight) % (jumpHeight * 2);        // 用于计算的高度
    
    // 如果大于跳跃高度，则处于落下范围
    float offsetY = 0.0f;
    if (height > jumpHeight) {
        offsetY = jumpHeight - (height - jumpHeight);
    } else {
        offsetY = height;
    }
    
    // 设置高度
    self.position = ccp(0, -offsetY);
}


// 墙壁后退
- (void) wallGoBackwardWithDistance:(float)distance {
    
    // 检查替换墙壁（离开屏幕的，重新排队）
    [self resetLeftWall];
    [self resetRightWall];
    
    
    // 将距离换算成移动像素（X轴）
    float movePointDistanceX = [self wallMovePointWithDistance:distance];
    
    // 计算Y坐标上的移动像素
    float movePointDistanceY = movePointDistanceX * self.wallMovePointRatio.y / self.wallMovePointRatio.x;

    
    // 设置左侧墙壁位置
    for (CCSprite *wall in self.leftWalls) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.wallMovePointRatio.x + 1.0f) * wall.scale;
        wall.position = ccpAdd(wall.position, ccp(-movePointDistanceX * wall.scale, -movePointDistanceY * wall.scale));
        wall.scale = scale;
    }
    
    // 设置右侧墙壁位置
    for (CCSprite *wall in self.rightWalls) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.wallMovePointRatio.x + 1.0f) * wall.scale;
        wall.position = ccpAdd(wall.position, ccp(movePointDistanceX * wall.scale, -movePointDistanceY * wall.scale));
        wall.scale = scale;
    }
    
/*
    
    // 为左侧墙壁添加运动
    for (CCSprite *wall in self.leftWalls) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.wallMovePointRatio.x + 1.0f) * wall.scale;
        id actScaleForWall = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMoveForWall = [CCMoveBy actionWithDuration:duration position:ccp(-movePointDistanceX * wall.scale, -movePointDistanceY * wall.scale)];
        id actSpawnForWall = [CCSpawn actions:actScaleForWall, actMoveForWall, nil];
        [wall runAction:actSpawnForWall];
    }

    // 为右侧墙壁添加运动
    for (CCSprite *wall in self.rightWalls) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.wallMovePointRatio.x + 1.0f) * wall.scale;
        id actScaleForWall = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMoveForWall = [CCMoveBy actionWithDuration:duration position:ccp(movePointDistanceX * wall.scale, -movePointDistanceY * wall.scale)];
        id actSpawnForWall = [CCSpawn actions:actScaleForWall, actMoveForWall, nil];
        [wall runAction:actSpawnForWall];
    }
 */
}


// 地面道具后退
- (void) floorGoodsGoBackwardWithDistance:(float)distance {
    
    // 将距离换算成移动像素（X轴）
    float movePointDistanceX = [self floorGoodsMovePointWithDistance:distance];
    
    // 计算Y坐标上的移动像素
    float movePointDistanceY = movePointDistanceX * self.floorGoodsMovePointRatio.y / self.floorGoodsMovePointRatio.x;
    
    // 设置左侧地面道具位置
    for (CCSprite *floorGoods in self.leftFloorGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.floorGoodsMovePointRatio.x + 1.0f) * floorGoods.scale;
        floorGoods.position = ccpAdd(floorGoods.position, ccp(-movePointDistanceX * floorGoods.scale, -movePointDistanceY * floorGoods.scale));
        floorGoods.scale = scale;
    }
    
    // 设置右侧地面道具位置
    for (CCSprite *floorGoods in self.rightFloorGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.floorGoodsMovePointRatio.x + 1.0f) * floorGoods.scale;
        floorGoods.position = ccpAdd(floorGoods.position, ccp(movePointDistanceX * floorGoods.scale, -movePointDistanceY * floorGoods.scale));
        floorGoods.scale = scale;
    }
/*
    // 为左侧地面道具添加运动
    for (CCSprite *floorGoods in self.leftFloorGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.floorGoodsMovePointRatio.x + 1.0f) * floorGoods.scale;
        id actScale = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMove = [CCMoveBy actionWithDuration:duration position:ccp(-movePointDistanceX * floorGoods.scale, -movePointDistanceY * floorGoods.scale)];
        id actSpawn = [CCSpawn actions:actScale, actMove, nil];
        [floorGoods runAction:actSpawn];
    }
    
    // 为右侧地面道具添加运动
    for (CCSprite *floorGoods in self.rightFloorGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.floorGoodsMovePointRatio.x + 1.0f) * floorGoods.scale;
        id actScale = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMove = [CCMoveBy actionWithDuration:duration position:ccp(movePointDistanceX * floorGoods.scale, -movePointDistanceY * floorGoods.scale)];
        id actSpawn = [CCSpawn actions:actScale, actMove, nil];
        [floorGoods runAction:actSpawn];
    }*/
}


// 天花板道具后退
- (void) ceilGoodsGoBackwardWithDistance:(float)distance {
    
    // 将距离换算成移动像素（X轴）
    float movePointDistanceX = [self ceilGoodsMovePointXWithDistance:distance];
    
    // 计算Y坐标上的移动像素
    float movePointDistanceY = movePointDistanceX * self.ceilGoodsMovePointRatio.y / self.ceilGoodsMovePointRatio.x;
    
    // 设置左侧地面道具位置
    for (CCSprite *goods in self.leftCeilGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.ceilGoodsMovePointRatio.x + 1.0f) * goods.scale;
        goods.position = ccpAdd(goods.position, ccp(-movePointDistanceX * goods.scale, movePointDistanceY * goods.scale));
        goods.scale = scale;
    }
    
    // 设置右侧地面道具位置
    for (CCSprite *goods in self.rightCeilGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.ceilGoodsMovePointRatio.x + 1.0f) * goods.scale;
        goods.position = ccpAdd(goods.position, ccp(movePointDistanceX * goods.scale, movePointDistanceY * goods.scale));
        goods.scale = scale;
    }
/*
    // 为左侧地面道具添加运动
    for (CCSprite *goods in self.leftCeilGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.ceilGoodsMovePointRatio.x + 1.0f) * goods.scale;
        id actScale = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMove = [CCMoveBy actionWithDuration:duration position:ccp(-movePointDistanceX * goods.scale, movePointDistanceY * goods.scale)];
        id actSpawn = [CCSpawn actions:actScale, actMove, nil];
        [goods runAction:actSpawn];
    }

    // 为右侧地面道具添加运动
    for (CCSprite *goods in self.rightCeilGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceX / self.ceilGoodsMovePointRatio.x + 1.0f) * goods.scale;
        id actScale = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMove = [CCMoveBy actionWithDuration:duration position:ccp(movePointDistanceX * goods.scale, movePointDistanceY * goods.scale)];
        id actSpawn = [CCSpawn actions:actScale, actMove, nil];
        [goods runAction:actSpawn];
    }*/
}


// 天花板中间道具后退
- (void) ceilMiddleGoodsGoBackwardWithDistance:(int)distance
                                      duration:(float)duration{
    
    // 检查替换天花板中间道具（离开屏幕的，重新排队）
    [self resetCeilMiddleGoods];
    
    
    // 将距离换算成移动像素（X轴）
    float movePointDistanceX = 0.0f;
    
    // 计算Y坐标上的移动像素
    float movePointDistanceY = [self ceilGoodsMovePointYWithDistance:distance];
    
    // 为天花板中间道具添加运动
    for (CCSprite *goods in self.middleCeilGoods) {
        
        // 新的缩放比例
        float scale = (movePointDistanceY / self.middleCeilGoodsMovePointRatio.y + 1.0f) * goods.scale;
        id actScale = [CCScaleTo actionWithDuration:duration scale:scale];
        id actMove = [CCMoveBy actionWithDuration:duration position:ccp(movePointDistanceX * goods.scale, movePointDistanceY * goods.scale)];
        id actSpawn = [CCSpawn actions:actScale, actMove, nil];
        [goods runAction:actSpawn];
    }
}


// 将移动距离转换为墙壁的X轴像素移动距离
- (float) wallMovePointWithDistance:(float)distance {
    return distance * WALL_MOVE_POINT_X_PER_DISTANCE;
}


// 将移动距离转换为地面道具的X轴像素移动距离
- (float) floorGoodsMovePointWithDistance:(float)distance {
    float wallMovePoint = [self wallMovePointWithDistance:distance];
    float floorGoodsMovePoint = self.floorGoodsMovePointRatio.x / self.wallMovePointRatio.x * wallMovePoint;
    return floorGoodsMovePoint;
}


// 将移动距离转换为天花板中间道具的Y轴像素移动距离
- (float) ceilGoodsMovePointYWithDistance:(float)distance {
    float wallMovePointX = [self wallMovePointWithDistance:distance];
//    float wallMovePointY = wallMovePointX * self.wallMovePointRatio.y / self.wallMovePointRatio.x;
//    float ceilGoodsMovePointY = self.middleCeilGoodsMovePointRatio.y / self.wallMovePointRatio.y * wallMovePointY;
    float ceilGoodsMovePointY = self.middleCeilGoodsMovePointRatio.y / self.wallMovePointRatio.x * wallMovePointX;
    return ceilGoodsMovePointY;
}


// 将移动距离转换为天花板道具的X轴像素移动距离
- (float) ceilGoodsMovePointXWithDistance:(float)distance {
    float wallMovePointX = [self wallMovePointWithDistance:distance];
    float ceilGoodsMovePointX = self.ceilGoodsMovePointRatio.x / self.wallMovePointRatio.x * wallMovePointX;
    return ceilGoodsMovePointX;
}


// 检查替换左侧墙壁（离开屏幕的，重新排队）
- (void) resetLeftWall {
    CCSprite *lastWall = [self.leftWalls objectAtIndex:(WALL_COUNT - 1)];
    if (lastWall.position.x < -lastWall.contentSize.width * lastWall.scale / 2) {
        
        // 删除最后一面墙
        [self.leftWalls removeLastObject];
        
        // 设置最后一面墙的位置和缩放比例
        CCSprite *firstWall = [self.leftWalls objectAtIndex:0];
        lastWall.scale = firstWall.scale / 2.0f;
        lastWall.position = ccpAdd(firstWall.position, ccp(self.wallMovePointRatio.x * lastWall.scale, self.wallMovePointRatio.y * lastWall.scale));
        
        // 插入第一个位置
        [self.leftWalls insertObject:lastWall atIndex:0];
    }
}


// 检查替换右侧墙壁（离开屏幕的，重新排队）
- (void) resetRightWall {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    CCSprite *lastWall = [self.rightWalls objectAtIndex:(WALL_COUNT - 1)];
    if (lastWall.position.x > winSize.width + lastWall.contentSize.width * lastWall.scale / 2) {
        
        // 删除最后一面墙
        [self.rightWalls removeLastObject];
        
        // 设置最后一面墙的位置和缩放比例
        CCSprite *firstWall = [self.rightWalls objectAtIndex:0];
        lastWall.scale = firstWall.scale / 2.0f;
        lastWall.position = ccpAdd(firstWall.position, ccp(-self.wallMovePointRatio.x * lastWall.scale, self.wallMovePointRatio.y * lastWall.scale));
        
        // 插入第一个位置
        [self.rightWalls insertObject:lastWall atIndex:0];
    }
}


// 检查替换天花板中间道具（离开屏幕的，重新排队）
- (void) resetCeilMiddleGoods {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    CCSprite *lastCeilMiddleGoods = [self.middleCeilGoods objectAtIndex:(WALL_COUNT - 1)];
    if (lastCeilMiddleGoods.position.y > winSize.height + lastCeilMiddleGoods.contentSize.height / 2) {
        
        // 删除最后一面墙
        [self.middleCeilGoods removeLastObject];
        
        // 设置最后一面墙的位置和缩放比例
        CCSprite *firstCeilMiddleGoods = [self.middleCeilGoods objectAtIndex:0];
        lastCeilMiddleGoods.scale = firstCeilMiddleGoods.scale / 2.0f;
        lastCeilMiddleGoods.position = ccpAdd(firstCeilMiddleGoods.position, ccp(self.middleCeilGoodsMovePointRatio.x * lastCeilMiddleGoods.scale, self.middleCeilGoodsMovePointRatio.y * lastCeilMiddleGoods.scale));
        
        // 插入第一个位置
        [self.middleCeilGoods insertObject:lastCeilMiddleGoods atIndex:0];
    }
}


// 检查替换左地面道具（离开屏幕的，删除，随即插入新的地面道具）
- (void) checkLeftFloorGoods {
    CCSprite *lastFloorGoods = [self.leftFloorGoods lastObject];
    if (lastFloorGoods != nil && lastFloorGoods.position.y < -lastFloorGoods.contentSize.height / 2) {
        
        // 删除最后一个地面道具
        [self.leftFloorGoods removeLastObject];
        
        // 从画面上移除
        [self removeChild:lastFloorGoods cleanup:YES];
    }
    
    // 随机添加新的道具
    if (arc4random() % FLOOR_GOODS_ADD_PROBABILITY == 0) {
        [self addNewFloorGoodsToSide:SIDE_LEFT];
    }
}


// 检查替换右地面道具（离开屏幕的，删除，随即插入新的地面道具）
- (void) checkRightFloorGoods {
    CCSprite *lastFloorGoods = [self.rightFloorGoods lastObject];
    if (lastFloorGoods != nil && lastFloorGoods.position.y < -lastFloorGoods.contentSize.height / 2) {
        
        // 删除最后一个地面道具
        [self.rightFloorGoods removeLastObject];
        
        // 从画面上移除
        [self removeChild:lastFloorGoods cleanup:YES];
    }
    
    // 随机添加新的道具
    if (arc4random() % FLOOR_GOODS_ADD_PROBABILITY == 0) {
        [self addNewFloorGoodsToSide:SIDE_RIGHT];
    }
}


// 检查替换左天花板道具（离开屏幕的，删除，随即插入新的地面道具）
- (void) checkLeftCeilGoods {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    CCSprite *lastGoods = [self.leftCeilGoods lastObject];
    if (lastGoods != nil && lastGoods.position.y > winSize.height + lastGoods.contentSize.height / 2) {
        
        // 删除最后一个地面道具
        [self.leftCeilGoods removeLastObject];
        
        // 从画面上移除
        [self removeChild:lastGoods cleanup:YES];
    }
    
    // 随机添加新的道具
    if (arc4random() % CEIL_GOODS_ADD_PROBABILITY == 0) {
        [self addNewCeilGoodsToSide:SIDE_LEFT];
    }
}


// 检查替换右天花板道具（离开屏幕的，删除，随即插入新的地面道具）
- (void) checkRightCeilGoods {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    CCSprite *lastGoods = [self.rightCeilGoods lastObject];
    if (lastGoods != nil && lastGoods.position.y > winSize.height + lastGoods.contentSize.height / 2) {
        
        // 删除最后一个地面道具
        [self.rightCeilGoods removeLastObject];
        
        // 从画面上移除
        [self removeChild:lastGoods cleanup:YES];
    }
    
    // 随机添加新的道具
    if (arc4random() % CEIL_GOODS_ADD_PROBABILITY == 0) {
        [self addNewCeilGoodsToSide:SIDE_RIGHT];
    }
}


// 添加新的地面道具，放置于走廊尽头
- (void) addNewFloorGoodsToSide:(int)side {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    int stage = delegate.delegateLogic.stage;                               // 关卡
    
    // 获取关卡定义数据
    NSDictionary *singleStageDef = [((GameStageScene *)[self parent]).stageDefinitionDM singleStageDefWithStage:stage];
    NSArray *floorGoodsImage = nil;
    if (side == SIDE_LEFT) {
        floorGoodsImage = [singleStageDef objectForKey:@"floorLeftGoods"];      // 左侧地面道具文件名数组
    } else {
        floorGoodsImage = [singleStageDef objectForKey:@"floorRightGoods"];     // 右侧地面道具文件名数组
    }

    if ([floorGoodsImage count] > 0) {
        int index = arc4random() % [floorGoodsImage count];
        NSString *fileName = [floorGoodsImage objectAtIndex:index];
        CCSprite *floorGoods = [CCSprite spriteWithFile:fileName];
        floorGoods.scale = 0.01f;
        floorGoods.position = self.goalPoint;
        
        // 添加到场景
        [self addChild:floorGoods z:2];
        
        // 添加到数组
        if (side == SIDE_LEFT) {
            [self.leftFloorGoods insertObject:floorGoods atIndex:0];
        } else {
            [self.rightFloorGoods insertObject:floorGoods atIndex:0];
        }
    }
}


// 添加新的天花板道具，放置于走廊尽头
- (void) addNewCeilGoodsToSide:(int)side {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    int stage = delegate.delegateLogic.stage;                               // 关卡
    
    // 获取关卡定义数据
    NSDictionary *singleStageDef = [((GameStageScene *)[self parent]).stageDefinitionDM singleStageDefWithStage:stage];
    NSArray *ceilGoodsImage = nil;
    if (side == SIDE_LEFT) {
        ceilGoodsImage = [singleStageDef objectForKey:@"ceilLeftGoods"];      // 左侧地面道具文件名数组
    } else {
        ceilGoodsImage = [singleStageDef objectForKey:@"ceilRightGoods"];     // 右侧地面道具文件名数组
    }
    
    if ([ceilGoodsImage count] > 0) {
        int index = arc4random() % [ceilGoodsImage count];
        NSString *fileName = [ceilGoodsImage objectAtIndex:index];
        CCSprite *goods = [CCSprite spriteWithFile:fileName];
        goods.scale = 0.01f;
        goods.position = self.goalPoint;
        
        // 添加到场景
        [self addChild:goods z:2];
        
        // 添加到数组
        if (side == SIDE_LEFT) {
            [self.leftCeilGoods insertObject:goods atIndex:0];
        } else {
            [self.rightCeilGoods insertObject:goods atIndex:0];
        }
    }
}


// 打击道具动画（飞行、破碎）
- (void) attackGoodsAnimationWithGoodsId:(int)goodsId {
    
    // 获取效果（眩晕时间）
    NSDictionary *singleGoodsDef = [((GameStageScene *)self.parent).goodsDefinitionDM singleGoodsDefWithGoodsId:goodsId];
    float effect = [[singleGoodsDef objectForKey:@"effect"] floatValue];
    
    AttackGoods *attackGoods = [[[AttackGoods alloc] initWithGoodsId:goodsId] autorelease];
    attackGoods.position = ccp(1200, 800);                                                  // 屏幕外的点
    attackGoods.scale = 1.5f;
    [self addChild:attackGoods z:5];
    CGPoint position = ccpAdd(self.doctor.doctorSpriteBatchNode.position, ccp(0, 300.0f * self.doctor.doctorSpriteBatchNode.scale));
    [attackGoods flyAndCrashWithPosition:position
                                   scale:self.doctor.doctorSpriteBatchNode.scale
                                  target:nil
                                selector:nil];
    
    // 医生眩晕动作
    // 延时处理，在飞行道具飞行完毕后执行
    id actDelay = [CCDelayTime actionWithDuration:0.5f];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        [self.doctor damageWithCallback:self.parent vertigoTime:effect];        
    }];
    id actSeq = [CCSequence actions:actDelay, actCallBlock, nil];
    [self runAction:actSeq];
}

/*
// 打击道具飞行完毕（命中医生）
- (void) attackGoodsFlyOverWithGoodsId {
    
    // 医生命中动画
    [self.doctor damageWithCallback:self.parent];
}*/


- (void) dealloc {
    self.doctor = nil;
    self.leftWalls = nil;
    self.rightWalls = nil;
    self.leftFloorGoods = nil;
    self.rightFloorGoods = nil;
    self.middleCeilGoods = nil;
    self.leftCeilGoods = nil;
    self.rightCeilGoods = nil;
    [super dealloc];
}


@end


// ------------------- 操作层 ---------------------
@implementation GameStagePlayLayer

@synthesize startPoint = startPoint_;
@synthesize prePoint = prePoint_;
@synthesize moveStartTime = moveStartTime_;

/*
- (id) init {
    if (self = [super init]) {
        self.isTouchEnabled = YES;
    }
    
    return self;
}*/


- (void) registerWithTouchDispatcher {	
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:kCCMenuTouchPriority swallowsTouches:NO];
}


- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event {
    
    // 如果是打击模式，不许移动
    if (((GameStageScene *)[self parent]).attackMode == YES) {
        return YES;
    }
    
    // 移除上次的滑行动作
    [self stopActionByTag:E_ACTION_TAG_ID_SLIDE_ON_PLAY_LAYER];
    
	CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];

	self.startPoint = touchPoint;
    self.prePoint = touchPoint;
    self.moveStartTime = [[NSDate date] timeIntervalSince1970];
    
    // 开始移动逻辑
    [(GameStageScene *)[self parent] patientMoveBegan];
    
	return YES;
}


- (void)ccTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event {
    
    // 如果是打击模式，不许移动
    if (((GameStageScene *)[self parent]).attackMode == YES) {
        return;
    }
    
	CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];
    
    if (touchPoint.y - self.prePoint.y > 0) {
        int moveDistance = touchPoint.y - self.prePoint.y;
        self.prePoint = touchPoint;
        
        // 移动
        if (moveDistance > 120) {
            moveDistance = 120;
        }
        [(GameStageScene *)[self parent] moveWithDistance:moveDistance];
    }
}


- (void)ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event {
/*
	CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];
	
	CGPoint endPoint = touchPoint;
	
	if (endPoint.y - self.startPoint.y > CONTROL_SPEED_MIN) {
        [(GameStageScene *)[self parent] speedUp];
    } else if(endPoint.y - self.startPoint.y < -CONTROL_SPEED_MIN) {
        [(GameStageScene *)[self parent] speedDown];
    }
*/

    // 如果是打击模式，不许移动
    if (((GameStageScene *)[self parent]).attackMode == YES) {
        return;
    }
    
    // 获取点击的点
    CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];
	
    // 获取移动距离
	CGPoint endPoint = touchPoint;
    double swipeDistance = endPoint.y - self.startPoint.y;

    
    // 计算移动速度 -----------------------------------------------------------------
    // 获取移动时间
    NSTimeInterval moveEndTime = [[NSDate date] timeIntervalSince1970];
    NSTimeInterval moveTime = moveEndTime - self.moveStartTime;
    
    // 计算速度，时间 / 距离
    double speed = moveTime / swipeDistance;
    
    
    // 高速移动引起医生警觉，立即回头 ---------------------------------------------------
    CCLOG(@"swipedistance: %f", swipeDistance);
    float distance = ((GameStageScene *)[self parent]).distance;
    
    // 在警戒距离内
//    if (distance < DISTANCE_WARNING) {
//        
//        // 滑动距离达到一定长度以上
//        if (swipeDistance > 100) {
///*            
//            // 获取移动时间
//            NSTimeInterval moveEndTime = [[NSDate date] timeIntervalSince1970];
//            NSTimeInterval moveTime = moveEndTime - self.moveStartTime;
//            
//            // 计算速度，时间 / 距离
//            double speed = moveTime / swipeDistance;
//*/
//            // 检查医生动作，是否立即回头
//            [(GameStageScene *)[self parent] checkDoctorMoveWithSwipeSpeed:speed];
//        }
//    }
    
    
    // 滑行一段距离 -----------------------------------------------------------------------------
    int slideDistance = swipeDistance / 2;                                      // 滑行总距离
    float slideTime = 0.2f;                                                     // 滑行总时间
    int times = 10;                                                             // 调用次数
    int slideDistanceEveryTime = slideDistance / times;                         // 每次滑行距离
    float delayDuration = slideTime / times;                                    // 调用间隔时间
    
    id actCallBlock = [CCCallBlock actionWithBlock:^{

        // 移动
        if (slideDistanceEveryTime > 0) {
            [(GameStageScene *)[self parent] moveWithDistance:slideDistanceEveryTime];
        }
    }];
    id actDelay = [CCDelayTime actionWithDuration:delayDuration];
    id actSeq = [CCSequence actions:actCallBlock, actDelay, nil];
    id actRepeat = [CCRepeat actionWithAction:actSeq times:times];
    
    id actCallBlock2 = [CCCallBlock actionWithBlock:^{
        
        // 病人动作
        if (speed < 0.001) {
            [(GameStageScene *)[self parent] patientBrake];
        } else {
            [(GameStageScene *)[self parent] patientStay];
        }
    }];
    CCAction *actSeq2 = [CCSequence actions:actRepeat, actCallBlock2, nil];
    actSeq2.tag = E_ACTION_TAG_ID_SLIDE_ON_PLAY_LAYER;
    [self runAction:actSeq2];
}


@end


// ----------------- 菜单层 -------------------
@implementation GameStageMenuLayer {
    BOOL isUsingGoods;
}

@synthesize pointer = pointer_;
@synthesize patientIcon = patientIcon_;
@synthesize patient = patient_;
@synthesize timeLabel = timeLabel_;

// 加载层内容，初始化变量
- (void) loadContentsOfLayer {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    isUsingGoods = NO;
    
    // 添加钟表 --------------------------------------------------
    // 表背景（文字提示）
    CCSprite* clockBg = [CCSprite spriteWithFile:@"clock_bg.png"];
    clockBg.position = ccp(clockBg.contentSize.width / 2, winSize.height - clockBg.contentSize.height / 2);
    [self addChild:clockBg];
    
    // 表盘
    CCSprite *clock = [CCSprite spriteWithFile:@"clock.png"];
    clock.position = ccp(70, 620);
    [self addChild:clock];
    
    // 表指针
    self.pointer = [CCSprite spriteWithFile:@"pointer.png"];
    self.pointer.position = clock.position;
    [self addChild:self.pointer];
    
    self.timeLabel = [CCLabelTTF labelWithString:@""
                                        fontName:@"impact"
                                        fontSize:40];
    self.timeLabel.position = clock.position;
    [self addChild:self.timeLabel];
    
    
    // 添加距离条 --------------------------------------------------
    // 距离条
    CCSprite *distanceBar = [CCSprite spriteWithFile:@"distance_bar.png"];
    distanceBar.position = ccp(winSize.width / 2, 650);
    [self addChild:distanceBar];
    
    // 警戒区域条
    CCProgressTimer *distanceBarWarning = [CCProgressTimer progressWithFile:@"distance_bar_warning.png"];
    distanceBarWarning.position = ccp(distanceBar.contentSize.width / 2, distanceBar.contentSize.height / 2);
    distanceBarWarning.type = kCCProgressTimerTypeHorizontalBarLR;
    distanceBarWarning.percentage = (float)DISTANCE_WARNING / DISTANCE_MAX_TO_GAME_OVER * 100.f;
    [distanceBar addChild:distanceBarWarning];
    
    // BOSS图标
    int doctorId = [((GameStageScene *)[self parent]).stageDefinitionDM doctorIdWithStage:delegate.delegateLogic.stage];
    NSString *fileName = [NSString stringWithFormat:@"distance_bar_boss_%i.png", doctorId];
    CCSprite *bossIcon = [CCSprite spriteWithFile:fileName];
    bossIcon.anchorPoint = ccp(0.5f, 0.0f);
    bossIcon.position = ccp(30, 5);
    [distanceBar addChild:bossIcon];
    
    // 病人图标
    fileName = [NSString stringWithFormat:@"distance_bar_patient_%i.png", delegate.delegateLogic.patientCharacter];
    self.patientIcon = [CCSprite spriteWithFile:fileName];
    self.patientIcon.anchorPoint = bossIcon.anchorPoint;
    self.patientIcon.position = ccp(0, bossIcon.position.y);                                            // 初始位置
    [self updatePatientIconPositionWithDistanceRatio:(float)DISTANCE_INIT / DISTANCE_MAX_TO_GAME_OVER]; // 更新位置
    [distanceBar addChild:self.patientIcon];
    
    
    // 添加菜单按钮 --------------------------------------------------
    // 暂停按钮
    CCSprite *spriteForMenuItemPauseNormal = [CCSprite spriteWithFile:@"btn_pause_normal.png"];
    CCSprite *spriteForMenuItemPauseSelected = [CCSprite spriteWithFile:@"btn_pause_normal.png"];
    CCMenuItem *menuItemPause = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemPauseNormal
                                                        selectedSprite:spriteForMenuItemPauseSelected
                                                                target:self
                                                              selector:@selector(onPauseBtnSelected)];
    
    // 设置按钮
    CCSprite *spriteForMenuItemConfigNormal = [CCSprite spriteWithFile:@"btn_config_normal.png"];
    CCSprite *spriteForMenuItemConfigSelected = [CCSprite spriteWithFile:@"btn_config_normal.png"];
    CCMenuItem *menuItemConfig = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemConfigNormal
                                                        selectedSprite:spriteForMenuItemConfigSelected
                                                                target:self
                                                              selector:@selector(onConfigBtnSelected)];
    
    CCMenu *menu = [CCMenu menuWithItems:menuItemPause, menuItemConfig, nil];
    [menu alignItemsHorizontally];
    menu.position = ccp(950, 730);
    [self addChild:menu];
    
    
    // 添加吊瓶 --------------------------------------------------
    // 添加吊瓶背景
    CCSprite *bottleBg = [CCSprite spriteWithFile:@"bottle_bg.png"];
    bottleBg.position = ccp(940, 510);
    [self addChild:bottleBg];
    
    // 添加吊瓶内病人动画对象
    self.patient = [[[Patient alloc] init] autorelease];
    self.patient.patientSpriteBatchNode.position = bottleBg.position;
    [self addChild:self.patient.patientSpriteBatchNode];
    
    // 添加吊瓶表层
    CCSprite *bottle = [CCSprite spriteWithFile:@"bottle.png"];
    bottle.position = ccp(winSize.width - bottle.contentSize.width / 2, winSize.height / 2);
    [self addChild:bottle];
    

    // 添加道具栏 --------------------------------------------------
    // 添加道具栏背景
//    CCSprite *goodsBarBg = [CCSprite spriteWithFile:@"goods_bar_bg.png"];
//    goodsBarBg.position = ccp(winSize.width / 2, 100);
//    [self addChild:goodsBarBg];
    
    // 添加道具
//    NSDictionary *goods = [delegate.delegateLogic.appProfile goods];        // 用户道具信息
//    CCMenu *menuForGoods = [CCMenu menuWithItems: nil];                     // 道具菜单
//    NSArray *goodsKeys = [goods allKeys];
//    for (int i = 0; i < 4; i++) {
//        if (i + 1 <= [goodsKeys count]) {
//            NSString *key = [goodsKeys objectAtIndex:i];
//            int goodsId = [key intValue];
//            NSString *goodsAmountStr = [[goods objectForKey:key] stringValue];          // 道具数量
//            
//            // 道具菜单项
//            NSString *goodsFileName = [NSString stringWithFormat:@"goods_%i_small_normal.png", goodsId];
//            CCMenuItem *menuItemForGoods = [CCMenuItemImage itemFromNormalImage:goodsFileName
//                                                                  selectedImage:goodsFileName
//                                                                         target:self
//                                                                       selector:@selector(onGoodsSelected:)];
//            
//            // 将道具ID写入tag
//            menuItemForGoods.tag = goodsId;
//            
//            // 添加道具数量显示
//            CCLabelTTF *labelForGoodsAmount = [CCLabelTTF labelWithString:goodsAmountStr
//                                                                 fontName:@"impact"
//                                                                 fontSize:32];
//            labelForGoodsAmount.color = ccc3(71, 21, 18);
//            labelForGoodsAmount.position = ccp(55, 25);
//            labelForGoodsAmount.tag = 1;
//            [menuItemForGoods addChild:labelForGoodsAmount];
//            
//            // 将菜单项加入菜单
//            [menuForGoods addChild:menuItemForGoods];
//            
//        } else {
//            
//            // 添加空槽菜单项
//            CCMenuItem *menuItemForGoods = [CCMenuItemImage itemFromNormalImage:@"goods_none_small_normal.png"
//                                                                  selectedImage:@"goods_none_small_normal.png"];
//            
//            // 将菜单项加入菜单
//            [menuForGoods addChild:menuItemForGoods];
//        }
//    }
//    
//    [menuForGoods alignItemsHorizontally];
////    menuForGoods.anchorPoint = ccp(0.0f, 0.5f);
//    menuForGoods.position = ccp(goodsBarBg.contentSize.width / 2, 50);
//    [goodsBarBg addChild:menuForGoods];
    
    
    // ------------------------------------ready go提示 ----------------------------------
    CCSprite *ready = [CCSprite spriteWithFile:@"ready.png"];
    ready.position = ccp(winSize.width / 2, winSize.height / 2);
    ready.scale = 0.0001f;
    [self addChild:ready];
    
    // ready动作
    id actDelayForReady = [CCDelayTime actionWithDuration:0.5f];                    // 延时，用于弥补场景切换的时间
    id actScaleToForReady = [CCEaseElasticOut actionWithAction:[CCScaleTo actionWithDuration:0.5f scale:1.0f]
                                                       period:0.5f];
    id actCallFuncNForReady = [CCCallFuncN actionWithTarget:self selector:@selector(showGo:)];
    id actSeqForReady = [CCSequence actions:actDelayForReady, actScaleToForReady, actCallFuncNForReady, nil];
    [ready runAction:actSeqForReady];
}


// 显示Go，启动游戏
- (void) showGo:(id)sender {
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    
    // 清除ready
    [sender removeFromParentAndCleanup:YES];

    // 添加Go
    CCSprite *go = [CCSprite spriteWithFile:@"go.png"];
    go.position = ccp(winSize.width / 2, winSize.height / 2);
    go.scale = 0.0001f;
    [self addChild:go];
    
    // Go动作
    id actScaleToForGo = [CCEaseElasticOut actionWithAction:[CCScaleTo actionWithDuration:0.5f scale:1.0f]
                                                        period:0.5f];
    id actDelayForGo = [CCDelayTime actionWithDuration:0.5f];
    id actCallBlockForGo = [CCCallBlock actionWithBlock:^{
        [(id)[self parent] startGame];
        [go removeFromParentAndCleanup:YES];
    }];
    id actSeqForGo = [CCSequence actions:actScaleToForGo, actDelayForGo, actCallBlockForGo, nil];
    [go runAction:actSeqForGo];
}


// 当道具按下
- (void) onGoodsSelected:(id)sender {
    if (isUsingGoods == YES) {
        return;
    }
    isUsingGoods = YES;
    
    
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    CCMenuItem *menuItem = (CCMenuItem *)sender;
    int goodsId = menuItem.tag;

    
    // 使用道具逻辑
    [(id)[self parent] useGoodsWithGoodsId:goodsId];
    
    
    //TODO 更新道具栏显示 --------------------------------------------
    int goodsAmount = [delegate.delegateLogic.appProfile goodsAmountWithGoodsId:goodsId];
    if (goodsAmount == 0) {

        // 设置隐藏，防止并发点击
        menuItem.visible = NO;
        
        // 将道具替换为【无道具】图标
        CCMenu *menu = (CCMenu *)[menuItem parent];
        
        // 添加新的菜单项目
        CCMenuItem *menuItemForGoods = [CCMenuItemImage itemFromNormalImage:@"goods_none_small_normal.png"
                                                              selectedImage:@"goods_none_small_normal.png"];
        menuItemForGoods.position = menuItem.position;
        [menu addChild:menuItemForGoods];

        // 清除旧的菜单项
//        [menuItem removeFromParentAndCleanup:YES];
//        [menu removeChild:menuItem cleanup:YES];
    } else {
        
        // 更新道具数量Label
        CCLabelTTF *labelForGoodsAmount = (CCLabelTTF *)[menuItem getChildByTag:1];
        [labelForGoodsAmount setString:[NSString stringWithFormat:@"%i", goodsAmount]];
    }
    

    // 延时解锁
    id actDelay = [CCDelayTime actionWithDuration:2.0f];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        isUsingGoods = NO;
    }];
    id actSeq = [CCSequence actions:actDelay, actCallBlock, nil];
    [self runAction:actSeq];
}


// 当暂停按钮按下
- (void) onPauseBtnSelected {
    [(GameStageScene *)[self parent] pause];
}


// 当设置按钮按下
- (void) onConfigBtnSelected {
    [(GameStageScene *)[self parent] showConfig];
}

// 更新时间
- (void) updateTimeLabelWithTime:(int)time
{
    [self.timeLabel setString:[NSString stringWithFormat:@"%i",time]];
}

// 更新钟表指针角度
- (void) updatePointerRotationWithTimeRatio:(float)timeRatio {

    // 计算角度
    float rotation = timeRatio * 360.0f;

    // 设置指针角度
    self.pointer.rotation = rotation;
}


// 更新距离条中病人图标位置
- (void) updatePatientIconPositionWithDistanceRatio:(float)distanceRatio {
    
    // 计算X距离
    float x = PATIENT_ICON_X_MIN + (PATIENT_ICON_X_MAX - PATIENT_ICON_X_MIN) * distanceRatio;
    
    // 设置病人图标位置
    self.patientIcon.position = ccp(x, self.patientIcon.position.y);
}


- (void) dealloc {
    self.pointer = nil;
    self.patientIcon = nil;
    self.patient = nil;
    self.timeLabel = nil;
    [super dealloc];
}

@end


// --------------------- 游戏场景打击层 ------------------------
@implementation GameStageAttackLayer

@synthesize cursor = cursor_;

// 初始化方法
- (id) init {
	if ((self = [super init])) {
		
		// 添加光标 -------------------------------------------------------------------------------------------------
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"punch.plist" textureFile:@"punch.pvr.ccz"];
        CCSpriteBatchNode *spriteBatchNode = [CCSpriteBatchNode batchNodeWithFile:@"punch.pvr.ccz"];
        [self addChild:spriteBatchNode];
        
        self.cursor = [CCSprite spriteWithSpriteFrameName:@"punch_1.png"];
        self.cursor.position = ccp(512, 300);
        [spriteBatchNode addChild:self.cursor];
        
        
        // 光标动画 -------------------------------------------------------------------------------------------------
        // 将动画帧放入数组
        NSMutableArray *animFrames = [NSMutableArray array];                                        // 存储动画帧的数组
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:@"punch_1.png"]];
        [animFrames addObject:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:@"punch_2.png"]];
        
        // 创建动画对象
        CCAnimation *anim = [CCAnimation animationWithFrames:animFrames delay:0.2f];
        
        // 动作
        id actAnimate = [CCRepeatForever actionWithAction:[CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO]];
        [self.cursor runAction:actAnimate];
         
        
        // 光标出现动作 ----------------------------------------------------------------------------------------------
        self.cursor.scale = 2.5f;
        id actScaleTo = [CCScaleTo actionWithDuration:0.5f scale:1.0f];
        id actFade = [CCFadeIn actionWithDuration:0.5f];
        id actSpawn = [CCSpawn actions:actScaleTo, actFade, nil];
        id actCallBlock = [CCCallBlock actionWithBlock:^{
            
            // 设置允许点击
            self.isTouchEnabled = YES;
            
            // 光标运动
            [self cursorMove];
        }];
        
        // 一定时间内未打击视作打击失败
        id actDelay = [CCDelayTime actionWithDuration:3.0f];
        id actCallBlock2 = [CCCallBlock actionWithBlock:^{
            self.isTouchEnabled = NO;
            [(GameStageScene *)[self parent] attackMiss];
        }];
        
        id actSeq = [CCSequence actions:actSpawn, actCallBlock, actDelay, actCallBlock2, nil];
        [self.cursor runAction:actSeq];

	}
	
	return self;
}


// 光标运动
- (void) cursorMove {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 根据不同难度添加光标运动
    if (delegate.delegateLogic.difficult == DIFFICULT_NORMAL) {
        CGPoint point = self.cursor.position;
        
        id actDelay = [CCDelayTime actionWithDuration:1.0f];
        id actBlink = [CCBlink actionWithDuration:0.5f blinks:5];
        id actCallBlock = [CCCallBlock actionWithBlock:^{
            int offsetX = arc4random() % 100;
            int offsetY = arc4random() % 120;
            if (arc4random() % 2 == 0) {
                offsetX = -offsetX;
            }
            if (arc4random() % 2 == 0) {
                offsetY = -offsetY;
            }
            
            self.cursor.position = ccpAdd(point, ccp(offsetX, offsetY));
        }];
        id actSeq = [CCSequence actions:actDelay, actBlink, actCallBlock, nil];
        id actRepeatForever = [CCRepeatForever actionWithAction:actSeq];
        [self.cursor runAction:actRepeatForever];
        
    } else if (delegate.delegateLogic.difficult == DIFFICULT_HARD) {
//        CGPoint point1 = ccpAdd(self.cursor.position, ccp(0, 100));
//        CGPoint point2 = self.cursor.position;
//        CGPoint point3 = ccpAdd(self.cursor.position, ccp(0, -100));
//        id actMoveTo1 = [CCMoveTo actionWithDuration:0.25f position:point3];
//        id actMoveTo2 = [CCMoveTo actionWithDuration:0.5f position:point1];
//        id actMoveTo3 = [CCMoveTo actionWithDuration:0.25f position:point2];
//        id actSeq = [CCSequence actions:actMoveTo1, actMoveTo2, actMoveTo3, nil];
//        id actRepeatForever = [CCRepeatForever actionWithAction:actSeq];
//        [self.cursor runAction:actRepeatForever];
        
        int xOffset = 50;
        int yOffset = 100;
        CGPoint point1 = ccpAdd(self.cursor.position, ccp(-xOffset, yOffset));
        CGPoint point2 = ccpAdd(self.cursor.position, ccp(xOffset, yOffset));
        CGPoint point3 = ccpAdd(self.cursor.position, ccp(-xOffset, -yOffset));
        CGPoint point4 = ccpAdd(self.cursor.position, ccp(xOffset, -yOffset));
        CGPoint point5 = self.cursor.position;
        id actMoveTo1 = [CCMoveTo actionWithDuration:0.25f position:point1];
        id actMoveTo2 = [CCMoveTo actionWithDuration:0.25f position:point2];
        id actMoveTo3 = [CCMoveTo actionWithDuration:0.5f position:point3];
        id actMoveTo4 = [CCMoveTo actionWithDuration:0.25f position:point4];
        id actMoveTo5 = [CCMoveTo actionWithDuration:0.25f position:point5];
        id actSeq = [CCSequence actions:actMoveTo1, actMoveTo2, actMoveTo3, actMoveTo4, actMoveTo5, nil];
        id actRepeatForever = [CCRepeatForever actionWithAction:actSeq];
        [self.cursor runAction:actRepeatForever];
    }
}


// 注册点击事件
- (void) registerWithTouchDispatcher {
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self
													 priority:kCCMenuTouchPriority + 1
											  swallowsTouches:YES];
}


// 点击开始
- (BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event {
    
    // 设置为不可点击
    self.isTouchEnabled = NO;
    
    // 获取点击的点
    CGPoint touchPoint = [touch locationInView:[touch view]];
	touchPoint = [[CCDirector sharedDirector] convertToGL:touchPoint];
    
    // 点击命中
    if (CGRectContainsPoint(self.cursor.boundingBox, touchPoint)) {
        [(GameStageScene *)[self parent] gameOverWithGameOverId:E_GAME_OVER_ID_WIN];
    } else {
        [(GameStageScene *)[self parent] attackMiss];
    }
    
	return YES;
}


- (void) dealloc {
    self.cursor = nil;
    [super dealloc];
}


@end


// --------------------- 游戏场景暂停层 ------------------------
@implementation GameStagePauseLayer

// 初始化方法
- (id) init {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
		
		// 添加菜单 ----------------------------------------------
		// 返回取消暂停按钮
		CCSprite *spriteForMenuItemResumeNormal = [CCSprite spriteWithFile:@"btn_resume_normal.png"];
		CCSprite *spriteForMenuItemResumeSelected = [CCSprite spriteWithFile:@"btn_resume_normal.png"];
		CCMenuItem *menuItemForResume = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemResumeNormal
																selectedSprite:spriteForMenuItemResumeSelected
																		target:self
																	  selector:@selector(onResumeSelected:)];
		
		CCMenu *menu = [CCMenu menuWithItems:menuItemForResume, nil];
		[self addChild:menu];

        
		// 设置允许点击
		self.isTouchEnabled = YES;
	}
	
	return self;
}


// 按下返回游戏
- (void) onResumeSelected:(id)sender {	
	[(GameStageScene *)[self parent] resume];
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


// --------------------- 游戏场景设置层 ------------------------
@implementation GameStageConfigLayer

// 初始化方法
- (id) init {
	if ((self = [super initWithColor:ccc4(0, 0, 0, 200)])) {
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        
        // 添加背景 ----------------------------------------------
        CCSprite *bg = [CCSprite spriteWithFile:@"config_bg.png"];
        bg.position = ccp(winSize.width / 2, winSize.height / 2);
        [self addChild:bg];
        
		
		// 添加菜单 ----------------------------------------------
        // 关闭按钮
		CCSprite *spriteForMenuItemCloseNormal = [CCSprite spriteWithFile:@"btn_close_normal.png"];
		CCSprite *spriteForMenuItemCloseSelected = [CCSprite spriteWithFile:@"btn_close_normal.png"];
		CCMenuItem *menuItemForClose = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemCloseNormal
                                                               selectedSprite:spriteForMenuItemCloseSelected
                                                                       target:self
                                                                     selector:@selector(onCloseSelected:)];
		
		CCMenu *menuForClose = [CCMenu menuWithItems:menuItemForClose, nil];
        menuForClose.position = ccp(680, 610);
		[self addChild:menuForClose];
        
        
        // BGM开关按钮
		CCMenuItem *menuItemForBGMOn = [CCMenuItemImage itemFromNormalImage:@"btn_bgm_on_normal.png"
                                                              selectedImage:@"btn_bgm_on_normal.png"];
		
		CCMenuItem *menuItemForBGMOff = [CCMenuItemImage itemFromNormalImage:@"btn_bgm_off_normal.png"
                                                               selectedImage:@"btn_bgm_off_normal.png"];
        
        CCMenuItemToggle *menuItemForBGM = [CCMenuItemToggle itemWithTarget:self
                                                             selector:@selector(onBGMSelected:)
                                                                items:menuItemForBGMOn, menuItemForBGMOff, nil];
        menuItemForBGM.rotation = -3;
        
        // 设置当前选中的项目
        if ([delegate.delegateLogic.appProfile bgm] == NO) {
            menuItemForBGM.selectedIndex = 1;
        }

        CCMenu *menuForBGM = [CCMenu menuWithItems:menuItemForBGM, nil];
        menuForBGM.position = ccp(460,420);
        [self addChild:menuForBGM];
        
        
        // SE开关按钮
		CCMenuItem *menuItemForSEOn = [CCMenuItemImage itemFromNormalImage:@"btn_se_on_normal.png"
                                                              selectedImage:@"btn_se_on_normal.png"];
		
		CCMenuItem *menuItemForSEOff = [CCMenuItemImage itemFromNormalImage:@"btn_se_off_normal.png"
                                                               selectedImage:@"btn_se_off_normal.png"];
        
        CCMenuItemToggle *menuItemForSE = [CCMenuItemToggle itemWithTarget:self
                                                                   selector:@selector(onSESelected:)
                                                                      items:menuItemForSEOn, menuItemForSEOff, nil];
        menuItemForSE.rotation = menuItemForBGM.rotation;
        
        // 设置当前选中的项目
        if ([delegate.delegateLogic.appProfile se] == NO) {
            menuItemForSE.selectedIndex = 1;
        }
        
        CCMenu *menuForSE = [CCMenu menuWithItems:menuItemForSE, nil];
        menuForSE.position = ccpAdd(menuForBGM.position, ccp(110, 5));
        [self addChild:menuForSE];
        
        
		// 重试按钮
		CCSprite *spriteForMenuItemRetryNormal = [CCSprite spriteWithFile:@"btn_retry_normal.png"];
		CCSprite *spriteForMenuItemRetrySelected = [CCSprite spriteWithFile:@"btn_retry_normal.png"];
		CCMenuItem *menuItemForRetry = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemRetryNormal
																selectedSprite:spriteForMenuItemRetrySelected
																		target:self
																	  selector:@selector(onRetrySelected:)];
		
		CCMenu *menuForRetry = [CCMenu menuWithItems:menuItemForRetry, nil];
        menuForRetry.position = ccp(410, 300);
		[self addChild:menuForRetry];
        
        // 返回地图按钮
		CCSprite *spriteForMenuItemMapNormal = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
		CCSprite *spriteForMenuItemMapSelected = [CCSprite spriteWithFile:@"btn_return_on_select_difficult_scene_normal.png"];
		CCMenuItem *menuItemForMap = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemMapNormal
                                                               selectedSprite:spriteForMenuItemMapSelected
                                                                       target:self
                                                                     selector:@selector(onMapSelected:)];
		
		CCMenu *menuForMap = [CCMenu menuWithItems:menuItemForMap, nil];
        menuForMap.position = ccpAdd(menuForRetry.position, ccp(110, 5));
		[self addChild:menuForMap];
        
        // 帮助按钮
		CCSprite *spriteForMenuItemHelpNormal = [CCSprite spriteWithFile:@"btn_help_normal.png"];
		CCSprite *spriteForMenuItemHelpSelected = [CCSprite spriteWithFile:@"btn_help_normal.png"];
		CCMenuItem *menuItemForHelp = [CCMenuItemSprite itemFromNormalSprite:spriteForMenuItemHelpNormal
                                                             selectedSprite:spriteForMenuItemHelpSelected
                                                                     target:self
                                                                   selector:@selector(onHelpSelected:)];
		
		CCMenu *menuForHelp = [CCMenu menuWithItems:menuItemForHelp, nil];
        menuForHelp.position = ccpAdd(menuForMap.position, ccp(110, 5));
		[self addChild:menuForHelp];
        
        
		// 设置允许点击
		self.isTouchEnabled = YES;
	}
	
	return self;
}


// 按下关闭按钮
- (void) onCloseSelected:(id)sender {	
    [(GameStageScene *)[self parent] closeConfig];
}


// 按下BGM开关
- (void) onBGMSelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    CCMenuItemToggle *menuItemToggle = (CCMenuItemToggle *)sender;
    BOOL bgm = YES;
    
    // 检查选中的项目
    if (menuItemToggle.selectedIndex == 1) {
        bgm = NO;
    }
    
    // 设置存档
    [delegate.delegateLogic.appProfile updateBgm:bgm];
    
    // 保存存档
    [delegate.delegateLogic.appProfile save];
}


// 按下SE开关
- (void) onSESelected:(id)sender {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    CCMenuItemToggle *menuItemToggle = (CCMenuItemToggle *)sender;
    BOOL se = YES;
    
    // 检查选中的项目
    if (menuItemToggle.selectedIndex == 1) {
        se = NO;
    }
    
    // 设置存档
    [delegate.delegateLogic.appProfile updateSe:se];
    
    // 保存存档
    [delegate.delegateLogic.appProfile save];
}


// 按下重试按钮
- (void) onRetrySelected:(id)sender {	
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    [delegate.delegateLogic goToGameStageScene];
    [[CCDirector sharedDirector] resume];
}


// 按下返回地图按钮
- (void) onMapSelected:(id)sender {	
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
//    [delegate.delegateLogic goToMapScene];
    [delegate.delegateLogic goToPatientModeSelectCharacterScene];
    [[CCDirector sharedDirector] resume];
}


// 按下帮助按钮
- (void) onHelpSelected:(id)sender {	
    [(id)[self parent] showHelp];
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


// --------------------- 游戏场景结果层（胜利或失败） ------------------------
@implementation GameStageResultLayer

@synthesize winBg2 = winBg2_;

- (id)init {
    if (self = [super init]) {
        
        // 释放内存
//        [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
//        [[CCDirector sharedDirector] purgeCachedData];
        [[CCTextureCache sharedTextureCache] removeUnusedTextures];
        
        // 设置允许点击
        self.isTouchEnabled = YES;
    }
    
    return  self;
}


// 显示胜利
- (void) showWin {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    int patientId = delegate.delegateLogic.patientCharacter;

  
    // 添加背景 -----------------------------------------------------------------------------
    // 添加背景1
    NSString *fileNameForBg1 = [NSString stringWithFormat:@"win_bg_1_for_patient_%i.png", patientId];
    CCSprite *winBg1 = [CCSprite spriteWithFile:fileNameForBg1];
    winBg1.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:winBg1];
    
    // 添加背景2
    NSString *fileNameForBg2 = [NSString stringWithFormat:@"win_bg_2_for_patient_%i.png", patientId];
    self.winBg2 = [CCSprite spriteWithFile:fileNameForBg2];
    self.winBg2.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:self.winBg2];
    
    
    // 添加病人 -----------------------------------------------------------------------------
    // 添加病人
    CGPoint startPointForPatient = ccp(-winSize.width / 2, winSize.height / 2);
    if (patientId == E_PATIENT_ID_GIRL || patientId == E_PATIENT_ID_DEPRESSION) {
        startPointForPatient = ccp(winSize.width * 1.5f, winSize.height / 2);
    }
    NSString *fileNameForPatient = [NSString stringWithFormat:@"win_for_patient_%i.png", patientId];
    CCSprite *patient = [CCSprite spriteWithFile:fileNameForPatient];
    patient.position = startPointForPatient;
    [self addChild:patient];
    
    // 病人动作
    CCDelayTime *actDelayForPatient = [CCDelayTime actionWithDuration:0.5f];
    CCMoveTo *actMoveToForPatient = [CCEaseElasticOut actionWithAction:[CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, winSize.height / 2)]
                                                               period:0.9f];
    CCSequence *actForPatient = [CCSequence actions:actDelayForPatient, actMoveToForPatient, nil];
    [patient runAction:actForPatient];
    
    
    // 添加winner文字 -----------------------------------------------------------------------------
    // winner文字Sprite
    CCSprite *winner;
    if (patientId == E_PATIENT_ID_GIRL || patientId == E_PATIENT_ID_NOBLE) {
        winner = [CCSprite spriteWithFile:@"winner_1.png"];
    } else {
        winner = [CCSprite spriteWithFile:@"winner_2.png"];
    }
    
    // 开始和结束坐标
    CGPoint startPointForWinner;
    CGPoint endPointForWinner;
    if (patientId == E_PATIENT_ID_GIRL) {
        endPointForWinner = ccp(300, 530);
        startPointForWinner = ccp(-winner.contentSize.width / 2, endPointForWinner.y);                      // 左侧飞入
    } else if (patientId == E_PATIENT_ID_NOBLE) {
        endPointForWinner = ccp(740, 170);
        startPointForWinner = ccp(winSize.width + winner.contentSize.width / 2, endPointForWinner.y);       // 右侧飞入
    } else if (patientId == E_PATIENT_ID_DEPRESSION) {
        endPointForWinner = ccp(240, 420);
        startPointForWinner = ccp(-winner.contentSize.width / 2, endPointForWinner.y);                      // 左侧飞入
    } else if (patientId == E_PATIENT_ID_FAT) {
        endPointForWinner = ccp(785, 280);
        startPointForWinner = ccp(winSize.width + winner.contentSize.width / 2, endPointForWinner.y);       // 右侧飞入
    }
    
    // 设置坐标，添加到画面
    winner.position = startPointForWinner;
    [self addChild:winner];
    
    // winner文字动作
    CCDelayTime *actDelayForWinner = [CCDelayTime actionWithDuration:1.0f];
    CCMoveTo *actMoveToForWinner = [CCEaseElasticOut actionWithAction:[CCMoveTo actionWithDuration:0.5f position:endPointForWinner]
                                                                period:0.9f];
    CCSequence *actForWinner = [CCSequence actions:actDelayForWinner, actMoveToForWinner, nil];
    [winner runAction:actForWinner];
    
    
    // 添加菜单
    [self addMenu];
    
    
    // 计划任务
    [self schedule:@selector(showAndHideWinBg2) interval:0.15f];
}


// 显示和隐藏胜利背景2（背景闪烁效果）
- (void) showAndHideWinBg2 {
    if (self.winBg2.visible == YES) {
        self.winBg2.visible = NO;
    } else {
        self.winBg2.visible = YES;
    }
}


// 显示失败
- (void) showLose {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    int doctorId = [((GameStageScene *)[self parent]).stageDefinitionDM doctorIdWithStage:delegate.delegateLogic.stage];

    
    // 添加背景 -----------------------------------------------------------------------------
    // 添加背景
    CCSprite *bg = [CCSprite spriteWithFile:@"lost_bg.png"];
    bg.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:bg];
    
    
    // 添加医生 -----------------------------------------------------------------------------
    // 添加医生
    CGPoint startPoint = ccp(winSize.width * 1.5f, winSize.height / 2);
    NSString *fileNameForDoctor = [NSString stringWithFormat:@"lost_for_doctor_%i.png", doctorId];
    CCSprite *doctor = [CCSprite spriteWithFile:fileNameForDoctor];
    doctor.position = startPoint;
    [self addChild:doctor];
    
    // 医生动作
    CCDelayTime *actDelayForDoctor = [CCDelayTime actionWithDuration:0.5f];
    CCMoveTo *actMoveToForDoctor = [CCEaseElasticOut actionWithAction:[CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, winSize.height / 2)]
                                                                period:0.9f];
    CCSequence *actSeqForDoctor = [CCSequence actions:actDelayForDoctor, actMoveToForDoctor, nil];
    [doctor runAction:actSeqForDoctor];
    

    // 添加Lost文字 -----------------------------------------------------------------------------
    // Lost文字Sprite
    CCSprite *lost;
    if (doctorId == 1 || doctorId == 2) {
        lost = [CCSprite spriteWithFile:@"lost_1.png"];
    } else {
        lost = [CCSprite spriteWithFile:@"lost_2.png"];
    }
    
    // 开始和结束坐标
    CGPoint endPointForLost = ccp(300, 150);
    CGPoint startPointForLost = ccp(-lost.contentSize.width / 2, endPointForLost.y);                      // 左侧飞入
    
    // 设置坐标，添加到画面
    lost.position = startPointForLost;
    [self addChild:lost];
    
    // Lost文字动作
    CCDelayTime *actDelayForLost = [CCDelayTime actionWithDuration:1.0f];
    CCMoveTo *actMoveToForLost = [CCEaseElasticOut actionWithAction:[CCMoveTo actionWithDuration:0.5f position:endPointForLost]
                                                             period:0.9f];
    CCSequence *actSeqForLost = [CCSequence actions:actDelayForLost, actMoveToForLost, nil];
    [lost runAction:actSeqForLost];
    
    
    // 添加菜单
    [self addMenu];
}


// 显示失败（被发现）
- (void) showLoseForFound {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    CGSize winSize = [[CCDirector sharedDirector] winSize];
    
    // 医生ID
    int doctorId = [((GameStageScene *)[self parent]).stageDefinitionDM doctorIdWithStage:delegate.delegateLogic.stage];
    
    
    // 添加被发现效果（大眼睛注视）
    // 添加背景
    NSString *fileNameForEyesBg = [NSString stringWithFormat:@"eyes_bg_for_doctor_%i.png", doctorId];
    CCSprite *eyesBg = [CCSprite spriteWithFile:fileNameForEyesBg];
    eyesBg.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:eyesBg];
    
    // 添加人物
    NSString *fileNameForEyes = [NSString stringWithFormat:@"eyes_for_doctor_%i.png", doctorId];
    CCSprite *eyes = [CCSprite spriteWithFile:fileNameForEyes];
    eyes.position = ccp(winSize.width / 2 + 500, winSize.height / 2);
    [self addChild:eyes];
    
    // 人物动作
    id actMoveTo = [CCMoveTo actionWithDuration:0.5f position:ccp(winSize.width / 2, winSize.height / 2)];
    id actFadeIn = [CCFadeIn actionWithDuration:0.5f];
    id actSpawn = [CCSpawn actions:actMoveTo, actFadeIn, nil];
    id actDelay = [CCDelayTime actionWithDuration:1.5f];
    id actCallBlock = [CCCallBlock actionWithBlock:^{
        [self showLose];
    }];
    id actSeq = [CCSequence actions:actSpawn, actDelay, actCallBlock, nil];
    [eyes runAction:actSeq];
    
    // 添加前景
    CCSprite *eyesFg = [CCSprite spriteWithFile:@"eyes_fg.png"];
    eyesFg.position = ccp(winSize.width / 2, winSize.height / 2);
    [self addChild:eyesFg];
    
    
    // 添加菜单
    [self addMenu];
    
    // 设置允许点击
//    self.isTouchEnabled = YES;
}


// 添加菜单
- (void) addMenu {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 重试按钮
    CCMenuItem *menuItemForRetry = [CCMenuItemImage itemFromNormalImage:@"btn_retry_normal.png"
                                                          selectedImage:@"btn_retry_normal.png"
                                                                  block:^(id sender) {
                                                                      [delegate.delegateLogic goToGameStageScene];
                                                                  }];
    CCMenu *menuForRetry = [CCMenu menuWithItems:menuItemForRetry, nil];
    menuForRetry.position = ccp(970, 50);
    [self addChild:menuForRetry];
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


- (void) dealloc {
    self.winBg2 = nil;
    [super dealloc];
}

@end


// ------------------- 场景 ---------------------
@implementation GameStageScene

@synthesize bgLayer = bgLayer_;
@synthesize menuLayer = menuLayer_;

@synthesize stageDefinitionDM = stageDefinitionDM_;
@synthesize patientDefinitionDM = patientDefinitionDM_;
@synthesize goodsDefinitionDM = goodsDefinitionDM_;
@synthesize doctorActionProbabilityDef = doctorActionProbabilityDef_;
@synthesize time = time_;
@synthesize timeLimit = timeLimit_;
//@synthesize speedUpToWalk = speedUpToWalk_;
//@synthesize speedUpToRun = speedUpToRun_;
//@synthesize speedDownToWalk = speedDownToWalk_;
//@synthesize speedDownToStand = speedDownToStand_;
//@synthesize stepLength = stepLength_;
//@synthesize walkTimePerStep = walkTimePerStep_;
//@synthesize runTimePerStep = runTimePerStep_;
@synthesize swipeDistancePerMoveDistance = swipeDistancePerMoveDistance_;
@synthesize patientStatus = patientStatus_;
@synthesize swipeValue = swipeValue_;
@synthesize isMoving = isMoving_;
@synthesize distance = distance_;
@synthesize attackMode = attackMode_;
@synthesize isGameOver = isGameOver_;


+ (id) scene {
    
    GameStageScene *scene = [GameStageScene node];
    
    GameStageBgLayer *bgLayer = [[[GameStageBgLayer alloc] initWithColor:ccc4(255, 255, 255, 255)] autorelease];
    [scene addChild:bgLayer z:E_Z_ORDER_BG_LAYER];
    scene.bgLayer = bgLayer;
    [bgLayer loadContentsOfLayer];      // 载入层内容，必须在加入场景之后
    
    GameStagePlayLayer *playLayer = [GameStagePlayLayer node];
    [scene addChild:playLayer z:E_Z_ORDER_PLAY_LAYER tag:E_TAG_ID_PLAY_LAYER];
    
    GameStageMenuLayer *menuLayer = [GameStageMenuLayer node];
    scene.menuLayer = menuLayer;
    [scene addChild:menuLayer z:E_Z_ORDER_MENU_LAYER];
    [menuLayer loadContentsOfLayer];
    
    // 添加遮罩层
    CoverLayer *coverLayer = [CoverLayer node];
    [scene addChild:coverLayer z:9999 tag:E_TAG_ID_COVER_LAYER];
    
    return scene;
}


- (id) init {
    if (self = [super init]) {
        AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
        
        self.stageDefinitionDM = [[[StageDefinitionDM alloc] init] autorelease];
        self.patientDefinitionDM = [[[PatientDefinitionDM alloc] init] autorelease];
        self.goodsDefinitionDM = [[[GoodsDefinitionDM alloc] init] autorelease];
        
        
        // 获取单个关卡定义
        NSDictionary *singleStageDef = [self.stageDefinitionDM singleStageDefWithStage:delegate.delegateLogic.stage];
        
        // 获取单个病人定义
        NSDictionary *singlePatientDef = [self.patientDefinitionDM singlePatientDefWithPatientId:delegate.delegateLogic.patientCharacter];
        
        // 初始化医生动作定义
        int doctorId = [[singleStageDef objectForKey:@"doctorId"] intValue];
        DoctorActionProbabilityDefinitionDM *doctorActionProbabilityDefinitionDM = [[[DoctorActionProbabilityDefinitionDM alloc] init] autorelease];
        self.doctorActionProbabilityDef = [doctorActionProbabilityDefinitionDM singleDefWithDoctorId:doctorId difficultId:delegate.delegateLogic.difficult];
        
        // 时间限制
        self.time = 0;
        self.timeLimit = [self.stageDefinitionDM timeLimitWithStage:delegate.delegateLogic.stage
                                                          difficult:delegate.delegateLogic.difficult];

        // 初始化病人数据
//        self.speedUpToWalk = [[singlePatientDef objectForKey:@"speedUpToWalk"] intValue] + [[singleStageDef objectForKey:@"speedUp"] intValue]; 
//        self.speedUpToRun = [[singlePatientDef objectForKey:@"speedUpToRun"] intValue] + [[singleStageDef objectForKey:@"speedUp"] intValue];
//        self.speedDownToStand = [[singlePatientDef objectForKey:@"speedUpToWalk"] intValue] + [[singleStageDef objectForKey:@"speedDown"] intValue];
//        self.speedDownToWalk = [[singlePatientDef objectForKey:@"speedUpToRun"] intValue] + [[singleStageDef objectForKey:@"speedDown"] intValue];
//        self.stepLength = [[singlePatientDef objectForKey:@"stepLength"] intValue];
//        self.walkTimePerStep = [[singlePatientDef objectForKey:@"walkTimePerStep"] floatValue];
//        self.runTimePerStep = [[singlePatientDef objectForKey:@"runTimePerStep"] floatValue];
        
        self.swipeDistancePerMoveDistance = [[singlePatientDef objectForKey:@"swipeDistancePerMoveDistance"] floatValue];
        self.patientStatus = PATIENT_STATUS_STAND;
        
        // 医生与病人的距离
        self.distance = DISTANCE_INIT;
        
        // 滑动值
        self.swipeValue = 0;
        
        // 正在移动
        self.isMoving = NO;
/*
        // 计划任务：检查病人状态
        [self scheduleUpdate];
        
        // 计划任务：倒计时
        [self schedule:@selector(updateCountdown) interval:1];*/
//        [self startGame];
    }
    
    return self;
}


// 开始游戏（启动计划任务，设置界面点击等）
- (void) startGame {

    // ---------------------------------- 启动计划任务 ---------------------------------
    // 计划任务：检查病人状态
    [self scheduleUpdate];
    
    // 计划任务：倒计时
    [self schedule:@selector(updateCountdown) interval:1];
    
    // ---------------------------------- 设置层点击 ---------------------------------
    // 游戏层
    GameStagePlayLayer *playLayer = (GameStagePlayLayer *)[self getChildByTag:E_TAG_ID_PLAY_LAYER];
    playLayer.isTouchEnabled = YES;
    
    // ---------------------------------- 去除遮罩层 ---------------------------------
    [self removeCoverLayer];
}


// 去除遮罩层
- (void) removeCoverLayer {
    CoverLayer *coverLayer = (id)[self getChildByTag:E_TAG_ID_COVER_LAYER];
    [coverLayer removeFromParentAndCleanup:YES];
}


// 每一帧调用一次
- (void) update:(id)sender {

    // 检查并移动
//    [self move];
    
    // 设置医生位置
    [self.bgLayer setDoctorPositionWithDistance:self.distance];
    
    // 设置距离条上病人图标的位置
    [self.menuLayer updatePatientIconPositionWithDistanceRatio:self.distance / DISTANCE_MAX_TO_GAME_OVER];
    
    // 医生动作
    [self doctorMove];
}


// 更新倒计时
- (void) updateCountdown {
    self.time++;
    if (self.time > self.timeLimit) {
        self.time = self.timeLimit;
    }
    
    [self.menuLayer updateTimeLabelWithTime:(self.timeLimit - self.time)];
    
    float timeRatio = (float)self.time / self.timeLimit;        // 时间比例

    // 更新时间显示
    [self.menuLayer updatePointerRotationWithTimeRatio:timeRatio];
    
    
    // 判定游戏失败
    if (self.time == self.timeLimit) {

        // 显示游戏结果（失败）
        [self gameOverWithGameOverId:E_GAME_OVER_ID_LOSE];
    }
}


// 获取随即的动作ID
- (int) randomActionId {
    int actionId = 0;
    
    int rand = arc4random() % 100 + 1;
    for (NSDictionary *def in self.doctorActionProbabilityDef) {
        int lower = [[def objectForKey:@"lower"] intValue];
        int upper = [[def objectForKey:@"upper"] intValue];
        if (rand >= lower && rand <= upper) {
            actionId = [[def objectForKey:@"actionId"] intValue];
            break;
        }
    }
    
    return actionId;
}


// 医生做动作
- (void) doctorMove {

    // 如果是打击模式，退出
    if (self.attackMode == YES) {
        return;
    }
    
    if (self.bgLayer.doctor.isMoving == NO) {
        self.bgLayer.doctor.isMoving = YES;
        
        // 获取随即动作ID
        int actionId = [self randomActionId];
        
        switch (actionId) {
            case DOCTOR_ACTION_ID_WALK:
                if (self.distance < DISTANCE_WARNING && arc4random() % DOCTOR_RUN_PROBABILITY == 0) {
                    [self.bgLayer.doctor walkWithCallback:self fast:YES];
                } else {
                    [self.bgLayer.doctor walkWithCallback:self fast:NO];
                }
                break;
            case DOCTOR_ACTION_ID_STAY:
                [self.bgLayer.doctor stayWithMoving:NO];
                break;
            case DOCTOR_ACTION_ID_FEINT:
                [self.bgLayer.doctor stayAndFeint];
                break;
            case DOCTOR_ACTION_ID_TURN_AROUND:
                [self.bgLayer.doctor stayAndTurnAroundWithCallback:self];
                break;
                
            default:
                break;
        }
    }
}


// 检查时候被发现，用于医生回头的回调函数
- (void) checkFound {
    
    // 防止并发调用
    if (self.isGameOver == YES) {
        return;
    }
    
    // 病人不是站立状态，则被发现
    if ([self.menuLayer.patient isSafe] == NO) {
        CCLOG(@"found");
        
        [self gameOverWithGameOverId:E_GAME_OVER_ID_LOSE_BY_FOUND];
    }
}


// 检查高速移动（快速滑动），引起医生立即回头
- (void) checkDoctorMoveWithSwipeSpeed:(double)speed {
    
    if (speed < 0.001)
    {
        [self.bgLayer.doctor justTurnAroundWithCallback:self];
    }
}


// 增加距离
- (void) addDistanceOfPatientAndDoctor:(float)distance {
    self.distance += distance;
    if (self.distance < 0) {
        self.distance = 0;
        
        // 执行打击
        [self startAttackMode];
        
    } else if(self.distance > DISTANCE_MAX_TO_GAME_OVER) {
        self.distance = DISTANCE_MAX_TO_GAME_OVER;
        
        // 医生逃离，GAME OVER
        // 显示游戏结果（失败）
        [self gameOverWithGameOverId:E_GAME_OVER_ID_LOSE];
    }
}


// 检查运动 参数：屏幕滑动点距离
- (void) moveWithDistance:(int)swipeDistance {
    
    if (self.attackMode == YES) {
        return;
    }
    
    // 将屏幕滑动距离转换为直线移动距离
    // 数值转换有3个阶段，屏幕操作滑动距离 -> 真实移动距离(模拟现实移动) -> 各个移动轴的像素距离
    float moveDistance = swipeDistance / self.swipeDistancePerMoveDistance;
    
    // 减少医生与病人的距离
    [self addDistanceOfPatientAndDoctor:-moveDistance];
    
    [self.bgLayer goForwardWithDistance:moveDistance];
    
/*    
    // 正在移动中，退出
    if (self.isMoving == YES) {
        return;
    }
    
    
    // 如果不是站立，进行移动
    if (self.patientStatus != PATIENT_STATUS_STAND) {
        self.isMoving = YES;
        float moveTime = 0.0f;
        if (self.patientStatus == PATIENT_STATUS_WALK) {
            moveTime = self.walkTimePerStep;
        } else if (self.patientStatus == PATIENT_STATUS_RUN) {
            moveTime = self.runTimePerStep;
        }
        
        // 移动动画
        [self.bgLayer goForwardWithDistance:self.stepLength duration:moveTime];
        
        // 运动完成后清除移动标记
        id actDelay = [CCDelayTime actionWithDuration:moveTime];
        id actCallBlockN = [CCCallBlockN actionWithBlock:^(CCNode *node) {
            self.isMoving = NO; 
        }];
        id actSeq = [CCSequence actions:actDelay, actCallBlockN, nil];
        [self runAction:actSeq];
    }
*/
}

/*
// 加速
- (void) speedUp {
    if (self.patientStatus != PATIENT_STATUS_RUN) {
        self.swipeValue++;
    }

    // 满足站到走转化条件
    if (self.patientStatus == PATIENT_STATUS_STAND && self.swipeValue >= self.speedUpToWalk) {
        self.swipeValue = 0;
        self.patientStatus = PATIENT_STATUS_WALK;
    } else if (self.patientStatus == PATIENT_STATUS_WALK && self.swipeValue >= self.speedUpToRun) {
        self.swipeValue = 0;
        self.patientStatus = PATIENT_STATUS_RUN;
    }
}


// 减速
- (void) speedDown {
    if (self.patientStatus != PATIENT_STATUS_STAND) {
        self.swipeValue--;
    }
    
    // 满足跑到走转化条件
    if (self.patientStatus == PATIENT_STATUS_RUN && -self.swipeValue >= self.speedDownToWalk) {
        self.swipeValue = 0;
        self.patientStatus = PATIENT_STATUS_WALK;
    } else if (self.patientStatus == PATIENT_STATUS_WALK && -self.swipeValue >= self.speedDownToStand) {
        self.swipeValue = 0;
        self.patientStatus = PATIENT_STATUS_STAND;
    }
}
*/


// 暂停
- (void) pause {
    
    // 添加暂停层
	GameStagePauseLayer *pauseLayer = [GameStagePauseLayer node];
    pauseLayer.tag = E_TAG_ID_PAUSE_LAYER;
	[self addChild:pauseLayer z:E_Z_ORDER_PAUSE_LAYER];
    
    // 暂停动作
    [[CCDirector sharedDirector] pause];
}


// 取消暂停
- (void) resume {
	
	// 清除暂停层
    [self removeChildByTag:E_TAG_ID_PAUSE_LAYER cleanup:YES];

    // 恢复动作
    [[CCDirector sharedDirector] resume];
}


// 显示配置
- (void) showConfig {
    
    // 添加配置层
	GameStageConfigLayer *configLayer = [GameStageConfigLayer node];
    configLayer.tag = E_TAG_ID_CONFIG_LAYER;
	[self addChild:configLayer z:E_Z_ORDER_CONFIG_LAYER];
    
    // 暂停动作
    [[CCDirector sharedDirector] pause];
}


// 关闭配置
- (void) closeConfig {
	
	// 清除设置层
    [self removeChildByTag:E_TAG_ID_CONFIG_LAYER cleanup:YES];
    
    // 恢复动作
    [[CCDirector sharedDirector] resume];
}


// 显示帮助
- (void) showHelp {
    
    // 添加帮助层
	HelpLayer* helpLayer = [HelpLayer node];
	[self addChild:helpLayer z:E_Z_ORDER_HELP_LAYER];
}


// 进入打击模式
- (void) startAttackMode {
    
    // 设置打击模式标记
    self.attackMode = YES;
    
    // 设置病人动画
    [self patientStay];
    
    // 停止医生运动
    [self.bgLayer.doctor justStand];
    
    // 显示打击光标
    [self showAttackLayer];
}


// 显示打击层
- (void) showAttackLayer {
    
    // 添加打击层
	GameStageAttackLayer *attackLayer = [GameStageAttackLayer node];
    attackLayer.tag = E_TAG_ID_ATTACK_LAYER;
	[self addChild:attackLayer z:E_Z_ORDER_ATTACK_LAYER];
}


// 打击失败
- (void) attackMiss {
    
    // 添加计划任务：医生快速前进
    [self schedule:@selector(doctorRun) interval: 1.0f / 60.0f];
    
    // 清除打击层
    [self removeChildByTag:E_TAG_ID_ATTACK_LAYER cleanup:YES];
}


// 医生跑开，打击失败时的医生行为
- (void) doctorRun {

    // 医生快速跑动
    if (self.bgLayer.doctor.isMoving == NO) {
        self.bgLayer.doctor.isMoving = YES;
        [self.bgLayer.doctor walkWithCallback:self fast:YES];
    }
    
    // 加速
    self.distance += 20.0f;
    
    // 当医生跑到初始距离时，停止计划任务
    if (self.distance > DISTANCE_INIT) {
        
        // 停止计划任务
        [self unschedule:@selector(doctorRun)];
        
        // 解除打击模式
        self.attackMode = NO;
        
        return;
    }
    

}


// 开始移动（移动病人，开始滑动屏幕时）
- (void) patientMoveBegan {
    
    // 设置点滴瓶内的病人动作
    [self.menuLayer.patient run];
}


// 病人停止（吊瓶内的动画）
- (void) patientStay {
    
    // 设置点滴瓶内的病人动作
    [self.menuLayer.patient stay];
}


// 病人急停（吊瓶内的动画）
- (void) patientBrake {
    
    // 设置点滴瓶内的病人动作
    [self.menuLayer.patient brake];
}


// 游戏结束
- (void) gameOverWithGameOverId:(int)gameOverId {
    
    // 防止并发调用
    if (self.isGameOver == YES) {
        return;
    }
    self.isGameOver = YES;
    
    
    // 设置状态，停止游戏操作 -----------------------------------------
    // 停止倒计时
    [self unschedule:@selector(updateCountdown)];
    
    // 停止检查更新（医生运动）
    [self unscheduleUpdate];
    
    
    if (gameOverId == E_GAME_OVER_ID_WIN) {
        
        // 胜利奖励及显示游戏结果
        [self win];
        
    } else if (gameOverId == E_GAME_OVER_ID_LOSE) {
        
        // 显示游戏结果（失败）
        GameStageResultLayer *resultLayer = [self showResult];
        [resultLayer showLose];
        
    } else if (gameOverId == E_GAME_OVER_ID_LOSE_BY_FOUND) {
        
        // 显示游戏结果（被发现）
        GameStageResultLayer *resultLayer = [self showResult];
        [resultLayer showLoseForFound];
    }
}


// 胜利
- (void) win {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 给予金币奖励 ---------------------------------------------------------------------------------------
    // 计算花费时间处于哪一象限，等同于关卡定义中金币的下标
    int index = self.time / (self.timeLimit / 4);
    if (index > 3) {
        index = 3;
    }
    
    // 获取金币奖励数量
    int coinRewardAmount = [self.stageDefinitionDM coinRewardAmountWithStage:delegate.delegateLogic.stage
                                                             difficult:delegate.delegateLogic.difficult
                                                                 index:index];
    
    // 更新存档中的金币数量
    [delegate.delegateLogic addCoins:coinRewardAmount justSave:NO];
    
    
    // 解锁下一关 ---------------------------------------------------------------------------------------
    if (delegate.delegateLogic.stage < STAGE_MAX) {
        int nextStage = delegate.delegateLogic.stage + 1;
        [delegate.delegateLogic.appProfile updateStageLock:NO difficult:delegate.delegateLogic.difficult stage:nextStage];
    }
    
    
    // 解锁新人物 ---------------------------------------------------------------------------------------
    // 如果当前是最后一关，且使用的不是最后一个角色
    if (delegate.delegateLogic.stage == STAGE_MAX && delegate.delegateLogic.patientCharacter < PATIENT_MAX) {
        int nextPatientId = delegate.delegateLogic.patientCharacter + 1;
        [delegate.delegateLogic.appProfile updatePatientLock:NO patientId:nextPatientId];
    }
    
    
    // 保存存档 -----------------------------------------------------------------------------------------
    [delegate.delegateLogic.appProfile save];
    
    
    // 显示游戏结果层
//    GameStageResultLayer *resultLayer = [GameStageResultLayer node];
//    [self addChild:resultLayer z:E_Z_ORDER_RESULT_LAYER];
    GameStageResultLayer *resultLayer = [self showResult];
    [resultLayer showWin];
}


// 显示游戏结果层
- (GameStageResultLayer *) showResult {
    
    // 显示游戏结果层
    GameStageResultLayer *resultLayer = [GameStageResultLayer node];
    [self addChild:resultLayer z:E_Z_ORDER_RESULT_LAYER];
    
    return resultLayer;
}


// 使用道具
- (void) useGoodsWithGoodsId:(int)goodsId {
    AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    
    // 减少道具数量
    [delegate.delegateLogic addGoodsWithGoodsId:goodsId amount:-1];
    
    // 保存存档
    [delegate.delegateLogic.appProfile save];
    
    //TODO 根据道具类型，执行不同的逻辑
    // 打击类道具
    [self.bgLayer attackGoodsAnimationWithGoodsId:goodsId];
}


- (void) dealloc {
    self.bgLayer = nil;
    self.menuLayer = nil;
    
    self.stageDefinitionDM = nil;
    self.patientDefinitionDM = nil;
    self.goodsDefinitionDM = nil;
    self.doctorActionProbabilityDef = nil;
    [super dealloc];
}

@end
