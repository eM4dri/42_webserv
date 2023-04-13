/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 19:11:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <vector>
# include <poll.h>
# include <arpa/inet.h>


namespace ft
{

class server{
	public:
		//Constructor
		server(const char *address, int port, int backlog);
		~server();
		
	private:
		server();	// not necesary
		server( const server & copy );	// not necesary
		server & operator=( const server & assign );	// not necesary
		
		int								_server_fd;
		struct sockaddr_in				_address;
		socklen_t						_address_len;
		std::vector<struct pollfd> 		_poll_fds;
		bool							_listening;
		
		//Function to init server
		bool _init_server(const char *address, int port, int backlog);

		//Function to start server
		void _start(void);

		//Function to stop server
		void _stop(void);

		//Functions to handle connections
		void _accepter();
		void _handler(std::vector<struct pollfd>::iterator it);
		void _responder(int client_fd);
		void _echo(int fd, char const *str, size_t nbytes);
};
		

}//Namespace ft

#endif
