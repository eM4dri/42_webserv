#include <gtest/gtest.h>
#include "../../../../src/network/socket/ASocket.hpp"

#define ANY_PROTOCOL 0
#define MOCK_PORT 8080
#define RANDOM_NUMBER 42
#define MOCK_HOST_ADDR "192.168.0.21"
#define MIN_VALID_SOCKETFD 0

class ASocketForTest : public ft::ASocket 
{
    public:
        ASocketForTest(int domain, int type, int protocol,  u_long interface, int port)
            : ASocket(domain, type, protocol, interface, port){}
        ASocketForTest(int domain, int type, int protocol, int port, const char * address)
            : ASocket(domain, type, protocol, port, address){}

        int connect_to(int socketfd, struct sockaddr_in address)
            {   return RANDOM_NUMBER;   }
};

TEST(ASocketTest, InterfaceConstructor)
{
    ASocketForTest *interfaceSocket = new ASocketForTest(AF_INET, SOCK_STREAM, ANY_PROTOCOL, INADDR_ANY, MOCK_PORT);
    EXPECT_GE(interfaceSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    delete interfaceSocket;
}

TEST(ASocketTest, AddressConstructor)
{
    ASocketForTest *addressSocket = new ASocketForTest(AF_INET, SOCK_STREAM, ANY_PROTOCOL, MOCK_PORT, MOCK_HOST_ADDR);
    EXPECT_GE(addressSocket->get_socketfd(), MIN_VALID_SOCKETFD);
    delete addressSocket;
}
