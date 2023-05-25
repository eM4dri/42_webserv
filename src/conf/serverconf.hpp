/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/24 20:37:22 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP
# include <string>		// std::string
# include <map>			// std::map
# include "location.hpp"
# include "Filetypes.hpp"
# define DEFAULT_ADDRESS "localhost"
# define DEFAULT_PORT 8080
# define DEFAULT_ROOT "www"
# define DEFAULT_SERVER_NAME "webserv v4.2"

namespace ft
{

/**
 * @param address	(std::string)
 * @param port		(unsigned short)
 * @param default_root		(std::string)
 * @param locations	(std::map<std::string, location>)
 * @param filetypes (const Filetypes &)
 * @warning Declare an object with ft::serverconf.
*/
class serverconf{
	public:
		std::string							address;
		unsigned short						port;
		std::string							default_root;
		std::map<std::string, location>		locations;
		const Filetypes &					filetypes;
		std::string							server_name;

		//Constructor
		serverconf(const Filetypes & types);

		//Destructor
		~serverconf();

		//Copy constructor
		serverconf(const ft::serverconf & tocopy);

};

}//Namespace ft

#endif

