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
# include <arpa/inet.h>		// sockaddr_in, socklen_t
# include <poll.h>			// pollfd
# include <vector>			// std::vector
# include "conf/conf.hpp"
# include "requests/Request.hpp"
# include "responses/Response.hpp"
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
		server(const serverconf &conf);
		~server();

	private:
		server();	// not necesary
		server( const server & copy );	// not necesary
		server & operator=( const server & assign );	// not necesary

		int								_server_fd;
		struct sockaddr_in				_address;
		socklen_t						_address_len;
		std::vector<struct pollfd>		_poll_fds;
		bool							_listening;
		const serverconf				&_conf;

		//Function to init server
		bool _init_server(const char *address, int port, int backlog);

		//Function to start server
		void _start();

		//Function to stop server
		void _stop();

		//Functions to handle connections
		void _accepter();
		void _handler(std::vector<struct pollfd>::iterator it);
		void _responder(int client_fd, const Request & request);
		void _echo(int fd, char const *str, size_t nbytes);
};


}//Namespace ft

#endif
