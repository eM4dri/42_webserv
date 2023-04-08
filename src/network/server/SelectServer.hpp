/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SelectServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 15:40:39 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTSERVER_HPP
# define SELECTSERVER_HPP
# include "AServer.hpp"
# include <iostream>
# include <set>

namespace ft
{

class SelectServer: public AServer{
	private:
		fd_set 	_master;    // master file descriptor list
   		fd_set 	_read_fds;  // temp file descriptor list for select()
    	int 	_fdmax;     // maximum file descriptor number
		
		//Functions to handle connections
		void _accepter();
		void _handler(int client_fd);
		void _responder(int client_fd);
		void _echo(int client_fd, char const *str, size_t nbytes);

	public:
		//Constructor
		SelectServer(int domain, int type, int protocol, u_long interface, int port, int backlog);

		//Function to  launch server
		void launch(void);
};

}//Namespace ft

#endif
