/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 15:31:12 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"
//Constructor
ft::ASocket::ASocket(int domain, int type, int protocol,  u_long interface, int port){
	memset(&_address, 0,sizeof(_address));
	_address.sin_family = domain;
	_address.sin_addr.s_addr = htonl(interface);
	_address.sin_port = htons(port);

	_socketfd = socket(domain, type, protocol);

}
ft::ASocket::ASocket(int domain, int type, int protocol, int port, const char *address){
	memset(&_address, 0,sizeof(_address));
	_address.sin_family = domain;
	_address.sin_addr.s_addr = inet_addr(address);
	_address.sin_port = htons(port);

	_socketfd = socket(domain, type, protocol);

}

//Getters
int	const & ft::ASocket::get_socketfd() const{
	return _socketfd;
}
struct sockaddr_in const & ft::ASocket::get_address() const{
	return _address;
}
int	const & ft::ASocket::get_connectionStatus() const{
	return _connectionStatus;
}
//Setters
void ft::ASocket::set_connectionStatus(int status){
	_connectionStatus = status;
}
