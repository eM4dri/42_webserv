/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:55:30 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/15 21:20:52 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filetypes.hpp"

Filetypes::Filetypes()
{
	std::ifstream	file_instream;
	std::string		file_line;
	std::vector<std::string>		line_couple;

	file_instream.open(FILETYPES);
	if (!file_instream.is_open())
	{
		//	COMPLAIN
	}
	std::getline(file_instream, file_line);
	while (std::getline(file_instream, file_line))
	{
		line_couple = cpp_split(file_line, ' ');
		for (std::vector<std::string>::iterator idx = line_couple.begin() + 1; idx != line_couple.end(); idx++)
		{
			if (*((*idx).end() - 1) == ';')
				full_list[(*idx).substr(0, idx->size() - 1)] = line_couple[0];
			else
				full_list[*idx] = line_couple[0];
		}
	}
}


Filetypes::~Filetypes()
{
}

std::string Filetypes::get(const std::string &tosearch)
{
	return (full_list[tosearch]);
}
