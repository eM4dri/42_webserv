/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:32 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 17:35:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTSOCKET_HPP
# define CONNECTSOCKET_HPP
# include "ASocket.hpp"

namespace ft
{

class ConnectSocket: public ASocket{
	public:
		//Constructor
		ConnectSocket(int domain, int type, int protocol, u_long interface, int port);
		ConnectSocket(int domain, int type, int protocol, int port, const char *address);

		//Function to establish conection
		int connect_to(int socketfd, struct sockaddr_in address);

};


}//Namespace ft

#endif
