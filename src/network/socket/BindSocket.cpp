/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:24 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:51:48 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindSocket.hpp"
//Constructor
ft::BindSocket::BindSocket(int domain, int type, int protocol, u_long interface, int port)
: ASocket(domain, type, protocol, interface, port)
{
	int	socketfd = get_socketfd();
	struct sockaddr_in  address = get_address();

	set_connectionfd(connect_to(socketfd, address));
}

ft::BindSocket::BindSocket(int domain, int type, int protocol, int port, char *address)
:ASocket(domain, type, protocol, port, address)
{
	set_connectionfd(connect_to(get_socketfd(), get_address()));
}

//Function to establish conection
int ft::BindSocket::connect_to(int socketfd, struct sockaddr_in address){
	return bind(socketfd, (struct sockaddr *)&address, sizeof(address));
}


