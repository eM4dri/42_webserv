/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 18:20:21 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASERVER_HPP
# define ASERVER_HPP
# include "../socket/fdlibc-socket.hpp"
# include <unistd.h>

namespace ft
{

class AServer{
	private:
		ListenSocket *		_socket;

		//Virtual functions to handle connections
		virtual void _accepter() = 0;
		virtual void _handler() = 0;
		virtual void _responder() = 0;

	public:
		//Constructor
		AServer(int domain, int type, int protocol, u_long interface, int port, int backlog);
		AServer(int domain, int type, int protocol, int port, const char *address, int backlog);
		//Destructor
		~AServer();

		//Virtual function to launch server
		virtual void launch(void) = 0;

		//Getters
		ListenSocket* get_listening_socket();
};

}//Namespace ft

#endif
