/*
 * UCSdkJniHelper.cpp
 *
 *  Created on: 2015-9-16
 *      Author: oceantech02
 */

#include "UCSdkJniHelper.h"

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{

	void payForBuyGameObject(SpecialObject * object)
	{
		_isBuying_object = object;
		JniMethodInfo info;
		if (JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity","payGameObject","(Ljava/lang/String;I)V"))
		{
			int price = _isBuying_object->getPrice();
			std::string c_name = _isBuying_object->getName();
			jstring name = info.env->NewStringUTF(c_name.c_str());
			info.env->CallStaticVoidMethod(info.classID, info.methodID,name,price);
			info.env->DeleteLocalRef(name);
		}
	}

	void Java_org_cocos2dx_cpp_AppActivity_payGameObjectEnd(JNIEnv *env, jobject thiz, jstring coreJ)
	{
		const char *coreC = env->GetStringUTFChars(coreJ, NULL);
		log("buy end:%s",coreC);
		if(_isBuying_object)
		{
			_isBuying_object->buyEnd(coreC);
			_isBuying_object = NULL;
		}
		env->ReleaseStringUTFChars(coreJ, coreC);
	}

	void showAd()
	{
		JniMethodInfo info;
		if (JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity","showAD","()V"))
		{
			info.env->CallStaticVoidMethod(info.classID, info.methodID);
		}
	}

}
