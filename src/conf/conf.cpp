/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/08 19:24:01 by emadriga         ###   ########.fr       */
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
#include <cstring>		// std::strcpy
#include <limits.h>		// UCHAR_MAX, USHRT_MAX

#define ERROR_OPENING_FILE "Error opening file"
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define NUMBER_CHARACTERS "0123456789"
#define ERROR_CONF(ERROR) LOG_ERROR("Invalid configuration file, " ERROR)
#define INVALID_FILE_END "not allowed ending directory"
#define INVALID_FILE_BRACES "curly braces not closed"
#define INVALID_UNKOWN_DIRECTIVE "unknown key directive"
#define INVALID_LISTEN "only accepts IPv4 (BYTE.BYTE.BYTE.BYTE:PORT & PORT)"

enum e_curly_braces_level{
	CLOSED,
	OPEN_SERVER,
	OPEN_LOCATION
};

namespace ft
{

//Constructor
conf::conf( const char* filename, const Filetypes & types )
{
	std::ifstream ifs;
	ifs.open (filename, std::ifstream::in);

	if (ifs.is_open() == false)
	{
		LOG_ERROR(ERROR_OPENING_FILE);
		std::exit(1);
	}

	_process_conf_file(ifs);
	// _print_processed_conf();
	_validate_processed_conf();
	_load_configuration(types);
	// _print_loaded_conf();

}

//Destructor
conf::~conf()
{
	if (_conf.size())
		_conf.clear();
	if (servers.size())
	{
		for (std::vector<serverconf>::iterator it = servers.begin(); it != servers.end(); it++) {
			if (it->locations.size())
				it->locations.clear();
		}
		servers.clear();
	}
	// if (_valid_conf_keys.size())
	// 	_valid_conf_keys.clear();
	if (_accepted_methods.size())
		_accepted_methods.clear();
}

void conf::_parse_path(const std::string &root, location *location)
{
	//TODO validate format
	location->path = root.substr(0, root.find_first_of(ISSPACE_CHARACTERS));
}

void conf::_parse_methods(const std::string &methods, location *location)
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
void conf::_parse_autoindex(const std::string &autoindex, location *location)
{
	//TODO validate format
	location->autoindex = (autoindex == "on");
}
void conf::_parse_client_max_body_size(const std::string &client_max_body_size, location *location)
{
	//TODO validate format
	location->client_max_body_size = std::atoi(client_max_body_size.c_str());
}
void conf::_parse_index(const std::string &index, location *location)
{
	//TODO validate format
	location->index = index;
}
void conf::_parse_redirect(const std::string &redirect, location *location)
{
	//TODO validate format
	location->redirect = redirect;
}

void conf::_parse_location_directive(const std::pair <std::string,std::string> &directive, location *location)
{
	std::stringstream ss(directive.second);
	std::string directive_val;
	std::getline(ss, directive_val, ';');
	if (directive.first == "location")
		_parse_path(directive_val, location);
	else if (directive.first == "index")
		_parse_index(directive_val, location);
	else if (directive.first == "client_max_body_size")
		_parse_client_max_body_size(directive_val, location);
	else if (directive.first == "autoindex")
		_parse_autoindex(directive_val, location);
	else if (directive.first == "redirect")
		_parse_redirect(directive_val, location);
	else if (directive.first == "methods")
		_parse_methods(directive_val, location);
}


bool _valid_byte(const std::string &byte)
{
	size_t len = byte.length();

	if (len > 3)
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if(!std::isdigit(byte[i]))
			return false;
	}
	if (std::atoi(byte.c_str()) > UCHAR_MAX)
		return false;
	return true;
}

bool _valid_port(const std::string &port)
{
	size_t len = port.length();

	if (len > 5)
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if(!std::isdigit(port[i]))
			return false;
	}
	if (std::atoi(port.c_str()) > USHRT_MAX)
		return false;
	return true;
}

bool _validate_listen(const std::string &listen)
{
	if (listen.find_first_of(".") != std::string::npos)
	{
		std::stringstream ss(listen);
		std::string byte;
		std::getline(ss, byte, '.'); // X.0.0.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, '.'); // 0.X.0.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, '.'); // 0.0.X.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, ':'); // 0.0.0.X:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, ';'); // 0.0.0.0:XX
		if (!_valid_port(byte))
			return false;
	}
	else if (!_valid_port(listen))
		return false;
	return true;
}

unsigned short _setPort(const std::string &str_port)
{
	return (std::atoi(str_port.c_str()));
}

void conf::_parse_listen(const std::string &listen, serverconf *server)
{
	if (!_validate_listen(listen))
		ERROR_CONF(INVALID_LISTEN);
	size_t port_start = listen.find_first_of(":");
	if (port_start == std::string::npos)
		server->port = std::atoi(listen.c_str());
	else
	{
		server->address = listen.substr(0, port_start);
		server->port = _setPort(&listen[port_start + 1]);
	}
}

void conf::_parse_root(const std::string &root, serverconf *server)
{
	//TODO validate format
	server->root = root;
}

void conf::_parse_server_directive(const std::pair<std::string,std::string> &directive, serverconf *server)
{
	std::stringstream ss(directive.second);
	std::string directive_val;
	std::getline(ss, directive_val, ';');
	if (directive.first == "listen")
		_parse_listen(directive_val, server);
	if (directive.first == "root")
		_parse_root(directive_val, server);
}

void conf::_set_server_defaults(serverconf *server)
{
	server->address = DEFAULT_ADDRESS;
	server->port = DEFAULT_PORT;
	server->root = DEFAULT_ROOT;
	if (server->locations.size())
		server->locations.clear();
}

void conf::_set_location_defaults(location *location)
{
	location->methods = GET;
	location->autoindex = DEFAULT_AUTOINDEX;
	location->path = DEFAULT_PATH;
	location->client_max_body_size = DEFAULT_CLIENT_MAX_BODY_SIZE;
	location->index = DEFAULT_INDEX;
}

void conf::_load_configuration(const Filetypes & types)
{
	int	curly_braces_level = CLOSED;
	serverconf server(types);
	location location;
	_load_acepted_methods();
	for (std::vector< std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first == "}")
		{
			curly_braces_level--;
			if (curly_braces_level == CLOSED)
				this->servers.push_back(server);
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

void conf::print_loaded_conf()
{
	LOG(this->servers.size() << " server configurations loaded");
	for (std::vector<serverconf>::iterator it= this->servers.begin(); it!= this->servers.end(); ++it){
		LOG("Listen\t"<<it->address <<":"<< it->port );
		for (std::map<std::string, location>::iterator it2=it->locations.begin(); it2!=it->locations.end(); ++it2){
			LOG("\tLocation " << it2->first);
			LOG("\t\tpath\t " << it2->second.path);
			LOG("\t\tautoindex\t " << it2->second.autoindex);
			LOG("\t\tclient_max_body_size\t " << it2->second.client_max_body_size);
			LOG("\t\tindex\t " << it2->second.index);
			LOG("\t\tmethods\t " << it2->second.methods);
			LOG("\t\tredirect\t " << it2->second.redirect);
		}
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

void load_valid_conf_keys(std::set<std::string> & valid_conf_keys)
{
	valid_conf_keys.insert("}");
	valid_conf_keys.insert("location");
	valid_conf_keys.insert("root");
	valid_conf_keys.insert("listen");
	valid_conf_keys.insert("methods");
	valid_conf_keys.insert("autoindex");
	valid_conf_keys.insert("server");
	valid_conf_keys.insert("return");
	valid_conf_keys.insert("server_name");
	valid_conf_keys.insert("client_max_body_size");
}

void conf::_load_acepted_methods()
{
	_accepted_methods.push_back("GET");
	_accepted_methods.push_back("DELETE");
	_accepted_methods.push_back("POST");
}

void conf::_validate_processed_conf()
{
	std::set<std::string>	valid_conf_keys;
	load_valid_conf_keys(valid_conf_keys);
	int	curly_braces_count;
	curly_braces_count = 0;
	char second_back;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		second_back = (it->second.length() == 0) ? '\0' : it->second[it->second.length() - 1];
		if (it->first != "}" && second_back != '{' && second_back != ';')
			// Every directive ends with semicolon or cruly braces (simple/block directive)
			ERROR_CONF(INVALID_FILE_END);
		else
		{
			if (it->first == "}")
				curly_braces_count--;
			else if (second_back == '{')
				curly_braces_count++;
			if (valid_conf_keys.find(it->first) == valid_conf_keys.end() )
				// Unkown key directive
				ERROR_CONF(INVALID_UNKOWN_DIRECTIVE);
		}
	}
	if (curly_braces_count != 0)
		// Curly braces must have start & end
		ERROR_CONF(INVALID_FILE_BRACES);
}

void conf::_process_conf_line(std::string &line)
{
	size_t	key_start = 0;
	while (std::isspace(line[key_start], std::locale()))
			key_start++;
	if (key_start > 0)
		line.erase(0, key_start);
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
			value.erase(0, value.find_first_not_of(ISSPACE_CHARACTERS,0)); //ltrim isspace
			_conf.push_back(std::pair<std::string,std::string>(key,value));
		}
	}
}

void conf::_process_conf_file(std::ifstream &ifs)
{
	std::string	line;
	while (std::getline(ifs, line))
		_process_conf_line(line);
}
}	// Nammespace ft
