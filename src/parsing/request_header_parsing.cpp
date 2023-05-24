/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:03 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/24 14:53:41 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../requests/Request.hpp"


/*
?	Returns false if there's an error in the first line of a request and prints a
?	formatted error to the std::cerr. It also initialises a given `header_struct` structure.
*	What's being checked:
	*	Parameters == 3
	*	Valid method ("GET", "POST" and "DELETE").
	*	The verison is "HTTP1.1".

!	UPDATE:	The formatting won't be transfered into the error page, so the formatting is
!			useless for now (except for debugging purposes). Most of it has been commented.
!			If there's time, we can pass some explanation about the error to the returned page.
*/
bool	Request::check_first_line_validity(std::string firstline, const ft::serverconf &_config)
{
	std::vector <std::string> params = cpp_split(firstline, ' ');

	if (params.size() < 3)
	{
		// std::cerr << "Error: Too few arguments (expected 3, got " << params.size() << ")." << std::endl << std::endl;
		// std::cerr << TXT_COLOR_GREEN;
		// for (unsigned long i = 0; i < params.size(); i++)
		// {													//? Uncomment if necessary for testing
		// 	std::cerr << params[i] << " ";
		// }
		// std::cerr << TXT_COLOR_YELLOW << ">>>" << TXT_RESET << std::endl;
		return (false);
	}
	else if (params.size() > 3)
	{
		// std::cerr << "Error: Too many arguments (expected 3, got " << params.size() << ")." << std::endl << std::endl;
		// for (unsigned long i = 0; i < params.size(); i++)
		// {													//? Uncomment if necessary for testing
		// 	if (i == 3)
		// 		std::cerr << TXT_BOLD_RED;
		// 	else if (!i)
		// 		std::cerr << TXT_COLOR_GREEN;
		// 	std::cerr << params[i] << " ";
		// }
		// std::cerr << TXT_RESET << std::endl;
		return (false);
	}
	if (params[0] != "GET" && params[0] != "POST" && params[0] != "DELETE")
	{
		// std::cerr << "Error: Unrecognized method \"" << params[0] << "\"." << std::endl << std::endl;
		// for (unsigned long i = 0; i < params.size(); i++)
		// {													//? Uncomment if necessary for testing
		// 	if (i == 0)
		// 		std::cerr << TXT_BOLD_RED;
		// 	else if (i)
		// 		std::cerr << TXT_RESET;
		// 	std::cerr << params[i] << " ";
		// }
		// std::cerr << std::endl;
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
	// 	// std::cout << "BBBBB    >"<< std::endl;
	// 	// std::cout << "AAAAAAAAAAAAAA    >"  << std::endl;
	// 	// std::cout << "$" << params[2] << "$" << std::endl;
	// 	// std::cout<<  "< vs >HTTP/1.1<" << std::endl;
	if (params[2] != "HTTP1.1" && params[2] != "HTTP/1.1")
	// // if (params[2] != "HTTP1.1" && params[2] != "HTTP1.1\r" && params[2] != "HTTP/1.1\r" && params[2] != "HTTP/1.1")
	{
		// std::cerr << "Error: HTTP version different to HTTP1.1" << std::endl << std::endl;
		// for (unsigned long i = 0; i < params.size(); i++)
		// {													//? Uncomment if necessary for testing
		// 	if (i == 2)
		// 		std::cerr << TXT_BOLD_RED;
		// 	else
		// 		std::cerr << TXT_RESET;
		// 	std::cerr << params[i] << " ";
		// }
		// std::cerr << TXT_RESET << std::endl;
		// // std::cout << "bolean " <<  (params[2] != "HTTP/1.1") << " compare " <<  params[2].compare( "HTTP/1.1") << std::endl;
		method = -2;
		return (false);
	}
	path.unparsed = params[1];


	std::string path_iter;
	path_iter = correct_path(params[1]);
	std::vector<std::string> split_path = cpp_split(path_iter, '/');
	unsigned int level = split_path.size();
	std::map<std::string, ft::location>::const_iterator it_location;
	while (path_iter.size() >= 0)	//!		Might enter an infinite loop. Check it out later.
	{
		 it_location = _config.locations.find(path_iter);
		if (it_location == _config.locations.end())
		{
			size_t last_slash = path_iter.find_last_of('/');
			if (last_slash == std::string::npos)
				path_iter = "";
			else
				path_iter = path_iter.substr(0, last_slash); //! Add a -1 after last_slash if is appends a '/'.
			level--;
		}
		else
		{
			location = &it_location->second;
			break;
		}
	}

	path.relative = correct_path(location->file_root);

	while (level < split_path.size())
	{
		path.relative.append("/");
		path.relative.append(split_path[level++]);
	}
	path.vec_relative = cpp_split(path.relative, '/');
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
bool	Request::check_request_validity(std::string fullheader, const ft::serverconf &_config)
{
	std::vector <std::string> line_vector = cpp_splitNremove(fullheader, '\n', '\r');
	if (!check_first_line_validity(line_vector[0], _config))
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
void Request::header_parser(const ft::serverconf &_config)
{
	size_t head_body_separation = fullrequest.find("\n\n");
	if (!check_request_validity(fullrequest.substr(0, head_body_separation), _config))
	{
		if (method != -2)
			method = -1;
		return ;
	}
	if (head_body_separation != std::string::npos)
		body = fullrequest.substr(head_body_separation + 2, std::string::npos);
	else
		body = "";
}
