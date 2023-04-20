/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 19:34:32 by emadriga         ###   ########.fr       */
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
// #include <cstdlib>
// #include <cstring>
// #include <utility>

#define ERROR_OPENING_FILE "Error opening file"
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define NUMBER_CHARACTERS "0123456789"
#define INVALID_CONF_FILE_END "Invalid configuration file, not allowed ending directory"
#define INVALID_CONF_FILE_BRACES "Invalid configuration file, curly braces not closed"
#define INVALID_CONF_UNKOWN_DIRECTIVE "Invalid configuration file, unknown key directive"

namespace ft
{

//Constructor
conf::conf( const char* filename )
{
	std::ifstream ifs;

	ifs.open (filename, std::ifstream::in);
	// std::ifstream ifs (filename);
	std::string	line;

	if (ifs.is_open() == false)
	{
	 	LOG_ERROR(ERROR_OPENING_FILE);
		exit(1);
	}
	while (std::getline(ifs, line))
		_processLine(line);
	_validate_conf();
	_print_processed_conf();
	_load_configuration();

}

//Destructor
conf::~conf()
{
	if (_conf.size() > 0)
		_conf.clear();
}

void conf::_load_configuration()
{
	// for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
	// 	if (it->first == "server")
	// 		// server_configuration *sc;


	// }
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
		if (it->second.back() == '{')
			curly_braces_count++;
	}
}

void conf::_load_valid_conf_keys()
{
	_valid_conf_keys.insert("server");
	_valid_conf_keys.insert("root");
	_valid_conf_keys.insert("listen");
	_valid_conf_keys.insert("server_name");
	_valid_conf_keys.insert("client_max_body_size");
	_valid_conf_keys.insert("location");
	_valid_conf_keys.insert("methods");
	_valid_conf_keys.insert("autoindex");
	_valid_conf_keys.insert("return");
	_valid_conf_keys.insert("}");
}

void conf::_validate_conf()
{
	_load_valid_conf_keys();
	int	curly_braces_count;
	curly_braces_count = 0;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first != "}" && it->second.back() != '{' && it->second.back() != ';')
			// Every directive ends with semicolon or cruly braces (simple/block directive)
			LOG_ERROR(INVALID_CONF_FILE_END);
		else
		{
			if (it->first == "}")
				curly_braces_count--;
			else if (it->second.back() == '{')
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

// void conf::_processLine(std::string line)
// {
// 	std::stringstream ss(line);

// 	std::string key;
// 	std::string value;
// 	std::getline(ss, key, ' ');
// 	std::getline(ss, value, '\0');
// 	_conf.insert(std::pair<std::string,std::string>(key,value));
// }

//Private
// void conf::_processLine(std::string line)
// {
// 	const size_t	first_print = line.find_first_not_of(ISSPACE_CHARACTERS,0);
// 	const size_t	first_comment = line.find_first_of('#', first_print);
// 	if (first_comment != 0)
// 	{
// 		const size_t	first_semicolon = line.find_first_of(';', first_print);
// 		if (first_semicolon != std::string::npos && first_semicolon < first_comment)
// 		{
// 			const size_t	key_length = line.find_first_of(ISSPACE_CHARACTERS, first_print);
// 			const size_t	value_ini = line.find_first_not_of(ISSPACE_CHARACTERS, key_length);
// 			std::string key = line.substr(first_print, key_length - first_print);
// 			if (key == "listen")
// 			{
// 				const size_t first_two_dots = line.find_first_of(':', first_print);
// 				if (first_two_dots != 0)
// 				{
// 					_ip = line.substr(value_ini, first_two_dots - value_ini);
// 					_setPort(line.substr(first_two_dots + 1, first_semicolon - first_two_dots - 1));
// 				}
// 				else
// 					_setPort(line.substr(value_ini, first_two_dots - value_ini));
// 			}
// 			else if(key == "methods")
// 			{
// 				_setAcceptedMethods(line.substr(value_ini, first_semicolon - value_ini));
// 			}
// 			else
// 			{
// 				std::string value = line.substr(value_ini, first_semicolon - value_ini);
// 				_conf.insert(std::pair<std::string,std::string>(key,value));
// 			}
// 		}
// 	}
// }

void conf::_setPort(std::string str_port)
{
	const size_t	first_not_digit = str_port.find_first_not_of(NUMBER_CHARACTERS);
	if (first_not_digit == std::string::npos)
	{
		const int length = str_port.length();
		char * c_port = new char[length + 1];
		std::strcpy(c_port, str_port.c_str());
		_port = std::atoi(c_port);
	}
	else
		_port = 0;
}

// void conf::_setAcceptedMethods(std::string accepted_methods)
// {
// 	short	bit;
// 	std::map<int, std::string> accepted;
// 	accepted[GET] = "GET";
// 	accepted[POST] = "POST";
// 	accepted[DELETE] = "DELETE";
// 	bit = 0;
// 	_methods = 0;
// 	std::stringstream ss(accepted_methods);
// 	std::string method;
// 	while (std::getline(ss, method, ' ')){
// 		bit = 0;
// 		for (std::map<int, std::string>::const_iterator it = accepted.begin(); it!=accepted.end(); it++ )
// 		{
// 			if ( method == it->second )
// 				_methods |= (1<<bit);
// 			bit++;
// 		}
// 	}

// }



}	// Nammespace ft
