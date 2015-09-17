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
		if (JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity","payGameObject","(I)V"))
		{
			int price = _isBuying_object->getPrice();
			info.env->CallStaticVoidMethod(info.classID, info.methodID, price);
		}
	}

	void Java_org_cocos2dx_cpp_AppActivity_payGameObjectEnd(JNIEnv *env, jobject thiz, jstring coreJ)
	{
		const char *coreC = env->GetStringUTFChars(coreJ, NULL);
		log("buy end:%s",coreC);
		_isBuying_object->buyEnd();
		env->ReleaseStringUTFChars(coreJ, coreC);
	}

}
