/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:17:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
#define WELCOME_MESSAGE "Hello from server"

//Constructor
ft::TestServer::TestServer() : AServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
	launch();
}

void ft::TestServer::accepter()
{
	ListenSocket* wsSocket = get_listening_socket();
	struct sockaddr_in	wsAddress = wsSocket->get_address();
	int wsAddressLen = sizeof(wsAddress);
	_clientSocket = accept(wsSocket->get_socketfd(), (struct sockaddr *)&wsAddress, (socklen_t*)&wsAddressLen);
	read(_clientSocket, _buffer, BUFFER_SIZE);
}

void ft::TestServer::handler()
{
	std::cout << _buffer << std::endl;
}

void ft::TestServer::responder()
{
	write(_clientSocket, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
	close(_clientSocket);
}

void ft::TestServer::launch()
{
	while (true)
	{
		std::cout << " ====== WAITING ====== " << std::endl;
		accepter();
		handler();
		responder();
		std::cout << " ======= DONE ======== " << std::endl;
	}
}
