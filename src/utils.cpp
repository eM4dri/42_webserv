/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:30:58 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/15 21:18:54 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"

std::vector <std::string> cpp_split(std::string full_line, char splitter)
{
	std::vector <std::string> line_vector;
	std::string::iterator begin = full_line.begin();
	std::string::iterator end = full_line.begin();
	
	while (end != full_line.end() && *end == splitter)
	{
		end++;
		begin++;
	}
	while (end != full_line.end())
	{

		while (end != full_line.end() && *end != splitter)
			end++;
		if (end != full_line.end())
		{
			line_vector.push_back(std::string(begin, end));
			while (*end == splitter)
				end++;
		}
		else
			line_vector.push_back(std::string(begin, end));
		begin = end;
	}
	return (line_vector);
}
