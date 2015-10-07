LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AlertTextTool.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/BaseUtil.cpp \
				   ../../Classes/BuffSprite.cpp \
				   ../../Classes/Bullet.cpp \
				   ../../Classes/BulletManager.cpp \
				   ../../Classes/BulletModel.cpp \
				   ../../Classes/BulletSprite.cpp \
				   ../../Classes/CCCsvHelper.cpp \
				   ../../Classes/ConfigManager.cpp \
				   ../../Classes/CrumpEnemySprite.cpp \
				   ../../Classes/CurveBullet.cpp \
				   ../../Classes/DefenseBuilding.cpp \
				   ../../Classes/DefenseBuilding1_Sprite.cpp \
				   ../../Classes/DefenseBuilding1.cpp \
				   ../../Classes/DefenseBuilding2_Sprite.cpp \
				   ../../Classes/DefenseBuilding2.cpp \
				   ../../Classes/DefenseBuilding3_Sprite.cpp \
				   ../../Classes/DefenseBuilding3.cpp \
				   ../../Classes/DefenseBuilding4_Sprite.cpp \
				   ../../Classes/DefenseBuilding4.cpp \
				   ../../Classes/DefenseBuilding6_Sprite.cpp \
				   ../../Classes/DefenseBuilding7_Sprite.cpp \
				   ../../Classes/DefenseBuildingManager.cpp \
				   ../../Classes/DefenseBuildingSprite.cpp \
				   ../../Classes/DropManager.cpp \
				   ../../Classes/DropModel.cpp \
				   ../../Classes/DropMoneySprite.cpp \
				   ../../Classes/DropPropSprite.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/EnemyGroup.cpp \
				   ../../Classes/EnemyInfo.cpp \
				   ../../Classes/EnemyManager.cpp \
				   ../../Classes/EnemyProgressBar.cpp \
				   ../../Classes/EnemySprite.cpp \
				   ../../Classes/ExpendObject.cpp \
				   ../../Classes/FireBulletSprite.cpp \
				   ../../Classes/FlyEnemy.cpp \
				   ../../Classes/FlyEnemySprite.cpp \
				   ../../Classes/GameBuff.cpp \
				   ../../Classes/GameBuffManager.cpp \
				   ../../Classes/GameCgShowScene.cpp \
				   ../../Classes/GameDirector.cpp \
				   ../../Classes/GameFightScene.cpp \
				   ../../Classes/GameHomeScene.cpp \
				   ../../Classes/GameHorizontalScrollHeadlerView.cpp \
				   ../../Classes/GameHorizontalScrollView.cpp \
				   ../../Classes/GameLoading.cpp \
				   ../../Classes/GameLoadingScene.cpp \
				   ../../Classes/GameMap.cpp \
				   ../../Classes/GameMap5s.cpp \
				   ../../Classes/GameMap6.cpp \
				   ../../Classes/GameMapManager.cpp \
				   ../../Classes/GameMapScene.cpp \
				   ../../Classes/GameObject.cpp \
				   ../../Classes/GameObserver.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/GamePauseScene.cpp \
				   ../../Classes/GameReliveLayer.cpp \
				   ../../Classes/GameScrollHeadler.cpp \
				   ../../Classes/GameScrollHeadlerView.cpp \
				   ../../Classes/GameScrollView.cpp \
				   ../../Classes/GameShopScene.cpp \
				   ../../Classes/GameShowDiscLayer.cpp \
				   ../../Classes/GameShowLevelupLayer.cpp \
				   ../../Classes/GameSprite.cpp \
				   ../../Classes/GameSubject.cpp \
				   ../../Classes/GameUser.cpp \
				   ../../Classes/GameVerticalScrollHeadlerView.cpp \
				   ../../Classes/GameVerticalScrollView.cpp \
				   ../../Classes/GuanQiaManager.cpp \
				   ../../Classes/GuanQiaModel.cpp \
				   ../../Classes/Gun.cpp \
				   ../../Classes/GunManager.cpp \
				   ../../Classes/GunSprite.cpp \
				   ../../Classes/House.cpp \
				   ../../Classes/HouseSprite.cpp \
				   ../../Classes/Human.cpp \
				   ../../Classes/HumanChangeState.cpp \
				   ../../Classes/HumanReloadState.cpp \
				   ../../Classes/HumanShootState.cpp \
				   ../../Classes/HumanSprite.cpp \
				   ../../Classes/HumanThrowPropState.cpp \
				   ../../Classes/HumanWaitState.cpp \
				   ../../Classes/LiquidBullet.cpp \
				   ../../Classes/MapGuanqiaButton.cpp \
				   ../../Classes/MapScrollHeadler.cpp \
				   ../../Classes/MoneyManager.cpp \
				   ../../Classes/MoneyObject.cpp \
				   ../../Classes/ProgressBar.cpp \
				   ../../Classes/Prop.cpp \
				   ../../Classes/PropManager.cpp \
				   ../../Classes/PropSprite_daoju1.cpp \
				   ../../Classes/PropSprite_daoju2.cpp \
				   ../../Classes/PropSprite_daoju3.cpp \
				   ../../Classes/PropSprite_daoju5.cpp \
				   ../../Classes/PropSprite_daoju6.cpp \
				   ../../Classes/PropSprite_daoju7.cpp \
				   ../../Classes/PropSprite_daoju8.cpp \
				   ../../Classes/PropSprite_daoju9.cpp \
				   ../../Classes/PropSprite.cpp \
				   ../../Classes/PropSpriteView.cpp \
				   ../../Classes/PunctureBullet.cpp \
				   ../../Classes/ScrollController.cpp \
				   ../../Classes/SelectMenuController.cpp \
				   ../../Classes/SelectMenuView.cpp \
				   ../../Classes/ShopAwardItemScrollHeadler.cpp \
				   ../../Classes/ShopBuildingItemScrollHeadler.cpp \
				   ../../Classes/ShopExpendShowLayer.cpp \
				   ../../Classes/ShopGoldShowLayer.cpp \
				   ../../Classes/ShopGunIcon.cpp \
				   ../../Classes/ShopGunItemScrollHeadler.cpp \
				   ../../Classes/ShopHealthShowLayer.cpp \
				   ../../Classes/ShopPropIcon.cpp \
				   ../../Classes/ShopPropItemScrollHeadler.cpp \
				   ../../Classes/ShopSelectMenuView.cpp \
				   ../../Classes/SpecialManager.cpp \
				   ../../Classes/SpecialObject.cpp \
				   ../../Classes/State.cpp \
				   ../../Classes/UserDelegatLayer.cpp \
				   ../../Classes/WalkEnemy.cpp \
				   ../../Classes/WalkEnemySprite.cpp \
				   ../../Classes/json/json_reader.cpp \
				   ../../Classes/json/json_value.cpp \
				   ../../Classes/json/json_writer.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_SHARED_LIBRARIES := mobclickcpp_shared

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,libmobclickcpp)
