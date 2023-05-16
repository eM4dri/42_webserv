/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:14:01 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/16 20:36:36 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "../general.hpp"
#include "../conf/serverconf.hpp"

/**
 * @param fullrequest (const string)
 * @param config (const ft::config)
 * @param method (int)
 * @param path (s_path)
 * @param header_map (map <string,string>)
 * @param body (string)
*/
class Request
{
	public:
		struct s_path
		{
			std::string absolute;
			std::string relative;
			std::string unparsed;
			std::vector<std::string> vec_relative;
		};

////		Request(const ft::serverconf &_config);
		Request(const std::string &_input, const ft::serverconf &_config);
		Request(Request &tocopy);
		Request(const Request &tocopy);

	//*	Parsing
		void header_parser(const ft::serverconf &_config);
		bool check_request_validity(std::string fullheader, const ft::serverconf &_config);
		bool check_first_line_validity(std::string firstline, const ft::serverconf &_config);

	//*	Getters
		const std::string &get_fullrequest() const;
		int get_method() const;
		const std::string get_method_txt() const;
		const std::string &get_path_raw() const;
		const std::string &get_path_rel() const;
		const std::string &get_path_abs() const;
		const std::map<std::string, std::string> get_headermap() const;
		const std::string &get_body() const;

		void set_redirect_path();
	private:
		const std::string fullrequest;
		const ft::serverconf config;
		int method;
		s_path path;
		std::map <std::string, std::string> header_map;
		std::string body;
		ft::location location;
		


};

#endif
