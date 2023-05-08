/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/08 19:23:17 by emadriga         ###   ########.fr       */
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
class Filetypes;

/**
 * @param server	(std::vector<serverconf>)
*/
class conf{
	public:
	    //Constructor
		conf( const char *filename, const Filetypes & types );

	    //Destructor
		~conf();

		//Getters
		std::vector<serverconf>				servers;
		void print_loaded_conf();

	private:
		conf();
		conf( const conf& copy );
		conf & operator=( const conf& assign ); // Assignement Operator

		void _process_conf_file(std::ifstream &ifs);
		void _process_conf_line(std::string &line);
		void _validate_processed_conf();
		void _print_processed_conf();
		void _load_configuration( const Filetypes & types );

		//	load parameters to validate conf file
		void _load_acepted_methods();

		// set_default_values
		void _set_server_defaults(serverconf *server);
		void _set_location_defaults(location *location);

		//	parse server directives
		void _parse_server_directive(const std::pair <std::string,std::string> &directive, serverconf *server);
		void _parse_listen(const std::string &listen, serverconf *server);
		void _parse_root(const std::string &root, serverconf *server);

		//	parse location directives
		void _parse_location_directive(const std::pair <std::string,std::string> &directive, location *location);
		void _parse_path(const std::string &path, location *location);
		void _parse_methods(const std::string &methods, location *location);
		void _parse_autoindex(const std::string &autoindex, location *location);
		void _parse_client_max_body_size(const std::string &client_max_body_size, location *location);
		void _parse_index(const std::string &index, location *location);
		void _parse_redirect(const std::string &redirect, location *location);

	private:
		std::vector<std::string>							_accepted_methods;	// GET, POST, DELETE for validations
		std::vector<std::pair <std::string,std::string> >	_conf;	// parsed conf for validations
};

}//Namespace ft

#endif
