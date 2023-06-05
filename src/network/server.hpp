/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 19:11:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <poll.h>				// pollfd
# include <vector>				// std::vector
# include <map>					// std::map
# include "conf/conf.hpp"
# include "requests/Request.hpp"
# include "network/listen_sockets.hpp"

namespace ft
{

// class serverconf;
// class Request;

/**
 * @param _server_fd	(int)
 * @param _address	(struct sockaddr_in)
 * @param _address_len	(socklen_t)
 * @param _poll_fds	(std::vector<struct pollfd>)
 * @param _listening	(bool)
 * @param _conf	(const serverconf &)
 * @warning Declare this class with ft::server
*/
class server{
	public:
		//Constructor
		server(const char* filename);
		~server();

	private:
		server();	// not necesary
		server( const server & copy );	// not necesary
		server & operator=( const server & assign );	// not necesary

		std::vector<struct pollfd>		_poll_fds;
		std::map<int,int>				_client_server_conections;

		//Add listening Soxckets to poll
		void _add_listening_sockets_to_poll(const listen_sockets &_listening_sockets);

		//Function to start server
		void _start(const listen_sockets &_listening_sockets);

		//Function to stop server
		void _stop();

		//Functions to handle connections
		void _accepter(const socket_fd& listen_socket);
		void _handler(std::vector<struct pollfd>::iterator it, const listen_sockets &_listening_sockets);
		void _responder(int client_fd, const Request & request);
};


}//Namespace ft

#endif
