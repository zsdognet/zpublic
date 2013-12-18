#include "service_application.h"
#include "server_handler.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TcpServer.h"
#include "Poco/Thread.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/File.h"
#include "logger.h"

ServiceApplication::ServiceApplication(const std::string& serviceName)
    : _serviceName(serviceName)
{
}

ServiceApplication::~ServiceApplication()
{

}

void ServiceApplication::initialize(Poco::Util::Application& self)
{
    ServerApplication::loadConfiguration();
    ServerApplication::initialize(self);

    // init logger
    Logger::getInstance().init(this->logger());
}

void ServiceApplication::uninitialize()
{
    ServerApplication::uninitialize();
}

void ServiceApplication::defineOptions(Poco::Util::OptionSet& options)
{
    ServerApplication::defineOptions(options);

    options.addOption(
        Poco::Util::Option("help", "h", "display help information on command line arguments")
        .required(false)
        .repeatable(false));
}

void ServiceApplication::handleOption(const std::string& name, const std::string& value)
{
    ServerApplication::handleOption(name, value);

    if (name == "help")
    {
        std::cout << "show help" << std::endl;
    }
}

int ServiceApplication::main(const std::vector<std::string>& args)
{
    //�����ö�ȡ��������Ϣ
    unsigned short port = (unsigned short) config().getInt("port", 36911);
    Poco::Net::ServerSocket socket(port);
    Poco::Net::TCPServerParams* serverParams = new Poco::Net::TCPServerParams();
    serverParams->setMaxQueued(64);         //���Ӷ��������
    serverParams->setMaxThreads(1);         //���IO�߳���
    serverParams->setThreadIdleTime(100);     //�߳���ֹʱ���ȴ�ʱ��

    info_log(
        "\n"
        "===================== Server Startup ===================\n"
        "       Service Name = %s\n"
        "       Listen Port  = %d\n"
        "       I/O Thread   = %d\n"
        "       Max Queued   = %d\n"
        "========================================================\n"
        "�ҵ�����һƬ�޻ڣ�����������Ϧ���µı��ܣ���������ȥ���ഺ\n"
        "========================================================",
        _serviceName.c_str(), port, serverParams->getMaxThreads(), serverParams->getMaxQueued()
        );

    Poco::Net::TCPServer server(new ConnectionFactory(), socket, serverParams);
    server.start();

    info_log("Server started.");
    Poco::Util::ServerApplication::waitForTerminationRequest();
    server.stop();

    return Application::EXIT_OK;
}