/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 19:58:29 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
# include <string>		// std::string
# include <vector>		// std::vector
# include <set>		// std::vector
// # include "server_configuration.hpp"
namespace ft
{

enum accepted_methods
	{ GET = 0x1, POST = 0x2, DELETE = 0x4 };
static const char *logLevel[] =
{ "GET", "POST", "DELETE"};

// class server_configuration;

class conf{
	public:
	    //Constructor
		conf( const char *filename );

	    //Destructor
		~conf();

		//Getters
		std::string		getIp() const;
		uint16_t		getPort() const;

	private:
		conf();
		conf( const conf& copy );
		conf & operator=( const conf& assign ); // Assignement Operator

		void _processLine(std::string line);
		void _validate_conf();
		void _load_valid_conf_keys();
		void _print_processed_conf();
		void _load_configuration();

		void _setPort(std::string str_port);
		void _setAcceptedMethods(std::string accepted_methods);


	private:
		std::string							_address;
		uint16_t							_port;
		uint16_t							_methods;
		std::set<std::string>				_valid_conf_keys;
		// std::map<std::string,std::string> 		_conf;
		std::vector<std::pair <std::string,std::string> >	_conf;
		// std::set<server_configuration>						_servers;
};

}//Namespace ft

#endif
