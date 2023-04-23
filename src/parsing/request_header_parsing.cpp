/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:03 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/23 20:21:59 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request_header_parsing.hpp"

/*
!	The error message might not be necessary, but an attempt to access somewhere over the root should be controlled and redirect back to the root.
!	This function is unused for now.
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

/*
?	This function takes a string that has a path starting from a root and 
?	checks whether there are attempts to access files over the root or not.
?	If there are, it will delete those attempts remaining within the allowed
?	boundaries and returning a string with a safe path.
*/
std::string correct_path(std::string orig_path)
{
	std::vector <std::string> routes = cpp_split(orig_path, '/');
	std::vector<std::string>::iterator curr_route = routes.end() - 1;
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

/*
?	Returns false if there's an error in the first line of a request and prints a
?	formatted error to the std::cerr. It also initialises a given `header_struct` structure.
*	What's being checked:
	*	Parameters == 3
	*	Valid method ("GET", "POST" and "DELETE").
	*	The verison is "HTTP1.1".
*/
bool	check_first_line_validity(std::string firstline, struct s_request_info &header_struct)
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
	if (params[0] != "GET" && params[0] != "POST" && params[0] != "DELETE")
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
	else
	{
		if (params[0] == "GET")
			header_struct.method = GET;
		if (params[0] == "POST")
			header_struct.method = POST;
		if (params[0] == "DELETE")
			header_struct.method = DELETE;
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
	else
		header_struct.http_version = "HTTP1.1";
	header_struct.path = correct_path(params[1]);
	return (true);
}

/*
?	This function will check whether the header (excluding the request line) is valid or not.
?	It also fills the std::map containing all of the header parameters.
*/
bool check_header_validity(std::vector <std::string> line_vector, std::map<std::string, std::string> &header_map)
{
	std::vector <std::string> pair;
	std::string body;
	for (std::vector<std::string>::iterator vector_iter = line_vector.begin() + 1; vector_iter != line_vector.end(); vector_iter++) 
	{
		body = "";
		pair = cpp_split(*vector_iter, ':');
		for (std::vector<std::string>::iterator pair_iter = pair.begin() + 1; pair_iter != pair.end(); pair_iter++)
		{
			body.append(*pair_iter);
			if (pair_iter + 1 != pair.end())
				body.append(":");
		}
		if (body[0] == ' ')
			body.erase(0, 1);
		header_map[pair[0]] = body;
	}
	return (true);
}

/*
?	Checks if all fo the testing worked out well.
*/
bool	check_request_validity(std::string fullrequest, struct s_request_info &header_struct, std::map<std::string, std::string> &header_map)
{
	std::vector <std::string> line_vector = cpp_split(fullrequest, '\n');
	if (!check_first_line_validity(line_vector[0], header_struct))
		return (false);
	if (!check_header_validity(line_vector, header_map))
		return (false);
	return (true);
	
}

/*
?	Fills out the stuct of the request's first line, the map of the rest of 
?	the header and the body into a string.
!	If there's no body, it will be left as an empty string ("").
*/
void header_parser(std::string fullrequest, struct s_request_info &header_struct, std::map<std::string, std::string> &header_map, std::string &body)
{
	size_t head_body_separation = fullrequest.find("\n\n");
	if (!check_request_validity(fullrequest.substr(0, head_body_separation), header_struct, header_map))
	{
		return ;
	}
	if (head_body_separation != std::string::npos)
		body = fullrequest.substr(head_body_separation + 2, std::string::npos);
	else
		body = "";
}
