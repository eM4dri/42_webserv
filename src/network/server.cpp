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
#include "responses/Response.hpp"
// #include "actuators/cgi.hpp"
#include <unistd.h>						//	close
#include <cstdlib>						//	std::exit
#include "utils/log.hpp"
#include <signal.h>						//	signal, sig_atomic_t

#define BUFFER_SIZE 1024

#define WELCOME_MESSAGE "Hello from server\n"
#define NEW_CONNECTION "webserver: new client connects on socket "
#define CLIENT_HUNGUP "client hung up"
#define CLIENT_SAYS(Client) "client " << Client << ": "
#define SERVER_REPONSE "server response:"

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
	LOG( "SIGINT suthing down server" );
	stopServer = true;
}

//Function to start server
void server::_start(const listen_sockets &listening_sockets)
{
	signal(SIGINT, signal_handler);
	while (!stopServer)
	{
		if ( -1 == poll(reinterpret_cast<pollfd *>(&_poll_fds[0]), static_cast<nfds_t>(_poll_fds.size()), -1) )
		{
			LOG_ERROR("poll");
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
	}
}

//Function to stop server
void server::_stop(void)
{
	if (_poll_fds.size() > 0)
	{
		std::vector<struct pollfd>::iterator it = _poll_fds.begin();
		for( ; it != _poll_fds.end(); it++)
			close(it->fd);
		_poll_fds.clear();
	}
	if (!_client_server_conections.empty())
		_client_server_conections.clear();
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

void server::_handler(std::vector<struct pollfd>::iterator it, const listen_sockets &_listening_sockets)
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
		_client_server_conections.erase(it->fd);
		_poll_fds.erase(it);
	}
	else	// message from client
	{
		buffer[nbytes] = '\0';
		LOG(CLIENT_SAYS(it->fd));
		LOG_COLOR(RED, buffer );
		int fd = _client_server_conections.find(it->fd)->second;
		const serverconf &server_config = *_listening_sockets._get_sockets().find(fd)->second.server_config;
		Request request(buffer, server_config);
		_responder(it->fd, request);
		// _echo(it->fd, buffer, nbytes);
		// close(it->fd);
		_poll_fds.erase(it);
	}
}

const std::string _mock_html_response(const char *filename,  const Request & request, const std::string &content_type)
{
	(void)request;
	std::string response = "HTTP/1.1 200 OK\r\nContent-Type: "
							+ content_type
							+ "\r\n\r\n";
	std::ifstream ifs;
	ifs.open (filename, std::ifstream::in);

	if (ifs.is_open() == false)
	{
		LOG_ERROR("ERROR_OPENING_FILE");
		std::exit(1);
	}
	std::string contents;
	ifs.seekg(0, std::ios::end);
	contents.resize(ifs.tellg());
	ifs.seekg(0, std::ios::beg);
	ifs.read(&contents[0], contents.size());
	ifs.close();
	response.append(contents);
	return response;
}

const std::string _mock_cgi_response( const std::string & cgi_exec, const std::string & cgi_script, const Request & request , const serverconf & conf
									// , const std::string &content_type
)
{
	std::string response = "HTTP/1.1 200 OK\r\n";
	// std::string response = "HTTP/1.1 200 OK\r\nContent-Type: "
	// 					+ content_type
	// 					+ "\r\n\r\n";
	cgi aux(cgi_exec, cgi_script,request, conf);
	response.append(aux.get_cgi_response());
	return response;
}

void server::_responder(int client_fd, const Request & request)
{
	Response the_response(request);
	std::string response = the_response.generate_response();
	// std::string response = _mock_html_response("test_files/post/php-example.html", request, "text/html");
	// std::string response = _mock_html_response("test_files/post/newmessage.html", request, "text/html");
	// std::string response = _mock_cgi_response("cgi/bin/show_env.wexec", "",request, _conf);
	// std::string response = _mock_cgi_response("cgi/bin/cpp_env.wexec", "",request, _conf);
	// std::string response = _mock_cgi_response("cgi/bin/print_ls_la.sh", "",request, _conf);
	// std::string response = _mock_cgi_response("/bin/ls", "-la",request, _conf, "text/plain");
	// std::string response = _mock_cgi_response("/usr/local/bin/python3", "cgi/script/reply.py",request, _conf);
	// std::string response = _mock_cgi_response("/usr/local/bin/python3", "cgi/script/guestbook.py",request, _conf);
	// std::string response = _mock_cgi_response("/usr/local/bin/python3", "cgi/script/newcomment.py",request, _conf)
	LOG(SERVER_REPONSE);
	LOG_COLOR(GREEN, response);
	send(client_fd, reinterpret_cast<const void *>(response.c_str()), response.length(), 0);
}

}	// Nammespace ft
