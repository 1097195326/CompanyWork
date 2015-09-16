package org.cocos2dx.cpp;

import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

/**
 * 显示在启动界面中的闪烁按钮
 * 
 * @author panzx
 * 
 */
public class FlashMsg {

	public final static int HANDLER_UPDATE_LOGO_MSG = 20000;
	public final static int HANDLER_END_LOGO_MSG = 20001;
	public final static int HANDLER_END_LOGO_MSG1 = 20002;
	private ImageView logoMsg;
	private LogoMsgThread logoMsgThread;
	private boolean logoRunning;

	private Handler handler;

	public FlashMsg(ImageView logoMsg, Handler handler) {
		this.logoMsg = logoMsg;
		this.handler = handler;
	}

	/**
	 * 结束消息动画
	 */
	public void endMsg() {
		Log.i("FlashMsg", " end msg---------------");
		logoRunning = false;
		logoMsgThread = null;
	}

	/**
	 * 开始动画
	 */
	public void startMsg() {
		if (logoMsg.getVisibility() != View.VISIBLE) {
			logoMsg.setVisibility(View.VISIBLE);
		}
		if (!logoRunning) {
			logoMsgThread = new LogoMsgThread();
			logoMsgThread.start();
		}
	}

	/**
	 * 刷新“按任意键继续”动画显示线程
	 */
	private class LogoMsgThread extends Thread {

		@Override
		public void run() {

			logoRunning = true;
			boolean visible = true;
			double sleepInterval = 0.5;
			while (logoRunning) {
				sleepInterval = visible ? 0.5 : 0.2;
				try {
					Thread.sleep((long) (1000 * sleepInterval));
				} catch (Exception e) {
					e.printStackTrace();
				}
				Message msg = new Message();
				msg.what = HANDLER_UPDATE_LOGO_MSG;
				msg.arg1 = visible ? View.INVISIBLE : View.VISIBLE;
				handler.sendMessage(msg);
				visible = !visible;

			}
		}
	}

	/**
	 * 更新“按任意键继续”动画
	 * 
	 * @param step
	 */
	public void updateLogoMsg(int visibility) {
		if (logoMsg != null) {
			logoMsg.setVisibility(visibility);
		}
	}
}
