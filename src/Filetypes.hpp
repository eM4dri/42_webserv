/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:55:36 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/15 21:26:34 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILETYPES_HPP
# define FILETYPES_HPP

#include "general.hpp"

/*
?		This class is used to retrieve the Content-Type of a file
*		(check https://www.nginx.com/resources/wiki/start/topics/examples/full/#mime-types)
?		by introducing the suffix of a file.

TODO	Give the whole file name and get the suffix automatically.
*/
class Filetypes
{
	private:
		std::map <std::string, std::string> full_list;
	public:
		Filetypes();
		~Filetypes();
		std::string get(const std::string &tosearch);

};

#endif
