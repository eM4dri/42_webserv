/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:52:34 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectSocket.hpp"
//Constructor
ft::ConnectSocket::ConnectSocket(int domain, int type, int protocol, u_long interface, int port)
:ASocket(domain, type, protocol, interface, port)
{
	set_connectionfd(connect_to(get_socketfd(), get_address()));
}

ft::ConnectSocket::ConnectSocket(int domain, int type, int protocol, int port, char *address)
:ASocket(domain, type, protocol, port, address)
{
	set_connectionfd(connect_to(get_socketfd(), get_address()));
}

//Function to establish conection
int ft::ConnectSocket::connect_to(int socketfd, struct sockaddr_in address){
	return connect(socketfd, (struct sockaddr *)&address, sizeof(address));
}


