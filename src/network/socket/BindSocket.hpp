/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 16:21:34 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP
# include "ASocket.hpp"

namespace ft
{

class BindSocket: public ASocket{
	public:
		//Constructor
		BindSocket(int domain, int type, int protocol, u_long interface, int port);
		BindSocket(int domain, int type, int protocol, int port, const char *address);

		//Function to establish conection
		int connect_to(int socketfd, struct sockaddr_in address);

};


}//Namespace ft

#endif
