LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/BaseUtil.cpp \
				   ../../Classes/Bullet.cpp \
				   ../../Classes/BulletManager.cpp \
				   ../../Classes/BulletSprite.cpp \
				   ../../Classes/CCCsvHelper.cpp \
				   ../../Classes/ConfigManager.cpp \
				   ../../Classes/CrumpEnemySprite.cpp \
				   ../../Classes/DefenseBuilding.cpp \
				   ../../Classes/DefenseBuilding1_Sprite.cpp \
				   ../../Classes/DefenseBuilding2_Sprite.cpp \
				   ../../Classes/DefenseBuilding3_Sprite.cpp \
				   ../../Classes/DefenseBuilding4_Sprite.cpp \
				   ../../Classes/DefenseBuildingManager.cpp \
				   ../../Classes/DefenseBuildingSprite.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/EnemyGroup.cpp \
				   ../../Classes/EnemyInfo.cpp \
				   ../../Classes/EnemyManager.cpp \
				   ../../Classes/EnemyProgressBar.cpp \
				   ../../Classes/EnemySprite.cpp \
				   ../../Classes/FlyEnemy.cpp \
				   ../../Classes/FlyEnemySprite.cpp \
				   ../../Classes/GameBuff.cpp \
				   ../../Classes/GameBuffManager.cpp \
				   ../../Classes/GameDirector.cpp \
				   ../../Classes/GameFightScene.cpp \
				   ../../Classes/GameHorizontalScrollHeadlerView.cpp \
				   ../../Classes/GameHorizontalScrollView.cpp \
				   ../../Classes/GameLoading.cpp \
				   ../../Classes/GameMap.cpp \
				   ../../Classes/GameMap5s.cpp \
				   ../../Classes/GameMap6.cpp \
				   ../../Classes/GameMapManager.cpp \
				   ../../Classes/GameMapScene.cpp \
				   ../../Classes/GameObject.cpp \
				   ../../Classes/GameObserver.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/GamePauseScene.cpp \
				   ../../Classes/GameScrollHeadler.cpp \
				   ../../Classes/GameScrollHeadlerView.cpp \
				   ../../Classes/GameScrollView.cpp \
				   ../../Classes/GameShopScene.cpp \
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
				   ../../Classes/HumanWaitState.cpp \
				   ../../Classes/MapGuanqiaButton.cpp \
				   ../../Classes/MapScrollHeadler.cpp \
				   ../../Classes/ProgressBar.cpp \
				   ../../Classes/Prop.cpp \
				   ../../Classes/PropManager.cpp \
				   ../../Classes/ScrollController.cpp \
				   ../../Classes/SelectMenuController.cpp \
				   ../../Classes/SelectMenuView.cpp \
				   ../../Classes/ShopAwardItemScrollHeadler.cpp \
				   ../../Classes/ShopBuildingItemScrollHeadler.cpp \
				   ../../Classes/ShopGunIcon.cpp \
				   ../../Classes/ShopGunItemScrollHeadler.cpp \
				   ../../Classes/ShopItemScrollHeadler.cpp \
				   ../../Classes/ShopPropIcon.cpp \
				   ../../Classes/ShopPropItemScrollHeadler.cpp \
				   ../../Classes/ShopSelectMenuView.cpp \
				   ../../Classes/State.cpp \
				   ../../Classes/WalkEnemy.cpp \
				   ../../Classes/WalkEnemySprite.cpp \
				   ../../Classes/json/json_reader.cpp \
				   ../../Classes/json/json_value.cpp \
				   ../../Classes/json/json_writer.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
