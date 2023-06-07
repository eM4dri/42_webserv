/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/06 16:14:00 by emadriga         ###   ########.fr       */
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
		conf( const char *filename, const Filetypes & types );

	    //Destructor
		~conf();

		//Getters
		std::vector<serverconf>				servers;
		void print_loaded_conf(const std::vector<serverconf> & servers) const;
		void print_serverconf( const serverconf& serverconf ) const;

	private:
		std::vector<serverconf>				_tmp_servers;
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
		void _parse_server_name(const std::string &server_name, serverconf *server);
		void _parse_default_root(const std::string &default_root, serverconf *server);

		//	parse location directives
		void _parse_location_directive(const std::pair <std::string,std::string> &directive, location *location, const serverconf &server);
		void _parse_request_path(const std::string &path, location *location);
		void _parse_autoindex(const std::string &autoindex, location *location);
		void _parse_client_max_body_size(const std::string &client_max_body_size, location *location);
		bool _valid_index(const std::string &index, const Filetypes &filetypes);
		void _parse_index(const std::string &index, location *location, const Filetypes &filetypes);
		void _parse_file_root(const std::string &file_root, location *location);
		void _parse_upload_store(const std::string &upload_store, location *location);
		void _parse_cgi(const std::string &cgi, location *location);

		void push_back_server(serverconf &server);

	// public:	//	gTest public
		conf() {};  // Default constructor for unit test
		bool _valid_path(const std::string &path);
		bool _valid_redirect_url(const std::string &url);
		bool _valid_redirect(const std::string &redirect);
		void _parse_redirect(const std::string &redirect, location *location, const serverconf &server);
		void _parse_methods(const std::string &methods, location *location);
		void _set_location_defaults(location *location);
	private:
		std::vector<std::pair <std::string,std::string> >	_conf;	// parsed conf for validations
};

}//Namespace ft

#endif
