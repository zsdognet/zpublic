#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include "configuration.h"

class ServerConfig
	: public Configuration, public Venus::Singleton<ServerConfig>
{
public:
    std::string serviceName;        //游戏服务名称
    std::string listenAddress;      //游戏服务监听地址, 例：0.0.0.0:36911
    int32 maxQueued;                //最大连接队列
    int32 maxThreads;               //最大I/O线程
    std::string phpServerAddress;   //PHP后台服务的地址, 例：127.0.0.1:19527
    std::string sqlite3File;        //sqlite3数据库文件路径

public:
	bool parse();
};

#endif