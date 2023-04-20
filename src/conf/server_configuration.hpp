/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:24:33 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 19:59:37 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONFIGURATION_HPP
# define SERVER_CONFIGURATION_HPP
# include <string>		// std::string
// # include <map>			// std::map
// # include "location.hpp"

namespace ft
{
	// class location;

class server_configuration{
	public:
		//Constructor
		server_configuration(){};

		//Destructor
		~server_configuration(){};

		void	set_address( std::string address );
		void	set_port( unsigned short port );

		const std::string	&get_address() const;
		const unsigned short	&get_port() const;

		// std::vector<location>			*locations;
		// std::map<std::string,location>	*_locations;
	private:
		server_configuration( int var );
		server_configuration( const server_configuration& copy );
		server_configuration & operator=( const server_configuration& assign ); // Assignement Operator

	private:
		std::string								_address;
		unsigned short								_port;


};

}//Namespace ft

#endif

