/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:14:34 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 12:46:35 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollServer.hpp"
#include <iostream>
#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define WELCOME_MESSAGE "Hello from server\n"
#define INITIAL_POLL_FD_SIZE 5

//Public
//Constructor
namespace ft
{

PollServer::PollServer(int domain, int type, int protocol, u_long interface, int port, int backlog) 
	: AServer(domain, type, protocol, interface, port, backlog)
{
	struct pollfd webServer;
	webServer.fd = get_listening_socket().get_socketfd();
	webServer.events = POLLIN;	 // Check ready-to-read
	poll_fds.push_back(webServer);
	fcntl(webServer.fd, F_SETFL, O_NONBLOCK);
	launch();
}

PollServer::~PollServer()
{
	if (poll_fds.size() > 0)
		poll_fds.clear();
}

//Function to  launch server
void PollServer::launch(void)
{
	while (true)
	{
		if ( -1 == poll(&poll_fds[0], poll_fds.size(), -1) )
		{
			perror("poll");
			exit(1);
		}
		for(std::vector<struct pollfd>::iterator it = poll_fds.begin(); it != poll_fds.end(); it++)
		{
			// Check if someone's ready to read
			if (it->revents & POLLIN)   // We got one!!
			{ 
				if (it == poll_fds.begin())  // If listener is ready to read, handle new connection
					_accepter();
				else	// If not the listener, we're just a regular client
					_handler(it);
				break;
			}	 // END got ready-to-read from poll()
		}	// END looping through file descriptors
	}
}

//Private
//Functions to handle connections
void PollServer::_accepter()
{
	ListenSocket wsSocket = get_listening_socket();
	struct sockaddr_in	wsAddress = wsSocket.get_address();
	int wsAddressLen = sizeof(wsAddress);
	int client_fd = accept(wsSocket.get_socketfd(), (struct sockaddr *)&wsAddress, (socklen_t*)&wsAddressLen);
	if (client_fd == -1)
	{
		perror("accept");
		exit(1);
	}
	struct pollfd client;
	client.fd = client_fd;
	client.events = POLLIN;  // Check ready-to-read
	poll_fds.push_back(client);
	std::cout << "pollserver: new connection on socket " << client.fd << std::endl; //TODO -> molaría printear la IP si las funciones nos dejan
	_responder(client.fd);
}

void PollServer::_handler(std::vector<struct pollfd>::iterator it)
{
	char 	buffer[BUFFER_SIZE];
	size_t nbytes = recv(it->fd, buffer, sizeof buffer, 0);
	if ( nbytes < 0 )   // got error
	{
		perror("recv");
		exit(1);
	}
	if ( nbytes == 0 )  // connection closed by client
	{
		std::cout << "selectserver: socket " << it->fd << " hung up" << std::endl;
		close(it->fd); // Bye!
		poll_fds.erase(it);
	}
	else	// message from client
	{
		buffer[nbytes] = '\0';
		std::cout << "client(socket " << it->fd << ")  says: " << buffer;
		_echo(it->fd, buffer, nbytes);
	}
}

void PollServer::_responder(int client_fd)
{
	const size_t len = strlen(WELCOME_MESSAGE);
	send(client_fd, WELCOME_MESSAGE, len, 0);
}

void PollServer::_echo(int fd, char const *str, size_t nbytes)
{
	for(std::vector<struct pollfd>::iterator it = poll_fds.begin(); it != poll_fds.end(); ++it)
	{
		if (it->fd != fd && it->fd != poll_fds.begin()->fd)
			send(it->fd, str, nbytes, 0);
	}
}

}	// Nammespace ft
