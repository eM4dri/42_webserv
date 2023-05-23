/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:41 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/08 11:41:46 by emadriga         ###   ########.fr       */
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
		ListenSocket(int domain, int type, int protocol, int port, const char *address, int backlog);

		//Function to establish conection
		void start_listen();

		//Getters
		int	const & get_listenfd() const;
		int	const & get_backlog() const;

};


}//Namespace ft

#endif
