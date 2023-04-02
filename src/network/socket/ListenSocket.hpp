/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:52:17 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENSOCKET_HPP
# define LISTENSOCKET_HPP
# include "BindSocket.hpp"

namespace ft
{

class ListenSocket: public BindSocket{
	private:
		int	_listenfd;
		int	_backlog;

	public:
		//Constructor
		ListenSocket(int domain, int type, int protocol, u_long interface, int port, int backlog);
		ListenSocket(int domain, int type, int protocol, int port, char *address, int backlog);

		//Function to establish conection
		void start_listen();

		//Getters
		int	get_listenfd() const;
		int	get_backlog() const;

};


}//Namespace ft

#endif
