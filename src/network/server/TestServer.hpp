/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 11:58:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP
# include "AServer.hpp"
# define BUFFER_SIZE 3000
# include <iostream>


namespace ft
{

class TestServer: public AServer{
	private:
		char _buffer[BUFFER_SIZE];
		int _clientSocket;
		
		//Functions to handle connections
		void _accepter();
		void _handler();
		void _responder();

	public:
		//Constructor
		TestServer();

		//Function to  launch server
		void launch(void);
};

}//Namespace ft

#endif
