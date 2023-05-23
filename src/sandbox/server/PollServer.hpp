/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/10 20:59:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLSERVER_HPP
# define POLLSERVER_HPP
# include "AServer.hpp"
# define BUFFER_SIZE 256
# include <vector>
# include <poll.h>

namespace ft
{

class PollServer: public AServer{
	public:
		//Constructor
		PollServer(int domain, int type, int protocol, u_long interface, int port, int backlog);
		~PollServer();

		//Function to  launch server
		void launch(void);
		
	private:
		PollServer();	// not necesary
		PollServer( const PollServer & copy );	// not necesary
		PollServer & operator=( const PollServer & assign );	// not necesary
		
		std::vector<struct pollfd> 				poll_fds;
		
		//Functions to handle connections
		void _accepter();
		void _handler(std::vector<struct pollfd>::iterator it);
		void _responder(int client_fd);
		void _echo(int fd, char const *str, size_t nbytes);
};

}//Namespace ft

#endif
