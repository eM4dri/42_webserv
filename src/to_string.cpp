/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:39:12 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/24 15:43:12 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"


namespace ft
{

/*
?	This is a recreation of the std::to_string() function, that's only
?	available after C++11.
*/
std::string to_string(int number)
{
	std::ostringstream s;
	s << number;
	std::string output = s.str();
	return (output);
}

/*
*	Feel free to duplicate the function above and overload it with any other
*	variable type as input (long, const x, unsigned x...).
?	Remember to add the function prototype on ./general.hpp.
*/

}	// Namespace ft
