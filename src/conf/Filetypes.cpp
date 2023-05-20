/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filetypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:55:30 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/19 15:29:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Filetypes.hpp"
#include "../utils/log.hpp"

namespace ft
{

/**
 * @param filetypes_status (bool *)  |  Will return false if the file required for this function is unavailable.
*/
Filetypes::Filetypes(bool *filetypes_status)
{
	std::ifstream	file_instream;
	std::string		file_line;
	std::vector<std::string>		line_couple;

	file_instream.open(FILETYPES);
	if (filetypes_status)
		*filetypes_status = true;
	if (!file_instream.is_open())
	{
		if (filetypes_status)
			*filetypes_status = false;
		return ;
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
	if (full_list.size())
		full_list.clear();
}

std::string Filetypes::get(const std::string &tosearch) const
{
	if (full_list.count(tosearch))
		return (full_list.find(tosearch)->second);
	return(DEFAULT_VALUE);
}

std::string Filetypes::get_suffix(const std::string &tosearch) const
{
	if (tosearch.size() < 1)
		return(DEFAULT_VALUE);
	size_t search_it = tosearch.find_last_of('.');
	if (search_it == std::string::npos)
		return(DEFAULT_VALUE);
	return (get(&tosearch[search_it + 1]));
}

}	// Nammespace ft
