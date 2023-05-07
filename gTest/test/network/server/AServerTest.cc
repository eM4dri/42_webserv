#include <gtest/gtest.h>
#include "../../../../src/sandbox/server/AServer.hpp"

#define ANY_PROTOCOL 0
#define MOCK_PORT 8080
#define MOCK_BACKLOG 10
#define RANDOM_NUMBER 42
#define MOCK_HOST_ADDR "192.168.0.21"
#define MIN_VALID_SOCKETFD 0
enum e_connect_status
{
    ERROR = -1,
    SUCCESS = 0
};


class AServerForTest : public ft::AServer
{
    private:
        void _accepter(){}
        void _handler(){}
        void _responder(){}

    public:
        AServerForTest(int domain, int type, int protocol,  u_long interface, int port, int backlog)
            : ft::AServer(domain, type, protocol, interface, port, backlog){}
        AServerForTest(int domain, int type, int protocol, int port, const char * address, int backlog)
            : ft::AServer(domain, type, protocol, port, address, backlog){}

        void launch(void){}
};

TEST(AServerTest, InterfaceConstructor)
{
    AServerForTest *interfaceServer = new AServerForTest(AF_INET, SOCK_STREAM, ANY_PROTOCOL, INADDR_ANY, MOCK_PORT, MOCK_BACKLOG);
    ft::ListenSocket listenSocket = interfaceServer->get_listening_socket();
    EXPECT_GE(listenSocket.get_socketfd(), MIN_VALID_SOCKETFD);
    // EXPECT_NE(listenSocket.get_connectionStatus(), SUCCESS);
    // EXPECT_EQ(listenSocket.get_connectionStatus(), ERROR);
    EXPECT_EQ(listenSocket.get_backlog(), MOCK_BACKLOG);
    EXPECT_EQ(listenSocket.get_listenfd(), SUCCESS);
    EXPECT_NE(listenSocket.get_listenfd(), ERROR);
    delete interfaceServer;
}

TEST(AServerTest, AddressConstructor)
{
    AServerForTest *addressServer = new AServerForTest(AF_INET, SOCK_STREAM, ANY_PROTOCOL, MOCK_PORT, MOCK_HOST_ADDR, MOCK_BACKLOG);
    ft::ListenSocket listenSocket = addressServer->get_listening_socket();
    EXPECT_GE(listenSocket.get_socketfd(), MIN_VALID_SOCKETFD);
    // EXPECT_NE(listenSocket.get_connectionStatus(), SUCCESS);
    // EXPECT_EQ(listenSocket.get_connectionStatus(), ERROR);
    EXPECT_EQ(listenSocket.get_backlog(), MOCK_BACKLOG);
    EXPECT_EQ(listenSocket.get_listenfd(), SUCCESS);
    EXPECT_NE(listenSocket.get_listenfd(), ERROR);
    delete addressServer;
}
