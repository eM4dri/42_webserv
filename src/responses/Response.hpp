/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:32 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/25 11:51:53 by emadriga         ###   ########.fr       */
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
		bool _is_cgi_response;
		Response();

	public:
		Response(const Request &_request);
		void return_content();
		void post_content();
		std::string generate_response();
		void file_status_custom_error(int file_status);
		void return_error_message(int error_code);
		void return_error_message(int error_code, std::string custom_reason);
		std::string create_directory_index();
};

}// Nammespace ft

#endif
