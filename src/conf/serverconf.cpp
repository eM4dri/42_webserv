/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:28:53 by jvacaris          #+#    #+#             */
/*   Updated: 2023/06/05 19:31:55 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverconf.hpp"


namespace ft
{

serverconf::serverconf(const Filetypes & types):	filetypes(types)
{
}

serverconf::~serverconf()
{
	if(locations.size())
		locations.clear();
}

serverconf::serverconf(const serverconf & tocopy):	address(tocopy.address),
													port(tocopy.port),
													default_root(tocopy.default_root),
													locations(tocopy.locations),
													filetypes(tocopy.filetypes),
													server_name(tocopy.server_name)
{
}


}	// Nammespace ft
