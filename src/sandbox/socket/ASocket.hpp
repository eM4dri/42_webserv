/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 11:40:24 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET_HPP
# define ASOCKET_HPP
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string>

namespace ft
{

class ASocket{
	private:
		int					_socketfd;
		struct sockaddr_in	_address;
		int					_connectionStatus;

	public:
	// public:
		//Constructor
		ASocket(int domain, int type, int protocol, u_long interface, int port);
		ASocket(int domain, int type, int protocol, int port, const char * address);

		//Virtual function to establish conection
		virtual int connect_to(int socketfd, struct sockaddr_in address) = 0;

		//Getters
		int	const & get_socketfd() const;
		struct sockaddr_in	const & get_address() const;
		int	const & get_connectionStatus() const;

		//Setters
		void set_connectionStatus(int status);
};


}//Namespace ft

#endif
