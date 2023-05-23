/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:28:53 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/23 15:43:25 by emadriga         ###   ########.fr       */
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
