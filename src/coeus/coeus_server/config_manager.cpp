#include "config_manager.h"
#include "configuration.h"
#include <thread>

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::registerConfig(Configuration* configuration)
{
	_configurations.push(configuration);
}

void ConfigManager::start()
{
    debug_log("loading server configurations...");
	std::thread threads[kThreadNums];

	for (int i = 0; i < kThreadNums; ++i)
		threads[i] = std::thread(&ConfigManager::workerThread, this);

	for (auto& thread : threads) thread.join();
}

void ConfigManager::wait()
{

}

void ConfigManager::workerThread()
{
	for (int i = 0; i < _configurations.size(); ++i)
	{
		_mutex.lock();
		Configuration* configuration = _configurations.front();
		_configurations.pop();
		_mutex.unlock();

		bool result = configuration->parse();
        if (result == false)
        {
            error_log("load config ['%s'] failed. server interrupt!", configuration->filename().c_str());
        }
        else
        {
            debug_log("load config ['%s'] ok.", configuration->filename().c_str());
        }
	}
}
