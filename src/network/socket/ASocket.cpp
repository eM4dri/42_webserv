/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:51:15 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"
//Constructor
ft::ASocket::ASocket(int domain, int type, int protocol,  u_long interface, int port){

	// memset(&_address, 0,sizeof(_address));
	_address.sin_family = domain;
	_address.sin_addr.s_addr = htonl(interface);
	_address.sin_port = htons(port);

	_socketfd = socket(domain, type, protocol);

}
ft::ASocket::ASocket(int domain, int type, int protocol, int port, char *address){

	memset(&_address, 0,sizeof(_address));
	_address.sin_family = domain;
	_address.sin_addr.s_addr = inet_addr(address);
	_address.sin_port = htons(port);

	_socketfd = socket(domain, type, protocol);

}

//Getters
int	ft::ASocket::get_socketfd() const{
	return _socketfd;
}
struct sockaddr_in ft::ASocket::get_address() const{
	return _address;
}
int	ft::ASocket::get_connectionfd() const{
	return _connectionfd;
}
//Setters
void ft::ASocket::set_connectionfd(int connection){
	_connectionfd = connection;
}
