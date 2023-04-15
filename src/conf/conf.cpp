/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/15 18:22:13 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"
#include "utils/log.hpp"
#include <iostream>
#define ERROR_OPENING_FILE "Error opening file"

namespace ft
{

//Constructor
conf::conf( const char* filename )
{
	std::ifstream ifs (filename);

	if (ifs.is_open() == false)
	 	LOGERROR(ERROR_OPENING_FILE);	
	 {
	// print file:
		char c = ifs.get();
		while (ifs.good()) {
			std::cout << c;
			c = ifs.get();
		}
	}
	else {
		// show message:
		std::cout << "Error opening file";
	}
}

//Destructor
conf::~conf() {}

// int	conf::getVar() const {
// 	return _var;
// }
// void	conf::setVar( int input ) {
// 	_var = input;
// }
//Private

}	// Nammespace ft

