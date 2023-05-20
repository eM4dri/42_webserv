/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:13:54 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/18 18:39:51 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/*Request::Request(const ft::serverconf &_config): fullrequest(""), config(_config)
{
	method = -2;
	path.absolute = "";
	path.relative = "";
	path.unparsed = "";
	body = "";
}*/

Request::Request(const std::string &_input, const ft::serverconf &_config): fullrequest(_input), config(_config)
{
	header_parser(_config);
}

Request::Request(Request &tocopy): fullrequest(tocopy.fullrequest), config(tocopy.config), \
method(tocopy.method), path(tocopy.path), header_map(tocopy.header_map), body(tocopy.body)
{
}

Request::Request(const Request &tocopy): fullrequest(tocopy.fullrequest), config(tocopy.config), \
method(tocopy.method), path(tocopy.path), header_map(tocopy.header_map), body(tocopy.body)
{
}

/*
TODO		Hasn't been tested yet. 
*/
void Request::set_redirect_path()
{
	std::string try_path;
	std::vector<std::string>::iterator ending = path.vec_relative.end();
	
	
	while (true)
	{
		try_path = "";
		for (std::vector<std::string>::iterator it = path.vec_relative.begin(); it != ending; it++)
		{
			if (it != path.vec_relative.begin())
				try_path.append("/");
			try_path.append(*it);
		}
		if (config.locations.find(try_path) != config.locations.end())
		{
			break ;
		}
		else
		{
			if (ending == path.vec_relative.begin())
				return ;
			else
				ending--;
		}
	}
	path.absolute = path.absolute.replace(path.absolute.find(try_path), try_path.length(), config.locations.find(try_path)->second.file_root);
	path.relative = path.absolute;
}

const std::string &Request::get_fullrequest() const
{
	return (fullrequest);
}

int Request::get_method() const
{
	return (method);
}

const std::string Request::get_method_txt() const
{
	if (method == GET)
		return ("GET");
	else if (method == POST)
		return ("POST");
	else if (method == DELETE)
		return ("DELETE");
	else
		return ("ERROR");

}

const std::string &Request::get_path_raw() const
{
	return (path.unparsed);
}

const std::string &Request::get_path_rel() const
{
	return (path.relative);
}

const std::string &Request::get_path_abs() const
{
	return (path.absolute);
}

const std::map<std::string, std::string> Request::get_headermap() const
{
	return(header_map);
}

const std::string &Request::get_body() const
{
	return(body);
}

const std::map<std::string, ft::location>::const_iterator &Request::get_dir_params() const
{
	return (it_location);
}

