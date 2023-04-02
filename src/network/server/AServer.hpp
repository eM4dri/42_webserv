/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AServer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 10:55:45 by emadriga         ###   ########.fr       */
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

		//Virtual function to handle connections
		virtual void accepter() = 0;
		virtual void handler() = 0;
		virtual void responder() = 0;

	public:
		//Constructor
		AServer(int domain, int type, int protocol, u_long interface, int port, int backlog);
		AServer(int domain, int type, int protocol, int port, char *address, int backlog);

		//Virtual function to launch server
		virtual void launch(void) = 0;

		//Getters
		ListenSocket* get_listening_socket();
};

}//Namespace ft

#endif
