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

//Private
//Functions to handle connections
void ft::TestServer::_accepter()
{
	ListenSocket* wsSocket = get_listening_socket();
	struct sockaddr_in	wsAddress = wsSocket->get_address();
	int wsAddressLen = sizeof(wsAddress);
	_clientSocket = accept(wsSocket->get_socketfd(), (struct sockaddr *)&wsAddress, (socklen_t*)&wsAddressLen);
	read(_clientSocket, _buffer, BUFFER_SIZE);
}

void ft::TestServer::_handler()
{
	std::cout << _buffer << std::endl;
}

void ft::TestServer::_responder()
{
	write(_clientSocket, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
	close(_clientSocket);
}

//Public
//Constructor
ft::TestServer::TestServer() : AServer(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10)
{
	launch();
}

// ft::TestServer::~TestServer()
// {
// 	ft::ListenSocket *socket = get_listening_socket();
// 	delete socket;	
// }

//Function to  launch server
void ft::TestServer::launch(void)
{
	while (true)
	{
		std::cout << " ====== WAITING ====== " << std::endl;
		_accepter();
		_handler();
		_responder();
		std::cout << " ======= DONE ======== " << std::endl;
	}
}
