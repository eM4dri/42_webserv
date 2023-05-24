/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:14:01 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/24 16:38:06 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "../general.hpp"
#include "../conf/serverconf.hpp"


namespace ft
{

struct s_path
{
	std::string absolute;
	std::string relative;
	std::string unparsed;
	std::vector<std::string> vec_relative;
};

/**
 * @param fullrequest (const string)
 * @param config (const config)
 * @param method (int)
 * @param path (s_path)
 * @param header_map (map <string,string>)
 * @param body (string)
*/
class Request
{
	public:
////		Request(const serverconf &_config);
		Request(const std::string &input, const serverconf &config);
		Request(Request &tocopy);
		Request(const Request &tocopy);
		~Request();

	//*	Parsing
		void header_parser(const serverconf &config);
		bool check_request_validity(std::string fullheader, const serverconf &config);
		bool check_first_line_validity(std::string firstline, const serverconf &config);

	//*	Getters
		const std::string &get_fullrequest() const;
		int get_method() const;
		const std::string get_method_txt() const;
		const std::string &get_path_raw() const;
		const std::string &get_path_rel() const;
		const std::string &get_path_abs() const;
		const std::map<std::string, std::string> get_headermap() const;
		const std::string &get_body() const;
		const location *get_location() const;

		void set_redirect_path();
		const serverconf &config;
	private:
		const std::string _fullrequest;
		int _method;
		s_path _path;
		std::map <std::string, std::string> _header_map;
		std::string _body;
		const location	*_location;
};

}// Nammespace ft

#endif
