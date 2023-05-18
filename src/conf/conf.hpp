/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/17 20:45:43 by emadriga         ###   ########.fr       */
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
class serverconf;
class Filetypes;

/**
 * @param server	(std::vector<serverconf>)
*/
class conf{
	public:
	    //Constructor
		conf() {};  // Should be private or better desgin patern
		conf( const char *filename, const Filetypes & types );

	    //Destructor
		~conf();

		//Getters
		std::vector<serverconf>				servers;
		void print_loaded_conf();

	private:
		// conf();  // Should be private or better desgin patern
		conf( const conf& copy );
		conf & operator=( const conf& assign );

		void _process_conf_file(std::ifstream &ifs);
		void _process_conf_line(std::string &line);
		void _validate_processed_conf();
		void _print_processed_conf();
		void _load_configuration( const Filetypes & types );

		// set_default_values
		void _set_server_defaults(serverconf *server,location *location);

		//	parse server directives
		void _parse_server_directive(const std::pair <std::string,std::string> &directive, serverconf *server);
		void _parse_listen(const std::string &listen, serverconf *server);
		void _parse_default_root(const std::string &default_root, serverconf *server);

		//	parse location directives
		void _parse_location_directive(const std::pair <std::string,std::string> &directive, location *location, const serverconf &server);
		void _parse_request_path(const std::string &path, location *location);
		void _parse_autoindex(const std::string &autoindex, location *location);
		void _parse_client_max_body_size(const std::string &client_max_body_size, location *location);
		void _parse_index(const std::string &index, location *location);
		void _parse_file_root(const std::string &file_root, location *location);
		void _parse_cgi(const std::string &cgi, location *location);

		void push_back_server(serverconf &server);

	// public:	//	gTest public
		bool valid_path(const std::string &path);
		bool valid_redirect(const std::string &redirect);
		void _parse_redirect(const std::string &redirect, location *location, const serverconf &server);
		void _parse_methods(const std::string &methods, location *location);
		void _set_location_defaults(location *location);
	private:
		std::vector<std::pair <std::string,std::string> >	_conf;	// parsed conf for validations
};

}//Namespace ft

#endif
