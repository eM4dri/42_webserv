/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:18 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/02 17:24:57 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP
# include <string>		// std::string
# include <map>			// std::map
# include "location.hpp"
# define DEFAULT_ADDRESS "localhost"
# define DEFAULT_PORT 8080
# define DEFAULT_ROOT "www"

namespace ft
{

struct location;

/**
 * @param address	(std::string)
 * @param port		(unsigned short)
 * @param root		(std::string)
 * @param locations	(std::map<std::string, location>)
*/
class serverconf{
	public:
		std::string							address;
		unsigned short						port;
		std::string							root;
		std::map<std::string, location>		locations;

		//Constructor
		// serverc();

		//Destructor
		~serverconf()
		{
			if(locations.size())
				locations.clear();
		};

};

}//Namespace ft

#endif
