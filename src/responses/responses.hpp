/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:21:44 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/03 18:05:50 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSES_HPP
# define RESPONSES_HPP

#include "../general.hpp"
#include "Filetypes.hpp"



std::string return_content(int status_code, std::string filename);
std::string return_error_message(int status_code);
std::string create_directory_index(std::string path);
std::string return_content(int status_code, std::string filename);
std::string file_status_custom_error(int file_status, std::string path);

#endif
