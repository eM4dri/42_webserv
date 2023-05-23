/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 11:33:09 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AServer.hpp"
//Constructor
ft::AServer::AServer(int domain, int type, int protocol, u_long interface, int port, int backlog)
{
	_listeningSocket = new ListenSocket(domain, type, protocol, interface, port, backlog);
}
ft::AServer::AServer(int domain, int type, int protocol, int port, const char *address, int backlog){
	_listeningSocket = new ListenSocket(domain, type, protocol, port, address, backlog);
}

//Destructor
// ft::AServer::~AServer()
// {
// 	delete _socket;
// }

//Getters
ft::ListenSocket const & ft::AServer::get_listening_socket() const
{
	return *_listeningSocket;
}


