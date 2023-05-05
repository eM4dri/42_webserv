/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:03 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/05 20:34:04 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../requests/Request.hpp"

/*
?	This function takes a string that has a path starting from a root and 
?	checks whether there are attempts to access files over the root or not.
?	If there are, it will delete those attempts remaining within the allowed
?	boundaries and returning a string with a safe path.
*/
static std::string correct_path(const std::string &orig_path)
{
	std::vector <std::string> routes = cpp_split(orig_path, '/');
	std::vector<std::string>::iterator curr_route = routes.end() - 1;
	std::vector<std::string>::iterator curr_route_aux = routes.end();
	std::string retval;
	int level = 0;
	if (!routes.size())
		return ("");
	while (curr_route != routes.begin())
	{
		if (*curr_route == "~")
			break;
		else
			curr_route--;
	}
	if (*curr_route == "~")
		curr_route++;
	curr_route_aux = curr_route;

	while (curr_route != routes.end())
	{
		if (*curr_route == "..")
		{
			if (level - 1 < 0)
				routes.erase(curr_route);
			else
			{
				routes.erase(curr_route);
				curr_route--;
				routes.erase(curr_route);
			}
				
		}
		else if (*curr_route == ".")
			routes.erase(curr_route);
		else
		{
			level++;
			curr_route++;
		}

	}
	while (curr_route_aux != routes.end())
	{
		retval.append("/");
		retval.append(*curr_route_aux);
		curr_route_aux++;
	}
	if (retval[0] == '/')
		retval = retval.substr(1, retval.size() - 1);
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
bool	Request::check_first_line_validity(std::string firstline)
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
			method = GET;
		if (params[0] == "POST")
			method = POST;
		if (params[0] == "DELETE")
			method = DELETE;
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
	path.unparsed = params[1];
	path.relative = correct_path(params[1]);
	path.absolute = SERVER_ROOT;
	path.absolute.append("/");
	path.absolute.append(path.relative);
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
bool	Request::check_request_validity(std::string fullheader)
{
	std::vector <std::string> line_vector = cpp_split(fullheader, '\n');
	if (!check_first_line_validity(line_vector[0]))
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
void Request::header_parser()
{
	size_t head_body_separation = fullrequest.find("\n\n");
	if (!check_request_validity(fullrequest.substr(0, head_body_separation)))
	{
		//TODO COMPLAIN
		return ;
	}
	if (head_body_separation != std::string::npos)
		body = fullrequest.substr(head_body_separation + 2, std::string::npos);
	else
		body = "";
}
