/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_sockets.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:02:39 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/07 16:58:17 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "listen_sockets.hpp"
#include <fcntl.h>						//	fcntl
#include <cstring>						//	std::memset
#include <unistd.h>						//	close, sleep
#include "utils/log.hpp"

#define NOT_BINDED_MSG " socket_fd could not be binded on "
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
	bool error = false;
	const char *address_c_str = conf.address.c_str();
	int yes = 1;	//	for setsockopt() SO_REUSEADDR, below

	if (!_ip_already_used(conf))
	{
		socket_fd s;

		size_t address_sizeof = sizeof(s.address);
		std::memset(reinterpret_cast<void *>(&s.address), 0, address_sizeof);
		s.address.sin_family = AF_INET;
		s.address.sin_addr.s_addr = inet_addr( address_c_str );
		s.address.sin_port = htons(conf.port);
		s.address_len = static_cast<socklen_t>(address_sizeof);

		s.fd = socket(PF_INET, SOCK_STREAM, 0);
		setsockopt(s.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		fcntl(s.fd, F_SETFL, O_NONBLOCK);

		const struct sockaddr * ws_address = reinterpret_cast<struct sockaddr *>(&s.address);
		if ( -1 == bind(s.fd, ws_address, s.address_len) ){
			error = true;
			LOG_ERROR( s.fd << NOT_BINDED_MSG << address_c_str << ":" << conf.port);
		}
		if ( -1 == listen(s.fd, BACKLOG) ){
			error = true;
			LOG_ERROR( "listen");
		}
		if (error)
		{
			if ( 0 != close(s.fd))
				LOG_ERROR("closing listening socket");
		}
		if (!error)
		{
			LOG(SEVER_LISTENING(s.fd, address_c_str, conf.port));
			s.hosted_server_config[conf.server_name] = &conf;
			_sockets[s.fd] = s;
		}
	}
}

bool listen_sockets::_ip_already_used(const serverconf &conf)
{
	std::map<int, socket_fd>::iterator it = _sockets.begin();
	if (it != _sockets.end())
	{
		unsigned short used_port = it->second.hosted_server_config.begin()->second->port;
		std::string used_address = it->second.hosted_server_config.begin()->second->address;
		if ( conf.port == used_port && conf.address == used_address)
		{
			std::map<std::string, const serverconf *>::iterator notfound = it->second.hosted_server_config.find(conf.server_name);
			if (notfound == it->second.hosted_server_config.end())
				it->second.hosted_server_config[conf.server_name] = &conf;
			return true;
		}
	}
	return false;
}

const std::map<int, socket_fd> &listen_sockets::_get_sockets() const
{
	return _sockets;
}

}	// Nammespace ft
