#include <gtest/gtest.h>
#include "../../../../src/sandbox/socket/BindSocket.hpp"
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

TEST(BindSocketTest, InterfaceConstructor)
{
	ft::BindSocket*	bindSocket = new ft::BindSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, INADDR_ANY, MOCK_PORT);
    EXPECT_GE(bindSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    EXPECT_EQ(bindSocket->get_connectionStatus(), SUCCESS);
    EXPECT_NE(bindSocket->get_connectionStatus(), ERROR);
	delete bindSocket;
}

TEST(BindSocketTest, AddressConstructor)
{
	ft::BindSocket*	bindSocket = new ft::BindSocket(AF_INET, SOCK_STREAM, ANY_PROTOCOL, MOCK_PORT, NOT_ACCESIBLE_HOST);
    EXPECT_GE(bindSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    EXPECT_NE(bindSocket->get_connectionStatus(), SUCCESS);
    EXPECT_EQ(bindSocket->get_connectionStatus(), ERROR);
	delete bindSocket;
}



