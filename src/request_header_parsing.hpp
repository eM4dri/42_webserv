/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:06 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/06 20:35:10 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HEADER_PARSING_HPP
# define REQUEST_HEADER_PARSING_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


#define TXT_RESET "\033[0m"
#define TXT_COLOR_RED "\033[0;31m"
#define TXT_BOLD_RED "\033[0;31m"
#define TXT_COLOR_GREEN "\033[0;32m"
#define TXT_COLOR_BLUE "\033[0;34m"
#define TXT_COLOR_YELLOW "\033[0;33m"
#define TXT_COLOR_MAGENTA "\033[0;35m"
#define TXT_COLOR_CYAN "\033[0;36m"

enum e_methods
{
	GET,
	POST,
	DELETE
};

struct s_request_info
{
	short method;
	std::string path;
	std::string http_version;
};


bool	check_request_validity(std::string fullrequest);
std::vector <std::string> cpp_split(std::string full_line, char splitter);


#endif