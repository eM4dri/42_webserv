#include <gtest/gtest.h>
#include "../../../../src/network/socket/ConnectSocket.hpp"
#include <iostream>

#define ANY_PROTOCOL 0
#define MOCK_PORT 8080
#define RANDOM_NUMBER 42
#define NOT_ACCESIBLE_HOST "1.2.3.4"
#define MIN_VALID_SOCKETFD 0
enum e_connect_status
{
    ERROR = -1,
    SUCCESS = 0
};


//This test keep connection alive, we need some kind dc
TEST(ConnectSocketTest, InterfaceConstructor)
{
	ft::ConnectSocket*	connectSocket = new ft::ConnectSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, INADDR_ANY, MOCK_PORT);
    close(connectSocket->get_socketfd());
    EXPECT_GE(connectSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    EXPECT_EQ(connectSocket->get_connectionStatus(), SUCCESS);
    EXPECT_NE(connectSocket->get_connectionStatus(), ERROR);
	delete connectSocket;
}

TEST(ConnectSocketTest, AddressConstructor)
{
	ft::ConnectSocket*	connectSocket = new ft::ConnectSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, MOCK_PORT, NOT_ACCESIBLE_HOST);
    EXPECT_GE(connectSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    EXPECT_NE(connectSocket->get_connectionStatus(), SUCCESS);
    EXPECT_EQ(connectSocket->get_connectionStatus(), ERROR);
	delete connectSocket;
}



