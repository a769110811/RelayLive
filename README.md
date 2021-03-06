# RelayLive
## 地址: 
*  https://github.com/BigPig0/RelayLive.git
*  https://gitee.com/ztwlla/RelayLive.git

## 说明:
* ipc_server: 进程间通讯和进程保护的工具
* * pm.json 配置文件，需要启动的程序信息。

### 对接海康SDK
* hik_server: 使用海康sdk播放视频并转为ws-flv
* hikctrl_server: 查看平台设备信息、客户端信息
* * hikctrl.lua 数据库脚本
* * config.txt 海康平台登陆配置
* * 配置示例在Build/projects/config_yongjia_hikserver
* 客户端请求格式为 http(ws)://IP:port/live/flv/0/[code]

### 对接视频流
* relay_server: 将视频流转为ws-flv，流可以为rtsp、rtmp、hls等
* relayctrl_server: 查看客户端信息
* * 配置示例在Build/projects/config_kunshan_tecc
* 客户端请求格式为 http(ws)://IP:port/live?url=[rtsp地址]

### 对接国标平台
* sip_server: sip服务器，用来与下级平台交互
* live_server: 将下级推送的基于PS的rtp流转为ws-flv
* livectrl_server: 查看设备信息、客户端信息、设备控制
* 客户端请求格式为 http(ws)://IP:port/live?code=[code]&hw=[960*480] 
* * code 相机的国标编码
* * hw 可选参数，用来缩放视频大小
* 云台控制 http://ip:port/device/control/[code]?ud=[p1]&lr=[p2]&io=[p3]
* * p1: 0-停止 1-向上 2-向下
* * p2: 0-停止 1-向左 2-向右
* * p3: 0-停止 1-焦距减 2-焦距加



## 编译方法
* 平台: Windows vs2012
* 用vs打开build/RelayLive.sln,按顺序编译ThirdParty、Common、Modules、Projects下的项目。
* 在输出目录部署配置文件pm.json,config.txt和脚本文件 XXX.lua。(文件在/Build/projects下有示例)
* 从thirdParty拷贝ffmpeg的dll到输出目录。
* 部署数据库，数据库的操作在XXX.lua中。
* 使用ipc_server启动

## nginx
* 页面demo静态文件通过nginx来访问
* 信息查询和设备控制等http请求通过nginx转发到XXXctrl_server
* 视频播放请求通过nginx进行负载均衡，转发到对应的视频服务

## 第三方:
* exosip: http://savannah.nongnu.org/projects/exosip
* exosip-vs: https://github.com/BigPig0/exOsip-vs.git
* ffmpeg: http://ffmpeg.org/
* libwebsockets: https://github.com/warmcat/libwebsockets.git
* libuv: https://github.com/libuv/libuv.git
* luapp: https://github.com/ToyAuthor/luapp.git
* libcstl: https://github.com/activesys/libcstl.git
* flv.js: https://github.com/Bilibili/flv.js.git
* NodePlayer.js: https://github.com/illuspas/NodePlayer.js.git