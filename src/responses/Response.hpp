/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:32 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/05 20:23:39 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../requests/Request.hpp"
#include "responses.hpp"

/**
 * @param request (const Request)
 * @param status_code (int)
 * @param head_params (std::map <std::string, std::string>)
 * @param body (std::String)
 * 
*/
class Response
{
	private:
		const Request request;
		int status_code;
		std::map<std::string, std::string> head_params;
		std::string body;
		Response();

	public:
		Response(const Request _request);
		void return_content();
		std::string reply();
		std::string generate_response();
		void file_status_custom_error(int file_status);
		void return_error_message(int error_code);
		std::string create_directory_index();
};



#endif