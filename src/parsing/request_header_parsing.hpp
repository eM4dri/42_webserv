/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_header_parsing.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:31:06 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/11 20:14:27 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HEADER_PARSING_HPP
# define REQUEST_HEADER_PARSING_HPP

#include "../general.hpp"


void header_parser(std::string fullrequest, struct s_request_info &header_struct, std::map<std::string, std::string> &header_map, std::string &body);
std::vector <std::string> cpp_split(std::string full_line, char splitter);


#endif
