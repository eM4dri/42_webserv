#include <gtest/gtest.h>
#include "../../../../src/sandbox/socket/ListenSocket.hpp"
#include <iostream>

#define ANY_PROTOCOL 0
#define MOCK_PORT 8080
#define MOCK_BACKLOG 10
#define RANDOM_NUMBER 42
#define NOT_ACCESIBLE_HOST "1.2.3.4"
#define MIN_VALID_SOCKETFD 0
enum e_connect_status
{
    ERROR = -1,
    SUCCESS = 0
};


//Review these test, it seems inheritance doesn't work as it should
TEST(ListenSocketTest, InterfaceConstructor)
{
	ft::ListenSocket*	listenSocket = new ft::ListenSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, INADDR_ANY, MOCK_PORT, MOCK_BACKLOG);
    EXPECT_GE(listenSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    // EXPECT_NE(listenSocket->get_connectionStatus(), SUCCESS);
    // EXPECT_EQ(listenSocket->get_connectionStatus(), ERROR);
    EXPECT_EQ(listenSocket->get_backlog(), MOCK_BACKLOG);
    EXPECT_EQ(listenSocket->get_listenfd(), SUCCESS);
    EXPECT_NE(listenSocket->get_listenfd(), ERROR);
	delete listenSocket;
}

TEST(ListenSocketTest, AddressConstructor)
{
	ft::ListenSocket*	listenSocket = new ft::ListenSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, MOCK_PORT, NOT_ACCESIBLE_HOST, MOCK_BACKLOG);
    EXPECT_GE(listenSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    // EXPECT_NE(listenSocket->get_connectionStatus(), SUCCESS);
    // EXPECT_EQ(listenSocket->get_connectionStatus(), ERROR);
    EXPECT_EQ(listenSocket->get_backlog(), MOCK_BACKLOG);
    EXPECT_EQ(listenSocket->get_listenfd(), SUCCESS);
    EXPECT_NE(listenSocket->get_listenfd(), ERROR);
	delete listenSocket;
}



