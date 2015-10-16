/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import com.cmcc.security.nativeC;



import android.app.Activity;
import android.app.AlertDialog;
import android.app.Application;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.umeng.mobclickcpp.MobClickCppHelper;

import cn.uc.gamesdk.sa.UCGameSdk;
import cn.uc.gamesdk.sa.activity.UCSdkActivity;
import cn.uc.gamesdk.sa.iface.open.SDKConst;
import cn.uc.gamesdk.sa.iface.open.UCCallbackListener;
import cn.uc.gamesdk.sa.iface.open.UCGameSDKStatusCode;
import cn.uc.paysdk.SDKCore;
import cn.uc.paysdk.face.commons.PayResponse;
import cn.uc.paysdk.face.commons.Response;
import cn.uc.paysdk.face.commons.SDKCallbackListener;
import cn.uc.paysdk.face.commons.SDKError;
import cn.uc.paysdk.face.commons.SDKProtocolKeys;

//Cocos2dxActivity
public class AppActivity extends Cocos2dxActivity {
	private static Handler handler;
	
	private final static int HANDLER_SHOW_ERRORDIALOG = 2;// 显示错误提示对话框
	private final static int HANDLER_FINISH_GAME = 12;// 结束游戏
	public final static int HANDLER_SDK_CALLBACK = 14;// SDK回调
	public final static int HANDLER_LOADING_STEP = 18;// 加载步骤
	public final static int HANDLER_HIDE_LOADING = 19;// 隐藏加载
	private TextView textView;
	
	static private boolean firstTime = true;
	static private Activity ucsdkActivity;
	
	static public native void payGameObjectEnd(String core);
	
	static public void payGameObject(int amount)
	{
		Log.i("hongxing", "pay game object");
		payGameObjectEnd("123");
		
		
//		Intent payIntent = new Intent();
////		payIntent.putExtra(SDKProtocolKeys.CP_ORDER_ID, "" + System.currentTimeMillis());
//		payIntent.putExtra(SDKProtocolKeys.APP_NAME, "Diamond");
//		payIntent.putExtra(SDKProtocolKeys.PRODUCT_NAME, "product_name1");
//		payIntent.putExtra(SDKProtocolKeys.AMOUNT, "2"); // 计费点价格
//		// 如果需要设置服务端通知，可以在此设置订单的通知地址
//		// payIntent.putExtra(SDKProtocolKeys.NOTIFY_URL,"http://10.1.84.183/receiveNotify.jsp");
//		payIntent.putExtra(SDKProtocolKeys.DEBUG_MODE, true);
//		//payIntent.putExtra(SDKProtocolKeys.ATTACH_INFO, "ATTACHINFOtest");
//		//如果支持运营商sdk短代支付，那么需要先判断用户手机号，然后传入相对应的paycode
////		payIntent.putExtra(SDKProtocolKeys.PAY_CODE, getPaycode(getApplicationContext())); // demo现在是写死的paycode，实际需要cp传计费点
//		try {
//			SDKCore.pay(ucsdkActivity, payIntent, new SDKCallbackListener() {
//				@Override
//				public void onSuccessful(int status, Response response) {
//					if (response.getType() == Response.LISTENER_TYPE_INIT) {
//						firstTime = false;
//						Message msg = new Message();
//						msg.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//						handler.sendMessageDelayed(msg, 3000);
//					} else if (response.getType() == Response.LISTENER_TYPE_PAY) {
//					    /*重要：CP必须设置确认结果，告诉CP是否成功收到，不然SDK会不断回调通知CP*/
//                        response.setMessage(Response.OPERATE_SUCCESS_MSG); 
//                        /*重要：CP必须设置确认结果，告诉CP是否成功收到，不然SDK会不断回调通知CP*/
//						Message msg = new Message();
//						msg.what = HANDLER_SDK_CALLBACK;
//						String s = response.getData();
//						if (s != null) {
//							msg.obj = response.getData();
//						}
//						msg.arg1 = response.getStatus();
//						handler.sendMessage(msg);
//					}
//				}
//
//				@Override
//				public void onErrorResponse(SDKError error) {
//					String errorMsg = error.getMessage();
//					if (TextUtils.isEmpty(errorMsg))
//						errorMsg = "SDK occur error!";
//					Message msg = new Message();
//					msg.what = HANDLER_SHOW_ERRORDIALOG;
//					msg.obj = errorMsg;
//					handler.sendMessage(msg);
//					if (firstTime) {
//						firstTime = false;
//						msg = new Message();
//						msg.what = FlashMsg.HANDLER_END_LOGO_MSG1;
//						handler.sendMessageDelayed(msg, 3000);
//					}
//				}
//			});
//		} catch (Exception ex) {
//			ex.printStackTrace();
//		}
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		Application application = this.getApplication();
		SDKCore.registerEnvironment(application);
		Log.i("hongxing", "app activity onCreate");
		MobClickCppHelper.init(this);
		
		ucsdkActivity = this;
		
		initHandler();
		initSdk();
		
	}
	static {
        MobClickCppHelper.loadLibrary();
    }
	private void initSdk()
	{
		UCGameSdk.defaultSdk().setCallback(SDKConst.PAY_INIT_LISTENER, new SDKCallbackListener() {
			
			@Override
			public void onSuccessful(int statusCode, Response response)
			{
				Log.i("hongxing", "pay init success");
				if(response.getType() == Response.LISTENER_TYPE_INIT)
				{
					Toast.makeText(AppActivity.this, "支付初始化成功啦!", Toast.LENGTH_LONG).show();
				}else if (response.getType() == Response.LISTENER_TYPE_PAY)
				{
					response.setMessage(Response.OPERATE_SUCCESS_MSG);
					try {
						JSONObject data = new JSONObject(response.getData());
						String orderId = data.getString(PayResponse.CP_ORDER_ID); // CP订单号
						String tradeId = data.getString(PayResponse.TRADE_ID); // 交易号
						String payMoney = data.getString(PayResponse.PAY_MONEY); // 支付金额
						String payType = data.getString(PayResponse.PAY_TYPE); // 支付类型
						                                                       // [207:支付宝快捷支付]
						String orderStatus = data.getString(PayResponse.ORDER_STATUS); // 订单状态
						                                                               // [00:成功][01:失败]
						String orderFinishTime = data.getString(PayResponse.ORDER_FINISH_TIME); // 订单完成时间
						String productName = data.getString(PayResponse.PRO_NAME);// 道具名称
						String extendInfo = data.optString(PayResponse.EXT_INFO); // 商品扩展信息
						String attachInfo = data.optString(PayResponse.ATTACH_INFO); // 附加透传信息
						
					} catch (JSONException ex) {
						ex.printStackTrace();
					}
				}
				
			}
			
			@Override
			public void onErrorResponse(SDKError error) 
			{
				String msg = error.getMessage();
                if (TextUtils.isEmpty(msg)) {
					msg = "SDK occur error!";
				}
				Message message = new Message();
				message.what = HANDLER_SHOW_ERRORDIALOG;
				message.obj = msg;
				handler.sendMessage(message);
				
			}
		});
		UCGameSdk.defaultSdk().setCallback(SDKConst.SDK_INIT_LISTENER, new UCCallbackListener<String>() {
			@Override
			public void callback(int statuscode, String msg) 
			{
				switch (statuscode) {
				case UCGameSDKStatusCode.SUCCESS: {
					Log.i("hongxing", "sdk init success");
					firstTime = false;
					Message message = new Message();
					message.what = FlashMsg.HANDLER_END_LOGO_MSG1;
					handler.sendMessageDelayed(message, 3000);
				}
					break;
				default: {
					if (TextUtils.isEmpty(msg)) {
						msg = "SDK occur error!";
					}
					Message message = new Message();
					message.what = HANDLER_SHOW_ERRORDIALOG;
					message.obj = msg;
					handler.sendMessage(message);
					if (firstTime) {
						firstTime = false;
						message = new Message();
						message.what = FlashMsg.HANDLER_END_LOGO_MSG1;
						handler.sendMessageDelayed(message, 3000);
					}
				}
					break;
				}
			}
			
		});
		
		try {
			Bundle payInitData = new Bundle();
			payInitData.putString(SDKProtocolKeys.APP_ID, "300008973569");
			payInitData.putString(SDKProtocolKeys.APP_KEY, "044B0F69808C6151552A90ACF757A323");
			UCGameSdk.defaultSdk().init(this, payInitData);
		} catch (Exception e) {

		}
	}
	private void initHandler() {
		handler = new Handler() {
			public void handleMessage(Message msg) {
				switch (msg.what) {
		
				case HANDLER_SHOW_ERRORDIALOG:
				case HANDLER_SDK_CALLBACK: {
					String message = (String) msg.obj;
					if (TextUtils.isEmpty(message)) 
						message = "unknown";
										
					AlertDialog.Builder builder = new Builder(AppActivity.this);
					builder.setTitle("Tips");
					builder.setMessage(message);
					
					builder.setPositiveButton("ok", new DialogInterface.OnClickListener() {
						@Override
						public void onClick(DialogInterface arg, int arg1) {
						}
					});
					builder.create().show();
					break;
					}

				case HANDLER_FINISH_GAME:
					finishGame((String) msg.obj);
					break;

				case HANDLER_LOADING_STEP:
//					setLoadingAnimation(msg.arg1);
					break;
				case HANDLER_HIDE_LOADING:
//					if (loadingLayout != null) {
//						stop = true;
//						loadingLayout.setVisibility(View.GONE);
//						loadingLayout.invalidate();
//					}
					break;
//				case FlashMsg.HANDLER_UPDATE_LOGO_MSG:
//					flash.updateLogoMsg(msg.arg1);
//					break;
//				case FlashMsg.HANDLER_END_LOGO_MSG:
//					flash.endMsg();
//					break;
//				case FlashMsg.HANDLER_END_LOGO_MSG1:
//					showAnyKeyContinue1();
//					((TextView) root.findViewById(R.id.tv_items)).setText("0");
//					((TextView) root.findViewById(R.id.tv_coins)).setText("0");
//					break;
				}
			}
		};
	}
	
	private void finishGame(String url) {
		finish();
	}
	
	@Override
	protected void onPause()
	{
		super.onPause();
		
		Log.i("hongxing", "app activity onPause");
	}

	@Override
	protected void onResume() 
	{
		super.onResume();
		
		Log.i("hongxing", "app activity onResume");
	}

	@Override
    protected void onDestroy()
	{
		Log.i("hongxing", "app activity onDestroy");
	    // 退出释放资源
        SDKCore.exitSDK(this);
        UCGameSdk.defaultSdk().exit(null);
        super.onDestroy();
    }
	
}