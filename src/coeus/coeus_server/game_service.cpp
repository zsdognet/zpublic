#include "game_service.h"
#include <Poco/Data/Common.h>
#include <Poco/Data/SQLite/Connector.h>
#include "game_database.h"
#include "game_session_manager.h"
#include "player_manager.h"
#include "config_loader.h"
#include "config_manager.h"

#define CHECK_INITIALIZE(result, x, s) \
	if (result) \
	debug_log(x); \
	else \
	error_log(s);

GameService::GameService()
{
}

GameService::~GameService()
{
}


bool GameService::initialize()
{
	try
	{
        ConfigLoader::getInstance().initialize(ConfigManager::getInstancePtr());
		ConfigManager::getInstance().start();
		CHECK_INITIALIZE(registerDatabase(), "Database registered OK.", "Database register failed.");
		CHECK_INITIALIZE(PlayerManager::getInstance().init(), "PlayerManager init OK.", "PlayerManager init failed.");
		CHECK_INITIALIZE(GameSessionManager::getInstance().init(), "GameSessionManager init OK.", "GameSessionManager init failed.");
	}
	catch (...)
	{
		error_log("An unknown exception occured when initialize game service. Aborted.");
		return false;
	}

	return true;
}

void GameService::destroy()
{
	GameSessionManager::getInstance().destroy();
	PlayerManager::getInstance().destroy();
	unregisterDatabase();
}

bool GameService::registerDatabase()
{
	Poco::Data::SQLite::Connector::registerConnector();
	return true;
}

void GameService::unregisterDatabase()
{
	Poco::Data::SQLite::Connector::unregisterConnector();
}