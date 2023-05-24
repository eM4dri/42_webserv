/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filetypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:55:36 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/24 19:58:58 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILETYPES_HPP
# define FILETYPES_HPP

#include "../general.hpp"
#define FILETYPES "conf/mime.types"
#define DEFAULT_VALUE "text/plain"

namespace ft
{
/*
?		This class is used to retrieve the Content-Type of a file
*		(check https://www.nginx.com/resources/wiki/start/topics/examples/full/#mime-types)
?		by introducing the suffix of a file or the full name of a file.
?		Declare an object with ft::serverconf.
*/
class Filetypes
{
	private:
		std::map <std::string, std::string> full_list;
	public:
		Filetypes(bool *filetypes_status);
		~Filetypes();

		std::string get(const std::string &tosearch) const;
		std::string get_suffix(const std::string &tosearch) const;

};

}//Namespace ft

#endif
