/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 18:28:58 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLSERVER_HPP
# define POLLSERVER_HPP
# include "AServer.hpp"
# define BUFFER_SIZE 256
# include <iostream>
#include <map>
#include <poll.h>


namespace ft
{

class PollServer: public AServer{
	private:
		// char _buffer[BUFFER_SIZE];
		// int _currentClientSocket;
		struct pollfd	*_pfds;
		int				_poll_fd_count;
		int				_poll_fd_size;
		
		//Functions to handle connections
		void _accepter();
		void _handler(int index_fd);
		void _responder(int client_fd);
		void _add_to_pfds(int newfd);
		void _del_from_pfds(int index_fd);
		void _echo(int index_fd, char const *str, size_t nbytes);

	public:
		//Constructor
		// PollServer();
		PollServer(int domain, int type, int protocol, u_long interface, int port, int backlog);
		// ~PollServer();

		//Function to  launch server
		void launch(void);
};

}//Namespace ft

#endif
