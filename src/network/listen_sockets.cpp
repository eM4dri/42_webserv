/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_sockets.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:02:39 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/04 21:11:04 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listen_sockets.hpp"
#include <fcntl.h>						//	fcntl
#include <cstring>						//	std::memset
#include <unistd.h>						//	close, sleep
#include "utils/log.hpp"

#define BINDING_RETRYS 10
#define TIME_TO_RETRY 5
#define RETRY_BIND_MSG "Retry bind ..."
#define NOT_BINDED_MSG "socket_fd could not be binded on"
#define SEVER_LISTENING(serverfd, address, port) "webserver: new server with socket_fd " << serverfd << " is listening on " << address << ":" << port
#define BACKLOG 256

namespace ft
{
listen_sockets::listen_sockets(const conf &conf)
{
	std::vector<serverconf>::const_iterator it,ite;
	it = conf.servers.begin();
	ite = conf.servers.end();
	for ( ; it != ite; it++)
		_listen_socket(*it);
}

listen_sockets::~listen_sockets()
{
	if (!_sockets.empty())
		_sockets.clear();
}

void listen_sockets::_listen_socket(const serverconf &conf)
{
	const char *address_c_str = conf.address.c_str();
	int yes = 1;	//	for setsockopt() SO_REUSEADDR, below
	socket_fd s;

	s.server_config = &conf;
	size_t address_sizeof = sizeof(s.address);
	std::memset(reinterpret_cast<void *>(&s.address), 0, address_sizeof);
	s.address.sin_family = AF_INET;
	s.address.sin_addr.s_addr = inet_addr( address_c_str );
	s.address.sin_port = htons(conf.port);
	s.address_len = static_cast<socklen_t>(address_sizeof);

	s.fd = socket(PF_INET, SOCK_STREAM, 0);
	setsockopt(s.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	fcntl(s.fd, F_SETFL, O_NONBLOCK);

	short retrys = BINDING_RETRYS;
	const struct sockaddr * ws_address = reinterpret_cast<struct sockaddr *>(&s.address);
	while ( -1 == bind(s.fd, ws_address, s.address_len) && retrys-- ){
		LOG(RETRY_BIND_MSG);
		sleep(TIME_TO_RETRY);
	}
	if (retrys == 0){
		close(s.fd);
		LOG_ERROR( s.fd << NOT_BINDED_MSG << address_c_str << ":" << conf.port);
	}
	if ( -1 == listen(s.fd, BACKLOG) ){
		LOG_ERROR( "listen");
	}
	LOG(SEVER_LISTENING(s.fd, address_c_str, conf.port));
	_sockets[s.fd] = s;
}

const std::map<int, socket_fd> &listen_sockets::_get_sockets() const
{
	return _sockets;
}

}	// Nammespace ft
