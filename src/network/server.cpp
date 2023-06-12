/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:14:34 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 19:57:32 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "utils/log.hpp"
#include <unistd.h>			//	close
#include <cstdlib>			//	std::exit
#include <signal.h>			//	signal, sig_atomic_t
#include <ctime>			//	std::time
#include <cstring>			//	std::time
#include <stdexcept>		//	std::invalid_argument

#define BUFFER_SIZE 1045504

#define WELCOME_MESSAGE "Hello from server\n"
#define NEW_CONNECTION "webserver: new client connects on socket "
#define CLIENT_HUNGUP "client hung up"
#define CLIENT_SAYS(Client) "client " << Client << ": "
#define SERVER_REPONSE "server response:"
#define CACHED_TIME 60
#define HTTP_HEADER_HOST "Host:"
#define HTTP_HEADER_HOST_SIZE 5
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define HTTP_HEADER_HOST_END_HOST_NAME ":\r\n"
#define SEND_SOCKET_FAILS "Send fails over socket "

namespace ft
{

//Public
//Constructor
server::server(const char* filename)
{
	bool status= false;

	LOG("Loading MimeTypes");
	Filetypes types(&status);	//	loading Mimetypes
	if (!status)
		throw std::invalid_argument("Error loading MimeTypes");
	LOG("Loading Configuration file");
	conf config_file(filename, types);
	listen_sockets	listening_sockets(config_file);
	if (listening_sockets._get_sockets().empty())
		LOG_ERROR("There is no listening socket");
	else
	{
		_add_listening_sockets_to_poll(listening_sockets);
		_start(listening_sockets);
	}
}

server::~server()
{
	_stop();
}

//Private
//Add listening Soxckets to poll
void server::_add_listening_sockets_to_poll(const listen_sockets &listening_sockets)
{
	std::map<int, socket_fd>::const_iterator it;
	it = listening_sockets._get_sockets().begin();
	for ( ; it != listening_sockets._get_sockets().end(); it++){
		struct pollfd webServer;
		webServer.fd = it->second.fd;
		webServer.events = POLLIN;		// Check ready-to-read
		_poll_fds.push_back(webServer);
	}
}


bool stopServer = false;

void signal_handler(int param)
{
	(void)param;
	LOG( "\nSIGINT shuting down server" );
	stopServer = true;
}

//Function to start server
void server::_start(const listen_sockets &listening_sockets)
{
	signal(SIGINT, signal_handler);
	while (!stopServer)
	{
		if ( -1 == poll(reinterpret_cast<pollfd *>(&_poll_fds[0]), static_cast<nfds_t>(_poll_fds.size()), -1) && !stopServer)
		{
			LOG_ERROR("poll shuting down server");
			break;
			// std::exit(1);	//! I think we should not exit, just log some error
		}
		std::vector<struct pollfd>::iterator it = _poll_fds.begin();
		for( ; it != _poll_fds.end(); it++)
		{
			// Check if someone's ready to read
			if (it->revents & POLLIN)   // We got one!!
			{
				std::map<int, socket_fd>::const_iterator found;
				found = listening_sockets._get_sockets().find(it->fd);
				if (found != listening_sockets._get_sockets().end())  // If listener is ready to read, handle new connection
					_accepter(found->second);
				else	// If not the listener, we're just a regular client
					_handler(it, listening_sockets);
				break;
			}	 // END got ready-to-read from poll()
		}	// END looping through file descriptors
		_expire_cached_responses();
	}
}

//Function to stop server
void server::_stop(void)
{
	if (!_poll_fds.empty())
	{
		std::vector<struct pollfd>::iterator it = _poll_fds.begin();
		for( ; it != _poll_fds.end(); it++)
			close(it->fd);
		_poll_fds.clear();
	}
	if (!_client_server_conections.empty())
		_client_server_conections.clear();
	if (!_cached_responses.empty())
		_cached_responses.clear();
	LOG("Server stopped properly");
}

//Functions to handle connections
void server::_accepter(const socket_fd& listen_socket)
{
	struct sockaddr_in	_address = listen_socket.address;
	socklen_t	_address_len = listen_socket.address_len;
	int client_fd = accept(listen_socket.fd, reinterpret_cast<struct sockaddr *>(&_address), &_address_len);
	if (client_fd == -1)
	{
		LOG_ERROR("accept");
		std::exit(1);	//! I think we should not exit, just log some error
	}
	struct pollfd client;
	client.fd = client_fd;
	client.events = POLLIN;  // Check ready-to-read
	_poll_fds.push_back(client);
	_client_server_conections[client_fd] = listen_socket.fd;
	LOG( NEW_CONNECTION << client.fd); //TODO -> molaría printear la IP si las funciones nos dejan
}

static std::string mocked_error_message()
{
	std::string retval;
	std::string the_body;
	std::string error_reason = "413";
	error_reason.append(" ");
	error_reason.append(getMessageFromCode(413));


	the_body.append("<html>\r\n");
	the_body.append("\t<head><title>");
	the_body.append(error_reason);
	the_body.append("</title></head>\r\n");
	the_body.append("\t<body>\r\n");
	the_body.append("\t\t<h1><center>");
	the_body.append(error_reason);
	the_body.append("</center></h1>\r\n");
	the_body.append("\t\t<hr>\r\n");
	the_body.append("\t\t<p><center>Webserv</center></p>\r\n");
	the_body.append("\t</body>\r\n");
	the_body.append("</html>");



	retval.append("HTTP/1.1 413 Payload Too Large\r\n");
	retval.append("Content-Length: ");
	retval.append(to_string(the_body.length()));
	retval.append("\r\n");
	retval.append("Date: ");
	retval.append(get_date());
	retval.append("\r\n");
	retval.append("Server: webserv\r\n");
	retval.append("\r\n");
	retval.append(the_body);


	return (retval);
}

void server::_handler(std::vector<struct pollfd>::iterator it, const listen_sockets &_listening_sockets)
{
	char 	buffer[BUFFER_SIZE];
	size_t nbytes = recv(it->fd, reinterpret_cast<void *>(buffer), sizeof(buffer), 0);
	if ( nbytes < 0 )   // got error
	{
		LOG_ERROR("recv");
		std::exit(1);	//! I think we should not exit, just log some error
	}
	if (nbytes > BUFFER_SIZE - 1)
	{
		std::string toolarge = mocked_error_message();

		if (send(it->fd, reinterpret_cast<const void *>(toolarge.c_str()), toolarge.length(), 0) == -1)
			LOG_ERROR(SEND_SOCKET_FAILS << it->fd);
		close(it->fd);
		_client_server_conections.erase(it->fd);
		_poll_fds.erase(it);

	}
	else if ( nbytes == 0 )  // connection closed by client
	{
		LOG( CLIENT_SAYS(it->fd) << CLIENT_HUNGUP );
		// TODO Should we not close conection inmediatly, after he closes?
		//?	I think we can close as soon as the response has properly ended following http
		close(it->fd); // Bye!
		_client_server_conections.erase(it->fd);
		_poll_fds.erase(it);
	}
	else	// message from client
	{
		buffer[nbytes] = '\0';
		int listen_fd = _client_server_conections.find(it->fd)->second;
		const serverconf *hosted_server_configuration = _get_hosted_server_configuration(listen_fd, buffer, _listening_sockets);
		Request request(buffer, *hosted_server_configuration);
		cached_key key;
		key.fd = listen_fd;
		key.request = buffer;
		std::map<cached_key, cached_value>::iterator found = _cached_responses.find(key);

		bool send_socket_fails;
		if (CACHED_TIME > 0 && request.get_method() == GET && found != _cached_responses.end())
		{
			if (send(it->fd, reinterpret_cast<const void *>(found->second.response.c_str()), found->second.response.length(), 0) == -1)
			{
				LOG_ERROR(SEND_SOCKET_FAILS << it->fd);
				send_socket_fails = true;
			}
		}
		else
		{
			LOG(CLIENT_SAYS(it->fd));
			LOG_COLOR(RED, buffer);
			_responder(it->fd, request, listen_fd, &send_socket_fails);
		}
		if (!request.get_keep_connection_alive() || send_socket_fails == true)
		{
			close(it->fd);
			_client_server_conections.erase(it->fd);
			_poll_fds.erase(it);
		}
	}
}

const serverconf *server::_get_hosted_server_configuration(int listen_fd, char *buffer, const listen_sockets &_listening_sockets)
{
	char * buffer_host = std::strstr(buffer, HTTP_HEADER_HOST);
	std::string host;
	if (buffer_host != NULL)
	{
		host = buffer_host;
		host.erase(0, HTTP_HEADER_HOST_SIZE);
		host.erase(0, host.find_first_not_of(ISSPACE_CHARACTERS));
		host.erase(host.find_first_of(HTTP_HEADER_HOST_END_HOST_NAME));
	}
	std::map< int, socket_fd>::const_iterator listening_socket = _listening_sockets._get_sockets().find(listen_fd);
	std::map< std::string,const serverconf	*>::const_iterator server_host;
	if (listening_socket != _listening_sockets._get_sockets().end())
	{
		server_host = listening_socket->second.hosted_server_config.find(host);
		if (server_host == listening_socket->second.hosted_server_config.end())
			server_host = listening_socket->second.hosted_server_config.begin();
	}
	return server_host->second;
}

void server::_responder(int client_fd, const Request & request, int listen_fd, bool *send_socket_fails)
{
	Response the_response(request);
	std::string response = the_response.generate_response();

	LOG(SERVER_REPONSE);
	LOG_COLOR(GREEN, response);
	_cache_response(request,listen_fd, the_response, response);
	if (send(client_fd, reinterpret_cast<const void *>(response.c_str()), response.length(), 0) == -1)
	{
		LOG_ERROR(SEND_SOCKET_FAILS << client_fd);
		*send_socket_fails = true;
	}
}

void server::_cache_response(const Request & request, const int &listen_fd, const Response &the_response, const std::string &response)
{
	if (CACHED_TIME < 1)
		return ;
	if (request.get_method() == GET)
	{
		if (!the_response.get_cgi_responses())
		{
			cached_key key;
			key.fd = listen_fd;
			key.request = request.get_fullrequest();
			cached_value  cache;
			cache.response = response;
			cache.expired = std::time(NULL) + CACHED_TIME;
			_cached_responses[key] = cache;
		}
	}
	else if (!_cached_responses.empty() && (the_response.get_status_code() - 200) < 100 )
	{
		size_t count = 0;
		while (count != _cached_responses.size())
		{
			count = _cached_responses.size();
			std::map<cached_key, cached_value>::iterator it = _cached_responses.begin();
			for ( ; it != _cached_responses.end(); it++){
				if (it->first.fd == listen_fd){
					_cached_responses.erase(it->first);
					break;
				}
			}
		}
	}
}

void server::_expire_cached_responses()
{
	std::map<cached_key, cached_value>::iterator it = _cached_responses.begin();
	for ( ; it != _cached_responses.end(); it++){
		if (it->second.expired < std::time(NULL))
		{
			_cached_responses.erase(it->first);
			break;
		}
	}
}

}	// Nammespace ft
