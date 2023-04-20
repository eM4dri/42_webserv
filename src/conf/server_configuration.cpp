/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_configuration.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:00:38 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 19:59:19 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_configuration.hpp"
// #include "utils/log.hpp"

namespace ft
{
//Public
//Constructor
server_configuration::server_configuration()
	:	_address("0.0.0.0"), _port(8080)
{
	// LOG("NEW SERVER");
}

//Destructor
server_configuration::~server_configuration()
{}

void	server_configuration::set_address( std::string address ){
	_address = address;
}
void	server_configuration::set_port( unsigned short port ){
	_port = port;
}

const std::string & server_configuration::get_address() const{
	return _address;
}
const unsigned short & server_configuration::get_port() const{
	return _port;
}

//Private


}	// Nammespace ft

