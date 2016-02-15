使用说明：

 1. 解apk包命令如下 

   apktool.jar d -f 你的应用.apk
 
 2. 将脚本放入apk解包的根目录，并在该目录下运行脚本：python env_check.py -r

=========================================================================================
脚本帮助命令  python env_check.py -h
---------------------------------------------
Usage: env_check.py [options]

Options:
  -h, --help         show this help message and exit
  -l LIB, --lib=LIB  指定要检查的lib的相对目录，默认为[../ugpsdk-lib/libs]
  -a, --alipay       忽略对支付宝支付配置进行校验!
  -w, --wechat       忽略对微信支付配置进行校验!
  -m, --cmmm         忽略对移动MM支付配置进行校验!
  -b, --cmbase       忽略对移动基地支付配置进行校验!
  -u, --cu           忽略对联通运营商支付配置进行校验!
  -t, --ct           忽略对电信运营商支付配置进行校验!
  -o, --operator     忽略对所有运营商支付配置进行校验!
  -r, --release      用于发布包解压后检查配置, 即默认检查本工程的lib目录
 