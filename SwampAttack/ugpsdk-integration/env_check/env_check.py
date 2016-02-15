#encoding:utf-8
#===============================================================================================
#作用：检查支付配置是否正确。
#使用方式：将脚本放在与工程AndroidManifest.xml同级目录下，在命令行调用'python env_check.py'即可。
#    如果支付配置有误，脚本会给出错误详情；如果配置成功，则提示'检查配置成功，通过检查！'
#作者：九游支付
#===============================================================================================

import os
import sys
import optparse
from string import Template



#指定工程lib目录
PROJECT_LIBS_PATH = '../ugpsdk-integration/libs'
#None表示即本工程的lib目录
#PROJECT_LIBS_PATH = None
#当前目录
CWD = os.getcwd()
#AndroidManifest.xml文件名
AM_FILE_NAME = 'AndroidManifest.xml'
#AndroidManifest.xml文件结构
#<manifest>
#--<application>
#----<activity>
#----</activity>
#----#or-service/receiver/...
#--</application>
#--<uses-permission>
#--</uses-permission>
#</manifest>

#AndroidManifest.xml中的属性关键字
XMLNS_PREFIX = '{http://schemas.android.com/apk/res/android}'
NAME = XMLNS_PREFIX + 'name'


#AndroidManifest.xml匹配模板
AM_TEMPLATE_PREFIX = \
'''
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="$PACKAGE_NAME">

    <application>

        <activity
            android:name="cn.uc.paysdk.SDKActivity"
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:theme="@android:style/Theme.Translucent.NoTitleBar">
        </activity>

        <service android:name="cn.uc.paysdk.service.SDKService" >
        </service>
        
        <activity android:name="cn.uc.gamesdk.sa.activity.ProxyActivity" 
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:label="@string/app_name"
            android:theme="@android:style/Theme.Translucent.NoTitleBar"
            android:windowSoftInputMode="adjustResize" >

            <intent-filter>
                <action android:name="cn.uc.gamesdk.sdkweb" />

                <category android:name="android.intent.category.DEFAULT" />
            </intent-filter>
        </activity>
        
        <!-- From SDK 1.4.0 for crash log-->
        <service android:name="com.uc.crashsdk.CrashLogFilesUploader"
           android:process=":TProcess">
        </service>
        <!-- From SDK 1.4.0 for crash log-->
'''

ALIPAY = \
'''
        <activity
            android:name="com.alipay.sdk.app.H5PayActivity"
            android:configChanges="orientation|keyboardHidden|navigation"
            android:exported="false"
            android:screenOrientation="behind" >
        </activity>
        <activity
            android:name="com.alipay.sdk.auth.AuthActivity"
            android:configChanges="orientation|keyboardHidden|navigation"
            android:exported="false"
            android:screenOrientation="behind" >
        </activity>
'''

NOW_PAY = \
'''
       <!-- now 微信SDK支付相关添加开始 -->
		<activity
            android:name="com.ipaynow.plugin.activity.PayMethodActivity"
            android:theme="@android:style/Theme.Dialog"
            android:configChanges="orientation|keyboardHidden|screenSize"
            android:exported="false"
            android:screenOrientation="unspecified">
        </activity>
        <activity
            android:name="com.ipaynow.plugin.inner_plugin.wechat_plugin.activity.WeChatNotifyActivity"
            android:theme="@android:style/Theme.NoDisplay"
            android:configChanges="orientation|keyboardHidden|screenSize">
        </activity>
        <!-- now 微信SDK支付相关添加结束 -->
'''

THREE_OPERATOR_SDK_CT = \
'''
        <!-- 中国电信SDK支付相關添加开始 -->
        <!-- 中国电信渠道号 :需要根据实际修改-->
        <meta-data android:name="EGAME_CHANNEL" android:value="10000000"/>
        <meta-data android:name="EGAME_UNINS" android:value="false"/>
        <meta-data android:name="EGAME_ALIPAY" android:value="false"/>
        <meta-data android:name="EGAME_UNIPAY" android:value="false"/>
		<meta-data android:name="EGAME_NOWWECHATPAY" android:value="false" />

        <!-- 根据游戏实际情况修改screenOrientation属性 -->
        <activity
            android:name="cn.egame.terminal.paysdk.EgamePayActivity"
            android:configChanges="orientation|keyboardHidden|screenSize"
            android:screenOrientation="unspecified"
            android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" >
        </activity>

        <receiver android:name="cn.egame.terminal.sdk.EgameCoreReceiver" >
            <intent-filter android:priority="1001" >
                <action android:name="android.intent.action.USER_PRESENT" />
                <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
                <category android:name="android.intent.category.DEFAULT" />
            </intent-filter>
            <intent-filter>
                <action android:name="android.intent.action.PACKAGE_ADDED" />
                <action android:name="android.intent.action.PACKAGE_REMOVED" />
                <data android:scheme="package" />
            </intent-filter>
            <intent-filter>
                <action android:name="cn.egame.terminal.sdk.RECEIVER_CMD" />
                <category android:name="android.intent.category.DEFAULT" />
            </intent-filter>
        </receiver>

        <service
            android:name="cn.egame.terminal.sdk.EgameCoreService"
            android:process=":egameCore" >
            <intent-filter>
                <action android:name="cn.egame.terminal.sdk.SERVICE_CMD" />
                <category android:name="android.intent.category.DEFAULT" />
            </intent-filter>
        </service>

		<!-- 根据游戏实际情况修改screenOrientation属性 -->
        <activity
            android:name="cn.egame.terminal.sdk.EgameCoreActivity"
            android:configChanges="screenSize|keyboardHidden|orientation"
            android:process=":egameCore"
            android:screenOrientation="behind"
            android:taskAffinity=":egameCore"
            android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
             <intent-filter>
                <action android:name="android.intent.action.MAIN" />
            </intent-filter>
        </activity>
		<!-- 中国电信SDK支付相關添加结束 -->
'''

THREE_OPERATOR_SDK_CU = \
'''
		<!-- 中国联通SDK支付相關添加开始 -->
		<service android:name="com.unicom.wostore.unipay.paysecurity.SecurityServiceFramework"/>
		<service  android:name="com.unicom.wostore.unipay.paysecurity.UpdateService"
		    android:process=":unicomuptsrv"/>
		<activity
		    android:name="com.unicom.wostore.unipay.paysecurity.SecurityActivity"
			android:theme="@android:style/Theme.Light.NoTitleBar.Fullscreen"
			android:configChanges="screenSize|orientation">
		</activity>

		<meta-data android:name="wostore_billing_otherpay" android:value="false"/>
		<meta-data android:name="wostore_billing_chinaunicom" android:value="true"/>
		<meta-data android:name="wostore_billing_chinamobile"  android:value="false" />
		<meta-data android:name="wostore_billing_chinatele"  android:value="false" />
		<!-- 中国联通SDK支付相關添加结束 -->

'''

LIBS_JARS_ALIPAY = [
  'alipaySdk-20151215.jar',
]
LIBS_JARS_NOW_WECHAT = [
  'ipaynow_plugin_phone_onlywechat_v1.3.1.jar',
]
LIBS_JARS_OPCM_MM = [
  'mmbilling.3.1.9.jar',
]
LIBS_JARS_OPCU = [
  'Multimode_UniPay_base.jar',
  'Multimode_UniPay_payinfo.jar',
]

LIBS_JARS_OPCT = [
  'egame.log_20151109_out_release.jar',
  'cn.egame.terminal.paysdk.jar',
]

LIBS_SO = [
  'x86/libbreakpad.so',
  'armeabi/libbreakpad.so',
]
LIBS_SO_NOW_WECHAT = [
  'x86/libplugin_phone.so',
  'armeabi/libplugin_phone.so',
]
LIBS_SO_OPCM_BASE = [
  'x86/libmegjb.so',
  'armeabi/libmegjb.so',
]

LIBS_SO_OPCT = [
  'x86/libegamepay_dr2.so',
  'armeabi/libegamepay_dr2.so',
]

LIBS_SO_OPCM_MM = [
  'x86/libcasdkjni.so',
  'x86/libcmcc_haze.so',
  'x86/libcmcc_rusteze.so',
  'x86/libDexHelper_mmb.so',
  'x86/libidentifyapp.so',
  'x86/libumc-auth.so',
  'armeabi/libcasdkjni.so',
  'armeabi/libcmcc_haze.so',
  'armeabi/libcmcc_rusteze.so',
  'armeabi/libDexHelper_mmb.so',
  'armeabi/libidentifyapp.so',
  'armeabi/libumc-auth.so',
]


SDK_CHECK_FILES = [
  'assets/UCPaySDK/pay.png',#权限验证文件
  'assets/UCGameInfo.ini',#GameInfo文件
]

THREE_OPERATOR_FILES_CM_BASE = [
  'assets/ConsumeCodeInfo.xml',
  'assets/Charge.xml',
  'assets/d_data_store.dat.x86',
  'assets/libmegbpp_03.01.00_00.so.x86',
  'assets/AndGame.Sdk.Lib_20150_86098B59D437DE14494674358197AAEA.dat',
  'assets/libmegbpp_03.01.00_00.so',
  'assets/Config.xml',
  'assets/c_data_store.dat',
  'assets/CMGC/ConfigExtend.xml',
  'assets/d_data_store.dat',
]

#EGAME文件，后续有可能校验，目前不用校验
THREE_OPERATOR_FILES_CT = [
  'assets/egame/EGAME_116.zip',
  'assets/egame/EPSH_123.zip',
  'assets/feeInfo.dat',#中国电信计费文件
]

AM_TEMPLATE_SUFFIX = \
'''
    <!-- 支付SDK内部权限添加开始 -->
    <uses-permission android:name="android.permission.INTERNET" />
	<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
	<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
	<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
	<uses-permission android:name="android.permission.READ_PHONE_STATE" />
	<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
	<uses-permission android:name="android.permission.SEND_SMS" />
	<uses-permission android:name="android.permission.GET_TASKS" />
	<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
	<uses-permission android:name="android.permission.VIBRATE" />
	<uses-permission android:name="android.permission.AUTHENTICATE_ACCOUNTS" />
	<uses-permission android:name="android.permission.GET_ACCOUNTS" />
	<uses-permission android:name="android.permission.USE_CREDENTIALS" />
	<uses-permission android:name="android.webkit.permission.PLUGIN" />
	<uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />

'''


AM_TEMPLATE_SUFFIX_OP = \
'''
    <uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS" />
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
    <uses-permission android:name="android.permission.GET_PACKAGE_SIZE" />
    <uses-permission android:name="android.permission.WRITE_SETTINGS" />
'''

AM_TEMPLATE_SUFFIX_HEAD = \
'''</application>
'''

AM_TEMPLATE_SUFFIX_TAIL = \
'''</manifest>
'''

PATH_NAME_CHECK_LIST = [
  (os.path.join('manifest', 'application', 'meta-data'), 'EGAME_CHANNEL'),
]

def Log(content):
  '输出日志'
  import platform
  if content:
    if sys.version_info < (3, 0) and platform.system() == 'Windows':
      print (content.decode('utf-8').encode('gbk'))
    else:
      print (content)

def LogTitle(title):
  '输出标题'

  Log('=========================================================================================')
  Log('||'+ title)
  Log('---------------------------------------------')


def ExistFile(file):
  '判断单个文件是否存在'

  Log('检查文件：' + file)
  return os.path.exists(file)

def ExistFileList(files):
  '判断文件列表中所有文件都存在'

  for file in files:
    if not ExistFile(file):
      Log('文件' + file + '不存在!')
      return False
  return True

def CheckFilesConfig():
  '检查工程文件配置是否正确'

  global USE_THREE_OPERATOR
  global PROJECT_LIBS_PATH

  #判断主工程assets目录文件配置
  # 1) SDK配置文件检查
  if not ExistFileList(SDK_CHECK_FILES):
    return False
  # 2) 三大运营商配置检查（如果使用三大运营商)
  if USED_CT:
    if not ExistFileList(THREE_OPERATOR_FILES_CT):
      return False
  if USED_BASE:
    if not ExistFileList(THREE_OPERATOR_FILES_CM_BASE):
      return False

  # 3) 工程libs目录检查
    check_lib = True 
    errorMsg = None
    check_jar = True
    if PROJECT_LIBS_PATH is None:
      PROJECT_LIBS_PATH = './lib'
      errorMsg = '未指定lib目录，尝试使用[' + PROJECT_LIBS_PATH + ']失败，该文件不存在!'
      check_jar = False
    else:
      errorMsg = '指定的lib目录[' + PROJECT_LIBS_PATH + ']不存在!'

    if not ExistFile(PROJECT_LIBS_PATH):
      PROJECT_LIBS_PATH = './libs'
      errorMsg = '未指定lib目录，尝试使用[' + PROJECT_LIBS_PATH + ']失败，该文件不存在!'

    if not ExistFile(PROJECT_LIBS_PATH):
      check_lib = False
      Log(errorMsg)

    if check_lib:
      files = []
      for file in LIBS_SO:
        file = os.path.join(PROJECT_LIBS_PATH, file)
        files.append(file)

      if USED_MM:
        for file in LIBS_SO_OPCM_MM:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_BASE:
        for file in LIBS_SO_OPCM_BASE:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_CT:
        for file in LIBS_SO_OPCT:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)

      if not ExistFileList(files):
        return False

    if check_jar:
      files = []
      if USE_ALIPAY:
        for file in LIBS_JARS_ALIPAY:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_NOW_WECHAT:
        for file in LIBS_JARS_NOW_WECHAT:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_CT:
        for file in LIBS_JARS_OPCT:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_MM:
        for file in LIBS_JARS_OPCM_MM:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)
      if USED_CU:
        for file in LIBS_JARS_OPCU:
          file = os.path.join(PROJECT_LIBS_PATH, file)
          files.append(file)

      if not ExistFileList(files):
        return False
		
  return True

def MatchAttributes(left, right):
  '判断两个节点的所有属性是否都匹配'

  for key in right.keys():
    if key not in left.keys():
      return False

    if left.get(key) != right.get(key):
      #部分属性值顺序可能颠倒，所以如果有"|"分割符，只要包括即可
      if left.get(key).find("|") != -1:
        ret = compareStrContentNotCareOrder(left.get(key), right.get(key), "|")
        continue
      return False
  return True

def MatchElement(left, right):
  '所有子节点的属性也都匹配,且只匹配子节点这一级，而非递归多级匹配'

  # 1) 属性检查
  if not MatchAttributes(left, right):
    return False
  # ) 子节点检查
  for left_child in list(left):
    matched = False
    for right_child in list(right):
      if MatchAttributes(left_child, right_child):
        matched = True 
    if not matched:
      return False
  return True
    

def Get(container, matcher):
  '从container中获取与ｍatcher匹配的节点'

  for ele in container:
    if MatchElement(ele, matcher):
      return ele
  return None 
   
    
def BuildAndroidManifestTemplate():
  '构建AndroidManifest.xml匹配模板'

  global AM_TEMPLATE_PREFIX
  global AM_TEMPLATE_SUFFIX,AM_TEMPLATE_SUFFIX_OP,AM_TEMPLATE_SUFFIX_HEAD,AM_TEMPLATE_SUFFIX_TAIL
  template = AM_TEMPLATE_PREFIX
  if USE_ALIPAY:
    template += ALIPAY
  if USED_NOW_WECHAT:
    template += NOW_PAY
  if USED_CU:
    template += THREE_OPERATOR_SDK_CU
  if USED_CT:
    template += THREE_OPERATOR_SDK_CT

  #...添加其他支付方式相关配置模板
  template += AM_TEMPLATE_SUFFIX_HEAD
  template += AM_TEMPLATE_SUFFIX
  if USE_THREE_OPERATOR:
    template += AM_TEMPLATE_SUFFIX_OP
  template += AM_TEMPLATE_SUFFIX_TAIL
  return template

def CheckElement(tag, path, name, element, matcher):
  '检查某个节点元素是否匹配模板（包括子节点检查)'

  Log('正在检查节点 [path:' + path + '][name:' + name + ']...')
  # special case 特殊配置检查（只需要检查路径和name，不需要检查value)
  global PATH_NAME_CHECK_LIST
  for (item_path, item_name) in PATH_NAME_CHECK_LIST:
    if item_path == path and item_name == name:
      return True 
  # 1) 属性检查
  for key in matcher.keys():
    if key not in element.keys():
      Log('遗漏属性4:' + key + '[tag:' + tag + '][name:' + name + '][path:' + path+ ']')
      return False
    matcher_attr_value = matcher.get(key)
    element_attr_value = element.get(key)
    if matcher_attr_value != element_attr_value:
      ret = False
      #部分属性值顺序可能颠倒，所以如果有"|"分割符，只要包括即可
      if matcher_attr_value.find("|") != -1:
        ret = compareStrContentNotCareOrder(matcher_attr_value, element_attr_value, "|")
        if ret == False:
          Log('属性值不匹配,应该是:[' + matcher_attr_value + ']却配置成了[' + element_attr_value + ']')
          return ret

  # 2) 子节点检查
  for child in list(matcher):
    child_tag = child.tag
    child_name = child.get(NAME)
    if child_name is None:
      child_name = ''
    child_path = os.path.join(path, child_tag)

    element_children = element.findall(child_tag)
    #full attri match
    element_child = Get(element_children, child)
    #part match
    if element_child is None:
      for ele in element_children:
         # special case 特殊配置检查（只需要检查路径和name，不需要检查value)
         for (item_path, item_name) in PATH_NAME_CHECK_LIST:
           ele_path = os.path.join(path, ele.tag)
           try:
             ele_name = ele.get(NAME)
           except:
             break
           if ele_name is not None:
             if ele_path == item_path and ele_name == item_name:
               Log('检查到特殊节点，忽略value,只检查路径和名字')
               element_child = ele
    if element_child is None:
      Log('遗漏配置5：[tag:' + child_tag + '][name:' + child_name  + '][path:' + child_path + ']')
      return False 
    # 递归校验子节点
    
    if not CheckElement(child_tag, child_path, child_name, element_child, child):
      return False

  return True

def CheckEnvironment():
  '环境检查'

  exist = os.path.exists(AM_FILE_NAME)
  if not exist:
    Log('文件' + AM_FILE_NAME + '不存在!')
    return False
  return True

def ParseAndCheckAndroidManifest():
  '解析AndroidManifest.xml并对内容进行校验'

  #忽略名字检查的tag表
  ignore_name_match_tags = [
    'application'
  ]

  # ) parse xml获取包名等信息
  import xml.etree.ElementTree as ET
  tree = ET.parse(AM_FILE_NAME)
  manifest = tree.getroot()
  package_name = manifest.get('package')
  xml_namespace = manifest.get('xmlns:android')

  # ) 预处理 ANDROID_MANIFEST_TEMPLATE
  AM_TEMPLATE = BuildAndroidManifestTemplate()
  template = Template(AM_TEMPLATE).substitute(PACKAGE_NAME=package_name)
  template_root = ET.fromstring(template)
  matchers = list(template_root)
  
  #对于每一个待检查元素进行检查校验
  for matcher in matchers:
    tag = matcher.tag
    name = matcher.get(NAME)
    if not name:
      name = ''

    elements = manifest.findall(tag)
    if len(elements) == 0:
      Log('遗漏配置项1[tag:' + tag + '][name:' + name + ']')
      return False

    #进行name属性检查
    matched_element = None
    if tag not in ignore_name_match_tags:
      for ele in elements:
        me_name = ele.get(NAME)
        if me_name and me_name == name:
          matched_element = ele 
    else:
      matched_element = elements[0]

    if matched_element is None:
      Log('遗漏配置项3[tag:' + tag + '][name:' + name + ']')
      return False

    #递归检查子元素
    if not CheckElement(tag, os.path.join('manifest', tag), name, matched_element, matcher):
      return False
  return True

def Unicode(string):
#  if sys.version[0] >= 3:
#    return unicode(string) 
   return string

def compareStrContentNotCareOrder(str1, str2, slipt):
  # Log('compareStrContentNotCareOrder: str1=' + str1 + ';str2 =' + str2)
  for str in str1.split(slipt):
    if (str2.find(str) == -1):
      return False

  return True

def ParseOptions():

  reload(sys)
  sys.setdefaultencoding('utf8')

  '解析用户自定义参数'
  parser = optparse.OptionParser()
  parser.add_option('-l', '--lib', help=u'指定要检查的lib的相对目录，默认为[../ugpsdk-lib/libs]')
  parser.add_option('-a', '--alipay', action='store_true', default=False, help=u'忽略对支付宝支付配置进行校验!')
  parser.add_option('-w', '--wechat', action='store_true', default=False, help=u'忽略对微信支付配置进行校验!')
  parser.add_option('-m', '--cmmm', action='store_true', default=False, help=u'忽略对移动MM支付配置进行校验!')
  parser.add_option('-b', '--cmbase', action='store_true', default=False, help=u'忽略对移动基地支付配置进行校验!')
  parser.add_option('-u', '--cu', action='store_true', default=False, help=u'忽略对联通运营商支付配置进行校验!')
  parser.add_option('-t', '--ct', action='store_true', default=False, help=u'忽略对电信运营商支付配置进行校验!')
  parser.add_option('-o', '--operator', action='store_true', default=False, help=u'忽略对所有运营商支付配置进行校验!')
  parser.add_option('-r', '--release', action='store_true', default=False, help=u'用于发布包解压后检查配置, 即默认检查本工程的lib目录')
  options, args = parser.parse_args()

  global ALIPAY
  global USED_NOW_WECHAT, USED_MM,USED_BASE,USED_CU,USED_CT
  global USE_ALIPAY,ALIPAY,USE_THREE_OPERATOR
  global PROJECT_LIBS_PATH

  USE_THREE_OPERATOR = True
  USE_ALIPAY = True
  USED_NOW_WECHAT = True
  USED_MM = True
  USED_BASE = True
  USED_CU = True
  USED_CT = True

  if options.alipay:
    USE_ALIPAY = False
    Log('忽略支付宝支付配置校验')
  if options.wechat:
    USED_NOW_WECHAT = False
    Log('忽略now微信支付配置校验')
  if options.cmmm:
    USED_MM = False
    Log('忽略移动MM配置校验')
  if options.cmbase:
    USED_BASE = False
    Log('忽略移动基地配置校验')
  if options.cu:
    USED_CU = False
    Log('忽略联通配置校验')
  if options.ct:
    USED_CT = False
    Log('忽略电信配置校验')

  if options.operator:
    USE_THREE_OPERATOR = False
    USED_MM = False
    USED_BASE = False
    USED_CU = False
    USED_CT = False
    Log('忽略所有运营商支付配置校验')

  if options.lib is not None:
    if not ExistFile(os.path.join(options.lib)):
      Log('工程目录[' + options.lib + ']不存在，请检查之后重新设置!')
      return
    PROJECT_LIBS_PATH = options.lib
  else:
    Log('not specify lib')

  if options.release:
    PROJECT_LIBS_PATH = None
    Log('apk解包后检查配置')

  return options 

#不允许设置<uses-sdk android:targetSdkVersion="23"/>
TARGET_SDK ='android:targetSdkVersion="23"'
def checkTargetSDKVersion():
  fh = open(AM_FILE_NAME)
  for line in  fh.readlines():
    str = "".join(line.split()); #消除字符串的空格
    if(str.find(TARGET_SDK) != -1):
      Log('不允许targetSdkVersion设置为23，请修改！建议修改为16')
      return False
  return True

def DoMain():
  #)参数检查
  LogTitle('开始参数检查...')
  options = ParseOptions()
  if not options:
    return

  #) targetSDK检查
  LogTitle('targetSDK检查（建议targetSdkVersion="16"）...')
  if not checkTargetSDKVersion():
    return
  #) 环境检查 
  LogTitle('开始环境检查...')
  if not CheckEnvironment():
    return 
  #) 读取并解析 AndroidManifest.xml 文件
  LogTitle('开始校验Androidmanifest.xml文件内容...')
  if not  ParseAndCheckAndroidManifest():
    return
  LogTitle('开始检查本地文件配置...')
  #) 检查本地文件配置 
  if not CheckFilesConfig():
    return
  #) 如果未出错，则提示通过检查
  LogTitle('(^_^)恭喜！通过检查，你的配置完全正确!')
    

if __name__ == '__main__':
  DoMain()
