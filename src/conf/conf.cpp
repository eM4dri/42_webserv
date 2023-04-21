/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/21 23:30:28 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"
#include "utils/log.hpp"
# include <string>		// std::string, std::getline
# include <vector>		// std::vector
#include <fstream>		// std::ifstream
#include <sstream>		// std::stringstream
#include <iostream>		// std::out, std::endl
#include <locale>		// std::locale, std::isspace
#include <cstdlib>		// std::exit
#include <cstring>		//	std::strcpy

#define ERROR_OPENING_FILE "Error opening file"
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define NUMBER_CHARACTERS "0123456789"
#define INVALID_CONF_FILE_END "Invalid configuration file, not allowed ending directory"
#define INVALID_CONF_FILE_BRACES "Invalid configuration file, curly braces not closed"
#define INVALID_CONF_UNKOWN_DIRECTIVE "Invalid configuration file, unknown key directive"

enum e_curly_braces_level{
	CLOSED,
	OPEN_SERVER,
	OPEN_LOCATION
};

namespace ft
{

//Constructor
conf::conf( const char* filename )
{
	std::ifstream ifs;
	// serverc *sc;

	ifs.open (filename, std::ifstream::in);
	// std::ifstream ifs (filename);
	std::string	line;

	if (ifs.is_open() == false)
	{
	 	LOG_ERROR(ERROR_OPENING_FILE);
		std::exit(1);
	}
	while (std::getline(ifs, line))
		_processLine(line);
	_validate_conf();
	_print_processed_conf();
	_load_configuration();
	LOG("HOLA");
	LOG(servers.size());
	for (std::vector<serverconf>::iterator it=servers.begin(); it!=servers.end(); ++it){
		LOG(it->address <<":"<< it->port );
		for (std::map<std::string, location>::iterator it2=it->locations.begin(); it2!=it->locations.end(); ++it2){
			LOG(it2->first);
			LOG("\t " << it2->second.autoindex);
			LOG("\t " << it2->second.client_max_body_size);
			LOG("\t " << it2->second.index);
			LOG("\t " << it2->second.methods);
			LOG("\t " << it2->second.redirect);
			LOG("\t " << it2->second.path);
		}
	}

}

//Destructor
conf::~conf()
{
	if (_conf.size())
		_conf.clear();
	if (servers.size())
		servers.clear();
	if (_valid_conf_keys.size())
		_valid_conf_keys.clear();
	if (_accepted_methods.size())
		_accepted_methods.clear();
}

void conf::_parse_path(std::string root, location *location)
{
	//TODO validate format
	location->path = root.substr(0, root.find_first_of(ISSPACE_CHARACTERS));
}

void conf::_parse_methods(std::string methods, location *location)
{
	//TODO validate format
	location->methods = 0;
	short	bit;
	bit = 0;
	std::stringstream ss(methods);
	std::string method;
	while (std::getline(ss, method, ' ')){
		bit = 0;
		for (std::vector<std::string>::const_iterator it = _accepted_methods.begin(); it!=_accepted_methods.end(); it++ )
		{
			if ( method == *it )
			{
				location->methods |= (1<<bit);
				break;
			}
			bit++;
		}
	}
}
void conf::_parse_autoindex(std::string autoindex, location *location)
{
	//TODO validate format
	location->autoindex = (autoindex == "on");
}
void conf::_parse_client_max_body_size(std::string client_max_body_size, location *location)
{
	//TODO validate format
	location->client_max_body_size = std::atoi(client_max_body_size.c_str());
}
void conf::_parse_index(std::string index, location *location)
{
	//TODO validate format
	location->index = index;
}
void conf::_parse_redirect(std::string redirect, location *location)
{
	//TODO validate format
	location->redirect = redirect;
}

void conf::_parse_location_directive(std::pair <std::string,std::string> conf, location *location)
{
	if (conf.first == "root")
		_parse_path(conf.second, location);
	else if (conf.first == "index")
		_parse_index(conf.second, location);
	else if (conf.first == "client_max_body_size")
		_parse_client_max_body_size(conf.second, location);
	else if (conf.first == "autoindex")
		_parse_autoindex(conf.second, location);
	else if (conf.first == "redirect")
		_parse_redirect(conf.second, location);
	else if (conf.first == "methods")
		_parse_methods(conf.second, location);
}

unsigned short _setPort(std::string str_port)
{
	return (std::atoi(str_port.c_str()));
}

void conf::_parse_listen(std::string listen, serverconf *server)
{
	//TODO validate format
	size_t port_start = listen.find_first_of(":");
	if (port_start == std::string::npos)
		server->port = std::atoi(listen.c_str());
	else
	{
		server->address = listen.substr(0, port_start);
		server->port = _setPort(&listen[port_start + 1]);
	}
}

void conf::_parse_root(std::string root, serverconf *server)
{
	//TODO validate format
	server->root = root;
}

void conf::_parse_server_directive(std::pair<std::string,std::string> conf, serverconf *server)
{
	if (conf.first == "listen")
		_parse_listen(conf.second, server);
	if (conf.first == "root")
		_parse_root(conf.second, server);
}

void _set_server_defaults(serverconf *server)
{
	server->address = DEFAULT_ADDRESS;
	server->port = DEFAULT_PORT;
	server->root = DEFAULT_ROOT;
	if (server->locations.size())
		server->locations.clear();
}

void _set_location_defaults(location *location)
{
	location->methods = GET;
	location->autoindex = DEFAULT_AUTOINDEX;
	location->path = DEFAULT_PATH;
	location->client_max_body_size = DEFAULT_CLIENT_MAX_BODY_SIZE;
	location->index = DEFAULT_INDEX;
}

void conf::_load_configuration()
{
	int	curly_braces_level = CLOSED;
	serverconf server;
	location location;
	_load_acepted_methods();
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first == "}")
		{
			curly_braces_level--;
			if (curly_braces_level == CLOSED)
				servers.push_back(server);
			else if (curly_braces_level == OPEN_SERVER)
				server.locations.insert(std::make_pair(location.path, location));
		}
		else if (it->second[it->second.length() - 1] == '{')
		{
			curly_braces_level++;
			if (curly_braces_level == OPEN_SERVER)
				_set_server_defaults(&server);
			else if (curly_braces_level == OPEN_LOCATION)
				_set_location_defaults(&location);
		}
		if (curly_braces_level == OPEN_SERVER)
			_parse_server_directive(*it, &server);
		else if (curly_braces_level == OPEN_LOCATION)
			_parse_location_directive(*it, &location);
	}
}

void conf::_print_processed_conf()
{
	int	curly_braces_count;
	curly_braces_count = 0;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first == "}")
			curly_braces_count--;
		for(int i = 0; i != curly_braces_count; i++)
			std::cout << "\t";
		LOG(it->first << "\t" << it->second );
		if (it->second[it->second.length() - 1] == '{')
			curly_braces_count++;
	}
}

void conf::_load_valid_conf_keys()
{
	_valid_conf_keys.insert("}");
	_valid_conf_keys.insert("location");
	_valid_conf_keys.insert("root");
	_valid_conf_keys.insert("listen");
	_valid_conf_keys.insert("methods");
	_valid_conf_keys.insert("autoindex");
	_valid_conf_keys.insert("server");
	_valid_conf_keys.insert("return");
	_valid_conf_keys.insert("server_name");
	_valid_conf_keys.insert("client_max_body_size");
}

void conf::_load_acepted_methods()
{
	_accepted_methods.push_back("GET");
	_accepted_methods.push_back("DELETE");
	_accepted_methods.push_back("POST");
}

void conf::_validate_conf()
{
	_load_valid_conf_keys();
	int	curly_braces_count;
	curly_braces_count = 0;
	char second_back;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		second_back = (it->second.length() == 0) ? '\0' : it->second[it->second.length() - 1];
		if (it->first != "}" && second_back != '{' && second_back != ';')
			// Every directive ends with semicolon or cruly braces (simple/block directive)
			LOG_ERROR(INVALID_CONF_FILE_END);
		else
		{
			if (it->first == "}")
				curly_braces_count--;
			else if (second_back == '{')
				curly_braces_count++;
			if( _valid_conf_keys.find(it->first) == _valid_conf_keys.end() )
				// Unkown key directive
				LOG_ERROR(INVALID_CONF_UNKOWN_DIRECTIVE);
		}
	}
	if (curly_braces_count != 0)
		// Curly braces must have start & end
		LOG_ERROR(INVALID_CONF_FILE_BRACES);
}

void conf::_processLine(std::string line)
{
	size_t	key_start = 0;
	while (std::isspace(line[key_start], std::locale()))
			key_start++;
	if (key_start > 0)
		line.erase(0,key_start);
	size_t comment_start = line.find_first_of('#', 0);
	if (comment_start != std::string::npos)	//remove comments
	{
		while (comment_start > 0 && std::isspace(line[comment_start - 1]))
			comment_start--;
		line.erase(comment_start, line.length());
	}
	if (line.length())
	{
		std::stringstream ss(line);

		std::string key;
		const size_t  key_end = line.find_first_of(ISSPACE_CHARACTERS, key_start);
		if (key_end == std::string::npos)
			_conf.push_back(std::pair<std::string,std::string>(line,"\0"));
		else
		{
			std::getline(ss, key, line[key_end]);
			std::string value;
			std::getline(ss, value, '\0');
			value.erase(0, value.find_first_not_of(ISSPACE_CHARACTERS,0)); //rtrim isspace
			_conf.push_back(std::pair<std::string,std::string>(key,value));
		}
	}
}

}	// Nammespace ft
