/*
 * UCSdkJniHelper.h
 *
 *  Created on: 2015-9-16
 *      Author: oceantech02
 */

#ifndef UCSDKJNIHELPER_H_
#define UCSDKJNIHELPER_H_

#include "../../Classes/SpecialObject.h"

extern "C"
{

	static SpecialObject * _isBuying_object = NULL;

	void payForBuyGameObject(SpecialObject * object);

	void showAd();


}

#endif /* UCSDKJNIHELPER_H_ */
