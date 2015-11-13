//
//  DelegateLogic.m
//  YohoYoho
//
//  Created by  on 12-2-16.
//  Copyright (c) 2012年 Leon.Young. All rights reserved.
//

#import "DelegateLogic.h"
#import "AppProfile.h"
#import "GameConfig.h"
#import "SimpleAudioEngine.h"
#import "TitleScene.h"
#import "StoryScene.h"
#import "SelectModeScene.h"
#import "PatientModeSelectCharacterScene.h"
#import "SelectDifficultScene.h"
#import "CharacterStoryScene.h"
#import "MapScene.h"
#import "GameStageScene.h"


@implementation DelegateLogic

@synthesize gameMode = gameMode_;
@synthesize patientCharacter = patientCharacter_;
@synthesize difficult = difficult_;
@synthesize stage = stage_;
@synthesize appProfile = appProfile_;


- (id) init {
    if (self = [super init]) {
        
        // 初始化存档
        self.appProfile = [[[AppProfile alloc] initWithFileName:PROFILE_NAME] autorelease];

        // 设置音量
        [self checkBgm];
        [self checkSe];
        
        // TEST
//        CCLOG(@"%@", self.appProfile.profile);
        
        [self.appProfile updatePatientLock:NO patientId:2];
        [self.appProfile updatePatientLock:NO patientId:3];
        [self.appProfile updatePatientLock:NO patientId:4];
        
        [self.appProfile updateStageLock:NO difficult:1 stage:3];
        [self.appProfile updateStageLock:NO difficult:2 stage:3];
        [self.appProfile updateStageLock:NO difficult:3 stage:3];
        
        [self.appProfile updateStageLock:NO difficult:1 stage:4];
        [self.appProfile updateStageLock:NO difficult:2 stage:4];
        [self.appProfile updateStageLock:NO difficult:3 stage:4];
//        [self.appProfile updateGoodsWithAmount:5 goodsId:1];
//        [self.appProfile updateGoodsWithAmount:3 goodsId:2];
        [self.appProfile save];
//        CCLOG(@"%@", self.appProfile.profile);
    }

    return self;
}


// 检查BGM开关
- (void) checkBgm {
    
    // 音量大小
    float bgmVolume = 0.0f;
    if ([self.appProfile bgm] == YES) {
        bgmVolume = 1.0f;
    }
    
    // 设置BGM音量
    [[SimpleAudioEngine sharedEngine] setBackgroundMusicVolume:bgmVolume];
}


// 检查SE开关
- (void) checkSe {
    
    // 音量大小
    float seVolume = 0.0f;
    if ([self.appProfile se] == YES) {
        seVolume = 1.0f;
    }
    
    // 设置SE音量
    [[SimpleAudioEngine sharedEngine] setEffectsVolume:seVolume];
}


// 跳转到标题场景
- (void) goToTitleScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[TitleScene scene]];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到故事场景
- (void) goToStoryScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[StoryScene scene]];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到选择模式场景
- (void) goToSelectModeScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
//    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[SelectModeScene scene]];
    id scene = [SelectModeScene scene];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到病人模式选择人物场景
- (void) goToPatientModeSelectCharacterScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
//    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[PatientModeSelectCharacterScene scene]];
    id scene = [PatientModeSelectCharacterScene scene];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到选择难度场景
- (void) goToSelectDifficultScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
//    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[SelectDifficultScene scene]];
    id scene = [SelectDifficultScene scene];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到个人剧情场景
- (void) goToCharacterStoryScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[CharacterStoryScene scene]];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到地图场景
- (void) goToMapScene {
    
    // 释放内存
    [[CCDirector sharedDirector] purgeCachedData];
    
    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[MapScene scene]];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 跳转到游戏场景
- (void) goToGameStageScene {
    
    // 释放内存
    [[CCSpriteFrameCache sharedSpriteFrameCache] removeUnusedSpriteFrames];
    [[CCDirector sharedDirector] purgeCachedData];
    
    id scene = [CCTransitionFade transitionWithDuration:0.5 scene:[GameStageScene scene]];
    [[CCDirector sharedDirector] replaceScene: scene];
}


// 增加或减少金币数量
- (int) addCoins:(int)amount justSave:(BOOL)justSave {
	int currentAmount = [self.appProfile coins];		// 当前的点数
	
	if (amount + currentAmount >= 0) {
		currentAmount += amount;
		
		// 更新存档对象
        [self.appProfile updateCoins:currentAmount];
		
		if (justSave == YES) {
			[self.appProfile save];
		}
	}
	
	return currentAmount;
}


// 设置BGM
- (void) updateBgm:(BOOL)bgm {
    
    // 设置存档
    [self.appProfile updateBgm:bgm];
    
    // 保存存档
    [self.appProfile save];
    
    // 设置声音
    [self checkBgm];
}


// 设置SE
- (void) updateSe:(BOOL)se {
    
    // 设置存档
    [self.appProfile updateSe:se];
    
    // 保存存档
    [self.appProfile save];
    
    // 设置声音
    [self checkSe];
}


// 增加或减少道具数量
- (void) addGoodsWithGoodsId:(int)goodsId
                      amount:(int)amount {
    
    int currentAmount = [self.appProfile goodsAmountWithGoodsId:goodsId];		// 当前的点数
	
    int balanceAmount = amount + currentAmount;
	if (balanceAmount > 0) {
        
        // 更新道具
        [self.appProfile updateGoodsWithAmount:balanceAmount goodsId:goodsId];

	} else if (balanceAmount == 0) {
        
        // 删除道具
        [self.appProfile deleteGoodsWithGoodsId:goodsId];
    }
}


- (void)dealloc {
    self.appProfile = nil;
    [super dealloc];
}

@end
