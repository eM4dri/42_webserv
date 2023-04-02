/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 02:04:09 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AServer.hpp"
//Constructor
ft::AServer::AServer(int domain, int type, int protocol, u_long interface, int port, int backlog)
{
	_socket = new ListenSocket(domain, type, protocol, interface, port, backlog);
}
ft::AServer::AServer(int domain, int type, int protocol, int port, char *address, int backlog){
	_socket = new ListenSocket(domain, type, protocol, port, address, backlog);
}

//Getters
ft::ListenSocket* ft::AServer::get_listening_socket()
{
	return _socket;
}


