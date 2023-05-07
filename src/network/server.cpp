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
#include <fcntl.h>						//	fcntl
#include <cstring>						//	std::memset
#include <unistd.h>						//	close, sleep
#include <cstdlib>						//	std::exit
#include "utils/log.hpp"
#include "actuators/cgi.hpp"
// #include <iostream>						//	std::cout, std::endl
// #include "responses/responses.hpp"
// #include "general.hpp"
// #include "actuators/methods.hpp"

#define BUFFER_SIZE 1024
#define BINDING_RETRYS 10
#define TIME_TO_RETRY 5
#define RETRY_BIND_MSG "Retry bind ..."
#define NOT_BINDED_MSG "socket_fd could not be binded on"
#define WELCOME_MESSAGE "Hello from server\n"
#define NEW_CONNECTION "webserver: new client connects on socket "
#define CLIENT_HUNGUP "client hung up"
#define CLIENT_SAYS(Client) "client " << Client << ": "
#define SERVER_REPONSE "server response:"
#define SEVER_LISTENING(serverfd, address, port) "webserver: new server with socket_fd " << _server_fd << " is listening on " << address << ":" << port
#define BACKLOG 256

namespace ft
{

//Public
//Constructor
server::server(const serverconf &conf)
	: _server_fd(-1), _listening(false), _conf(conf)
{
	_listening = _init_server(conf.address.c_str(), conf.port, BACKLOG);
	if (_listening == false)
		_stop();
	else
	{
		LOG(SEVER_LISTENING(_server_fd, conf.address, conf.port));
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
void server::_start()
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
			std::exit(1);	//! I think we should not exit, just log some error
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
		std::exit(1);	//! I think we should not exit, just log some error
	}
	struct pollfd client;
	client.fd = client_fd;
	client.events = POLLIN;  // Check ready-to-read
	_poll_fds.push_back(client);
	LOG( NEW_CONNECTION << client.fd); //TODO -> molaría printear la IP si las funciones nos dejan
}

void server::_handler(std::vector<struct pollfd>::iterator it)
{
	char 	buffer[BUFFER_SIZE];
	size_t nbytes = recv(it->fd, reinterpret_cast<void *>(buffer), sizeof buffer, 0);
	if ( nbytes < 0 )   // got error
	{
		LOG_ERROR("recv");
		std::exit(1);	//! I think we should not exit, just log some error
	}
	if ( nbytes == 0 )  // connection closed by client
	{
		LOG( CLIENT_SAYS(it->fd) << CLIENT_HUNGUP );
		// TODO Should we not close conection inmediatly, after he closes?
		//?	I think we can close as soon as the response has properly ended following http
		close(it->fd); // Bye!
		_poll_fds.erase(it);
	}
	else	// message from client
	{
		buffer[nbytes] = '\0';
		LOG(CLIENT_SAYS(it->fd));
		LOG_COLOR(RED, buffer );
		_responder(it->fd);
		// _echo(it->fd, buffer, nbytes);
		close(it->fd);
	}
}

void server::_responder(int client_fd)
{
	cgi aux;
	std::string response;
	response =	"HTTP/1.1 200 OK\n"
				"CONTENT-TYPE: text/plain; charset=utf-8\n"
				"Date: Sat, 06 May 2023 14:05:09 GMT\n"
				"Server: HippieServer/1.1\n"
				"Connection: keep-alive\n"
				"Keep-Alive: timeout=5, max=100\n"
				"TRANSFER-ENCODING: chunked\n"
				"\n";

	response.append(aux.get_response());
	// const size_t len = std::strlen(WELCOME_MESSAGE);
	LOG(SERVER_REPONSE);
	LOG_COLOR(GREEN, response);
	send(client_fd, reinterpret_cast<const void *>(response.c_str()), response.length(), 0);
	// struct s_request_info header_struct;
	// std::map<std::string, std::string> header_map;
	// std::string body;
	// int read_status;

	// std::string file_read = file_reader("test_files/get_request", &read_status);
	// if (read_status)
	// 	std::cout << "SOMETHING WENT WRONG IN THE MAIN!" << std::endl << "Error code: " << read_status << std::endl;
	// header_parser(file_read, header_struct, header_ma=p, body);

	// std::string content = return_content(200, header_struct.path);

	// send(client_fd, content.c_str(), content.length(), 0);
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
