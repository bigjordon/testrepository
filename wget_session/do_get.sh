#!/bin/sh
urllist="https://www.baidu.com/
http://www.sina.com.cn/
http://www.sohu.com/
http://www.qq.com/
http://www.163.com/
http://www.iqiyi.com/
https://s.click.taobao.com/
http://www.ifeng.com/
https://www.taobao.com/
https://www.douyu.com/
http://v.hao123.baidu.com/
http://www.eastmoney.com/
http://jump.luna.58.com/
http://u.ctrip.com/union/
http://www.zhihu.com/
http://www.icbc.com.cn/icbc/
https://mail.qq.com/
https://www.zhibo8.cc/
https://www.bilibili.com/
        "
echo $urllist
while true; do 
	for url in $urllist; do
		wget $url 
		sleep 0.1
		rm index.*
		rm t*
	done
#	break
done
