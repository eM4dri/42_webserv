/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:03 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/18 19:17:26 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request_header_parsing.hpp"

/*
!	The error message might not be necessary, but an attempt to access somewhere over the root should be controlled and redirect back to the root.
*/
bool	check_valid_path(std::string path)
{
	std::vector <std::string> routes = cpp_split(path, '/');
	std::vector<std::string>::iterator curr_route = routes.begin() + 1;
	int level = 0;

	while (curr_route != routes.end())
	{
		if (*curr_route == "..")
			level--;
		else if (*curr_route != ".")
			level++;
		if (level < 0)
		{
			std::cerr << "Error: Attempted to access files above the root." << std::endl << std::endl;
			std::vector<std::string>::iterator iter_route = routes.begin() + 1;
			while (iter_route != routes.end())
			{
				std::cerr << "/";
				if (iter_route == curr_route)
					std::cerr << TXT_BOLD_RED;
				std::cerr << *iter_route;
				std::cerr << TXT_RESET;
				iter_route++;
			}
			std::cerr << std::endl;
			return (false);
		}
		curr_route++;
	}
	return (true);
}

std::string correct_path(std::string orig_path)
{
	std::vector <std::string> routes = cpp_split(orig_path, '/');
	std::vector<std::string>::iterator curr_route = routes.end();
	std::vector<std::string>::iterator curr_route_aux = routes.end();
	std::string retval;
	int level = 0;
	while (curr_route != routes.begin())
	{
		if (*curr_route == "~")
			break;
		else
			curr_route--;
	}
	curr_route++;
	curr_route_aux = curr_route;

	while (curr_route != routes.end())
	{
		if (*curr_route == "..")
		{
			if (level - 1 < 0)
				routes.erase(curr_route);
			else
				level--;
		}
		else if (*curr_route != ".")
			level++;
		curr_route++;
	}
	while (curr_route_aux != routes.end())
	{
		retval.append("/");
		retval.append(*curr_route_aux);
		curr_route_aux++;
	}
	return (retval);
	
}

bool	check_first_line_validity(std::string firstline)
{
	std::vector <std::string> params = cpp_split(firstline, ' ');

	if (params.size() < 3)
	{
		std::cerr << "Error: Too few arguments (expected 3, got " << params.size() << ")." << std::endl << std::endl;
		std::cerr << TXT_COLOR_GREEN;
		for (unsigned long i = 0; i < params.size(); i++)
		{
			std::cerr << params[i] << " ";
		}
		std::cerr << TXT_COLOR_YELLOW << ">>>" << TXT_RESET << std::endl;
		return (false);
	}
	else if (params.size() > 3)
	{
		std::cerr << "Error: Too many arguments (expected 3, got " << params.size() << ")." << std::endl << std::endl;
		for (unsigned long i = 0; i < params.size(); i++)
		{
			if (i == 3)
				std::cerr << TXT_BOLD_RED;
			else if (!i)
				std::cerr << TXT_COLOR_GREEN;
			std::cerr << params[i] << " ";
		}
		std::cerr << TXT_RESET << std::endl;
		return (false);
	}
	if (params[0] != "GET" && params[0] != "POST" && params[1] != "DELETE")
	{
		std::cerr << "Error: Unrecognized method \"" << params[0] << "\"." << std::endl << std::endl;
		for (unsigned long i = 0; i < params.size(); i++)
		{
			if (i == 0)
				std::cerr << TXT_BOLD_RED;
			else if (i)
				std::cerr << TXT_RESET;
			std::cerr << params[i] << " ";
		}
		std::cerr << std::endl;
		return (false);
	}
	if (params[2] != "HTTP1.1" && params[2] != "HTTP/1.1")
	{
		std::cerr << "Error: HTTP version different to HTTP1.1" << std::endl << std::endl;
		for (unsigned long i = 0; i < params.size(); i++)
		{
			if (i == 2)
				std::cerr << TXT_BOLD_RED;
			else
				std::cerr << TXT_RESET;
			std::cerr << params[i] << " ";
		}
		std::cerr << TXT_RESET << std::endl;
		return (false);
	}
	if (!check_valid_path(params[1]))
		return (false);
	return (true);
}

bool	check_request_validity(std::string fullrequest)
{
	std::vector <std::string> line_vector = cpp_split(fullrequest, '\n');
	if (!check_first_line_validity(line_vector[0]))
		return(false);
	//TODO		Some more `if` statements with further testing functions missing.
	return (true);
	
}
