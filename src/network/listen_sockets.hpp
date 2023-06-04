/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_sockets.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 09:51:52 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/04 21:10:22 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTEN_SOCKETS_HPP
# define LISTEN_SOCKETS_HPP
# include <arpa/inet.h>		// sockaddr_in, socklen_t
# include <map>				// std::map
# include "conf/conf.hpp"

namespace ft
{
struct socket_fd{
	int						fd;
	struct sockaddr_in		address;
	socklen_t				address_len;
	const serverconf		*server_config;
};

class listen_sockets{
	private:
		std::map<int, socket_fd> _sockets;

	public:
		listen_sockets(const conf &conf);
		~listen_sockets();
		const std::map<int, socket_fd> &_get_sockets() const;

	private:
		listen_sockets();	// not necesary
		listen_sockets( const listen_sockets & copy );	// not necesary
		listen_sockets & operator=( const listen_sockets & assign );	// not necesary

		//Function bind & listen a socket for a port in server directive of conf file
		void _listen_socket(const serverconf &conf);
};

}//Namespace ft

#endif
