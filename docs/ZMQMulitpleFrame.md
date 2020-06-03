# ZMQ多客户端维护

关于ZMQ如何异步的找到正确的客户端分发消息

目前教程并没有提到如何在多客户端连接的情况下,找到需要找到的客户端的解决方案 

如多个客户端同时链接,ABC,并保持活跃,如果服务器需要只给B发送某个通知信息,该如何进行通知动作,平常的reactor模式,B会持有一个 fd 来建立连接



> https://www.cnblogs.com/catch/p/5841339.htmlhttps://webcache.googleusercontent.com/search?q=cache:FGM3Us0yVfoJ:https://android.developreference.com/article/14802382/How%2Bdoes%2BZeroMQ%2BREQ%2BREP%2Bhandle%2Bmultiple%2Bclients%3F+&cd=6&hl=zh-CN&ct=clnk)