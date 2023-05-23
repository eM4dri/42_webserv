/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:28:53 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/23 16:38:09 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverconf.hpp"

ft::serverconf::serverconf(const Filetypes & types):	filetypes(types)
{

}

ft::serverconf::~serverconf()
{
	if(locations.size())
		locations.clear();
}

ft::serverconf::serverconf(const ft::serverconf & tocopy): address(tocopy.address), port(tocopy.port), default_root(tocopy.default_root), locations(tocopy.locations), filetypes(tocopy.filetypes)
{

}

