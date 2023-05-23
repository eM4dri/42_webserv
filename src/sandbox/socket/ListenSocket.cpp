/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:38 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 11:42:02 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.hpp"
//Constructor
ft::ListenSocket::ListenSocket(int domain, int type, int protocol, u_long interface, int port, int backlog)
: BindSocket(domain, type, protocol, interface, port), _backlog(backlog)
{
	start_listen();
}

ft::ListenSocket::ListenSocket(int domain, int type, int protocol, int port, const char *address, int backlog)
:BindSocket(domain, type, protocol, port, address), _backlog(backlog)
{
	start_listen();
}

//Function to establish conection
void ft::ListenSocket::start_listen(){
	_listenfd = listen(get_socketfd(), _backlog);
}

//Gettters
int const &	ft::ListenSocket::get_listenfd() const{
	return _listenfd;
}
int const &	ft::ListenSocket::get_backlog() const{
	return _backlog;
}

