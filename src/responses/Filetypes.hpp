/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filetypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:55:36 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/06 15:32:06 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILETYPES_HPP
# define FILETYPES_HPP

#include "../general.hpp"
#define FILETYPES "conf/mime.types"
#define DEFAULT_VALUE ""

/*
?		This class is used to retrieve the Content-Type of a file
*		(check https://www.nginx.com/resources/wiki/start/topics/examples/full/#mime-types)
?		by introducing the suffix of a file or the full name of a file.
*/
class Filetypes
{
	private:
		std::map <std::string, std::string> full_list;
	public:
		Filetypes(bool *filetypes_status);
		~Filetypes();
		std::string get(const std::string &tosearch);
		std::string get_suffix(const std::string &tosearch);

};

#endif
