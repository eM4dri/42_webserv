/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:13:54 by jvacaris          #+#    #+#             */
/*   Updated: 2023/06/08 14:51:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

namespace ft
{

Request::Request(const std::string &input, const serverconf &config): config(config), _fullrequest(input)
{
	header_parser(config);
}

Request::Request(Request &tocopy): config(tocopy.config), _fullrequest(tocopy._fullrequest), \
_method(tocopy._method), _path(tocopy._path), _header_map(tocopy._header_map), _body(tocopy._body), _location(tocopy._location)
{
}

Request::Request(const Request &tocopy): config(tocopy.config), _fullrequest(tocopy._fullrequest), \
_method(tocopy._method), _path(tocopy._path), _header_map(tocopy._header_map), _body(tocopy._body), _location(tocopy._location)
{
}

Request::~Request()
{
	if (_header_map.size())
		_header_map.clear();
	if (_path.vec_relative.size())
		_path.vec_relative.clear();
}

/*
TODO		Hasn't been tested yet.
*/
void Request::set_redirect_path()
{
	std::string try_path;
	std::vector<std::string>::iterator ending = _path.vec_relative.end();


	while (true)
	{
		try_path = "";
		for (std::vector<std::string>::iterator it = _path.vec_relative.begin(); it != ending; it++)
		{
			if (it != _path.vec_relative.begin())
				try_path.append("/");
			try_path.append(*it);
		}
		if (config.locations.find(try_path) != config.locations.end())
		{
			break ;
		}
		else
		{
			if (ending == _path.vec_relative.begin())
				return ;
			else
				ending--;
		}
	}
	_path.absolute = _path.absolute.replace(_path.absolute.find(try_path), try_path.length(), config.locations.find(try_path)->second.file_root);
	_path.relative = _path.absolute;
}

const std::string &Request::get_fullrequest() const
{
	return (_fullrequest);
}

int Request::get_method() const
{
	return (_method);
}

const std::string Request::get_method_txt() const
{
	if (_method == GET)
		return ("GET");
	else if (_method == POST)
		return ("POST");
	else if (_method == DELETE)
		return ("DELETE");
	else
		return ("ERROR");

}

const std::string &Request::get_path_raw() const
{
	return (_path.unparsed);
}

const std::string &Request::get_path_rel() const
{
	return (_path.relative);
}

const std::string &Request::get_path_abs() const
{
	return (_path.absolute);
}

const std::map<std::string, std::string> &Request::get_headermap() const
{
	return(_header_map);
}

const std::string &Request::get_body() const
{
	return(_body);
}

const location *Request::get_location() const
{
	return (_location);
}

const bool &Request::get_keep_connection_alive() const
{
	return (_keep_connection_alive);
}

}	// Nammespace ft
