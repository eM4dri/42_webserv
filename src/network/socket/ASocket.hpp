/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:51:27 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET_HPP
# define ASOCKET_HPP
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>

namespace ft
{

class ASocket{
	private:
		int					_socketfd;
		struct sockaddr_in	_address;
		int					_connectionfd;

	public:
		//Constructor
		ASocket(int domain, int type, int protocol, u_long interface, int port);
		ASocket(int domain, int type, int protocol, int port, char *address);

		//Virtual function to establish conection
		virtual int connect_to(int socketfd, struct sockaddr_in address) = 0;

		//Getters
		int	get_socketfd() const;
		struct sockaddr_in	get_address() const;
		int	get_connectionfd() const;

		//Setters
		void set_connectionfd(int connection);
};


}//Namespace ft

#endif
