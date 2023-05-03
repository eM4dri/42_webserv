/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:32 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/03 20:24:53 by jvacaris         ###   ########.fr       */
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

	public:
		Response(const Request _request);
		std::string reply();
		void return_content();
		std::string generate_response();
		std::string file_status_custom_error(int file_status);
};



#endif
