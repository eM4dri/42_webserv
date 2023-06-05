/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:32 by jvacaris          #+#    #+#             */
/*   Updated: 2023/06/05 18:51:57 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../requests/Request.hpp"
#include "../actuators/cgi.hpp"

namespace ft
{

/**
 * @param _request (const Request)
 * @param _status_code (int)
 * @param _head_params (std::map <std::string, std::string>)
 * @param _body (std::String)
 *
*/
class Response
{
	private:
		const Request &_request;
		int _status_code;
		std::map<std::string, std::string> _head_params;
		std::string _body;
		Response();
		void _cgi_content(const std::string &cgi_exec);
		bool _cgi_responses;

	public:
		Response(const Request &_request);
		void return_content();
		void post_content();
		void delete_content();
		std::string generate_response();
		void file_status_custom_error(int file_status);
		void return_error_message(int error_code);
		void return_error_message(int error_code, std::string custom_reason);
		std::string create_directory_index();
		const bool &get_cgi_responses() const;
		const int &get_status_code() const;
};

}// Nammespace ft

#endif
