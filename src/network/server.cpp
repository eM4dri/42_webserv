/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:14:34 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 19:57:32 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include "utils/log.hpp"

#define BUFFER_SIZE 256
#define BINDING_RETRYS 10
#define TIME_TO_RETRY 5
#define RETRY_BIND_MSG "Retry bind ..."
#define NOT_BINDED_MSG "socket_fd could not be binded on"
#define WELCOME_MESSAGE "Hello from server\n"
#define NEW_CONNECTION "webserver: new client connects on socket "
#define CLIENT_HUNGUP "client hung up"
#define CLIENT_SAYS(Client) "client " << Client << ": "
#define SEVER_LISTENING(serverfd, address, port) "webserver: new server with socket_fd " << _server_fd << " is listening on " << address << ":" << port

//Public
//Constructor
namespace ft
{

server::server(const char *address, int port, int backlog)
	: _server_fd(-1), _listening(false)
{
	_listening = _init_server(address, port, backlog);

	if (_listening == false)
		_stop();
	else
	{
		LOG(SEVER_LISTENING(_server_fd, address, port));
		_start();
	}
}

server::~server()
{
	_stop();
}

//Private
//Function to init server
bool server::_init_server(const char *address, int port, int backlog)
{
	size_t address_sizeof = sizeof(_address);
	std::memset(reinterpret_cast<void *>(&_address), 0, address_sizeof);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = inet_addr( address );
	_address.sin_port = htons(port);
	_address_len = static_cast<socklen_t>(address_sizeof);

	_server_fd = socket(PF_INET, SOCK_STREAM, 0);

	short retrys = BINDING_RETRYS;
	const struct sockaddr * ws_address =  reinterpret_cast<struct sockaddr *>(&_address);
	while ( -1 == bind(_server_fd, ws_address, _address_len) && retrys-- ){
		LOG(RETRY_BIND_MSG);
		sleep(TIME_TO_RETRY);
	}
	if (retrys == 0){
		close(_server_fd);
		LOG_ERROR( _server_fd << NOT_BINDED_MSG << address << ":" << port);
		return false;
	}
	if ( -1 == listen(_server_fd, backlog) ){
		LOG_ERROR( "listen");
		return false;
	}
	return true;
}

//Function to start server
void server::_start(void)
{
	struct pollfd webServer;
	webServer.fd = _server_fd;
	webServer.events = POLLIN;	 // Check ready-to-read
	_poll_fds.push_back(webServer);
	fcntl(webServer.fd, F_SETFL, O_NONBLOCK);
	while (true)
	{
		if ( -1 == poll(reinterpret_cast<pollfd *>(&_poll_fds[0]), static_cast<nfds_t>(_poll_fds.size()), -1) )
		{
			LOG_ERROR("poll");
			exit(1);
		}
		for(std::vector<struct pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++)
		{
			// Check if someone's ready to read
			if (it->revents & POLLIN)   // We got one!!
			{ 
				if (it == _poll_fds.begin())  // If listener is ready to read, handle new connection
					_accepter();
				else	// If not the listener, we're just a regular client
					_handler(it);
				break;
			}	 // END got ready-to-read from poll()
		}	// END looping through file descriptors
	}
}

//Function to stop server
void server::_stop(void)
{
	if (_poll_fds.size() > 0)
	{
		for(std::vector<struct pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); it++)
			close(it->fd);
		_poll_fds.clear();
	}
	if ( _listening == true )
	{	
		close(_server_fd);
		_listening = false;
	}
}
 
//Functions to handle connections
void server::_accepter()
{
	int client_fd = accept(_server_fd, reinterpret_cast<struct sockaddr *>(&_address), &_address_len);
	if (client_fd == -1)
	{
		LOG_ERROR("accept");
		exit(1);
	}
	struct pollfd client;
	client.fd = client_fd;
	client.events = POLLIN;  // Check ready-to-read
	_poll_fds.push_back(client);
	LOG( NEW_CONNECTION << client.fd); //TODO -> molaría printear la IP si las funciones nos dejan
	_responder(client.fd);
}

void server::_handler(std::vector<struct pollfd>::iterator it)
{
	char 	buffer[BUFFER_SIZE];
	size_t nbytes = recv(it->fd, reinterpret_cast<void *>(buffer), sizeof buffer, 0);
	if ( nbytes < 0 )   // got error
	{
		LOG_ERROR("recv");
		exit(1);
	}
	if ( nbytes == 0 )  // connection closed by client
	{
		LOG( CLIENT_SAYS(it->fd) << CLIENT_HUNGUP );
		close(it->fd); // Bye!
		_poll_fds.erase(it);
	}
	else	// message from client
	{
		buffer[nbytes] = '\0';
		LOG2( CLIENT_SAYS(it->fd) << buffer );
		_echo(it->fd, buffer, nbytes);
	}
}

void server::_responder(int client_fd)
{
	const size_t len = std::strlen(WELCOME_MESSAGE);
	send(client_fd, reinterpret_cast<const void *>(WELCOME_MESSAGE), len, 0);
}

void server::_echo(int fd, char const *str, size_t nbytes)
{
	for(std::vector<struct pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); ++it)
	{
		if (it->fd != fd && it->fd != _server_fd)
			send(it->fd, str, nbytes, 0);
	}
}

}	// Nammespace ft
