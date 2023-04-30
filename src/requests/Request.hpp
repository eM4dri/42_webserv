/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:14:01 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/30 21:08:51 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "../general.hpp"

/**
 * @param fullrequest (const string)
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
		};

	//*	Parsing
		void header_parser();
		
		bool check_request_validity(std::string fullheader);
		bool check_first_line_validity(std::string firstline);

	private:
		const std::string fullrequest;
		int method;
		s_path path;
		std::map <std::string, std::string> header_map;
		std::string body;
		


};

int main()
{
	Request hi;
}

#endif
