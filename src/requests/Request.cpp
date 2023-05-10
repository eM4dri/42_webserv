/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:13:54 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/10 15:02:56 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(const ft::serverconf &_config): fullrequest(""), config(_config)
{
	method = -2;
	path.absolute = "";
	path.relative = "";
	path.unparsed = "";
	body = "";
}

Request::Request(const std::string &_input, const ft::serverconf &_config): fullrequest(_input), config(_config)
{
	header_parser();
}

Request::Request(Request &tocopy): fullrequest(tocopy.fullrequest), config(tocopy.config), \
method(tocopy.method), path(tocopy.path), header_map(tocopy.header_map), body(tocopy.body)
{
}

Request::Request(const Request &tocopy): fullrequest(tocopy.fullrequest), config(tocopy.config), \
method(tocopy.method), path(tocopy.path), header_map(tocopy.header_map), body(tocopy.body)
{
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

