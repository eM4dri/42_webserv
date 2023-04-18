/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/18 16:37:53 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"
#include "utils/log.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>

#define ERROR_OPENING_FILE "Error opening file"
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define NUMBER_CHARACTERS "0123456789"

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
	for (std::map<std::string,std::string>::iterator it=_conf.begin(); it!=_conf.end(); ++it)
		LOG( "(" << it->first << ", " << it->second << ")" );
	LOG( "(" << _ip << ", " << _port << ")" );
	LOG("Accepted methods " << _methods);

}

//Destructor
conf::~conf()
{
	if (_conf.size() > 0)
		_conf.clear();
}

//Private
void conf::_processLine(std::string line)
{
	const size_t	first_print = line.find_first_not_of(ISSPACE_CHARACTERS,0);
	const size_t	first_comment = line.find_first_of('#', first_print);
	if (first_comment != 0)
	{
		const size_t	first_semicolon = line.find_first_of(';', first_print);
		if (first_semicolon != std::string::npos && first_semicolon < first_comment)
		{
			const size_t	key_length = line.find_first_of(ISSPACE_CHARACTERS, first_print);
			const size_t	value_ini = line.find_first_not_of(ISSPACE_CHARACTERS, key_length);
			std::string key = line.substr(first_print, key_length - first_print);
			if (key == "listen")
			{
				const size_t first_two_dots = line.find_first_of(':', first_print);
				if (first_two_dots != 0)
				{
					_ip = line.substr(value_ini, first_two_dots - value_ini);
					_setPort(line.substr(first_two_dots + 1, first_semicolon - first_two_dots - 1));
				}
				else
					_setPort(line.substr(value_ini, first_two_dots - value_ini));
			}
			else if(key == "methods")
			{
				_setAcceptedMethods(line.substr(value_ini, first_semicolon - value_ini));
			}
			else
			{
				std::string value = line.substr(value_ini, first_semicolon - value_ini);
				_conf.insert(std::pair<std::string,std::string>(key,value));
			}
		}
	}
}

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

void conf::_setAcceptedMethods(std::string accepted_methods)
{
	short	bit;
	std::map<int, std::string> accepted;
	accepted[GET] = "GET";
	accepted[POST] = "POST";
	accepted[DELETE] = "DELETE";
	bit = 0;
	_methods = 0;
	std::stringstream ss(accepted_methods);
	std::string method;
	while (std::getline(ss, method, ' ')){
		bit = 0;
		for (std::map<int, std::string>::const_iterator it = accepted.begin(); it!=accepted.end(); it++ )
		{
			if ( method == it->second )
				_methods |= (1<<bit);
			bit++;
		}
	}

}



}	// Nammespace ft
