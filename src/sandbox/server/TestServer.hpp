/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 15:39:29 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP
# include "AServer.hpp"
# define BUFFER_SIZE 256
# include <iostream>


namespace ft
{

class TestServer: public AServer{
	private:
		char _buffer[BUFFER_SIZE];
		int _currentClientSocket;
		
		//Functions to handle connections
		void _accepter();
		void _handler();
		void _responder();

	public:
		//Constructor
		TestServer();
		TestServer(int domain, int type, int protocol, u_long interface, int port, int backlog);
		// ~TestServer();

		//Function to  launch server
		void launch(void);
};

}//Namespace ft

#endif
