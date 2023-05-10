/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/10 15:07:59 by jvacaris         ###   ########.fr       */
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

namespace ft
{

struct location;
class Filetypes;

/**
 * @param address	(std::string)
 * @param port		(unsigned short)
 * @param root		(std::string)
 * @param locations	(std::map<std::string, location>)
 * @warning Declare an object with ft::serverconf.
*/
class serverconf{
	public:
		std::string							address;
		unsigned short						port;
		std::string							default_root;
		std::map<std::string, location>		locations;
		const Filetypes &					filetypes;

		//Constructor
		serverconf(const Filetypes & types)
			:	filetypes(types)
		{};

		//Destructor
		~serverconf()
		{
			if(locations.size())
				locations.clear();
		};

};

}//Namespace ft

#endif
