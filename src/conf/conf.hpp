/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/21 23:28:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
# include <string>		// std::string
# include <vector>		// std::vector
# include <set>			// std::set
# include "serverconf.hpp"

namespace ft
{

// enum accepted_methods
// 	{ GET = 0x1, POST = 0x2, DELETE = 0x4 };
// static const char *logLevel[] =
// { "GET", "POST", "DELETE"};

class serverconf;

class conf{
	public:
	    //Constructor
		conf( const char *filename );

	    //Destructor
		~conf();

		//Getters
		std::string		getIp() const;
		unsigned short		getPort() const;

	private:
		conf();
		conf( const conf& copy );
		conf & operator=( const conf& assign ); // Assignement Operator

		void _processLine(std::string line);
		void _validate_conf();
		void _load_valid_conf_keys();
		void _load_acepted_methods();
		void _print_processed_conf();
		void _load_configuration();

		void _setAcceptedMethods(std::string accepted_methods);
		void _parse_server_directive(std::pair <std::string,std::string> conf, serverconf *server);
		void _parse_listen(std::string listen, serverconf *server);
		void _parse_root(std::string root, serverconf *server);
		void _parse_location_directive(std::pair <std::string,std::string> conf, location *location);
		void _parse_path(std::string path, location *location);
		void _parse_methods(std::string methods, location *location);
		void _parse_autoindex(std::string autoindex, location *location);
		void _parse_client_max_body_size(std::string client_max_body_size, location *location);
		void _parse_index(std::string index, location *location);
		void _parse_redirect(std::string redirect, location *location);

		std::vector<serverconf>				servers;

	private:
		// std::string											_address;
		// unsigned short										_port;
		// unsigned short										_methods;
		// std::string											_root;
		std::set<std::string>								_valid_conf_keys;
		std::vector<std::string>							_accepted_methods;

		std::vector<std::pair <std::string,std::string> >	_conf;
};

}//Namespace ft

#endif
