/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:35:25 by jvacaris          #+#    #+#             */
/*   Updated: 2023/06/08 14:41:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
?		This is a file to set all the general #define, #include, structs, etc.
*/

#ifndef GENERAL_HPP
# define GENERAL_HPP

//*		~~~~~~~~~ #includes ~~~~~~~~~
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>			// std::remove
#include <cstring>			// std::strcmp
#include <iomanip>			// std::setprecision
#include "utils/log.hpp"
#include "conf/location.hpp"
//*		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//*		~~~~~~~ Text coloring ~~~~~~~
#define TXT_RESET "\033[0m"
#define TXT_COLOR_RED "\033[0;31m"
#define TXT_COLOR_GREEN "\033[0;32m"
#define TXT_COLOR_YELLOW "\033[0;33m"
#define TXT_COLOR_BLUE "\033[0;34m"
#define TXT_COLOR_MAGENTA "\033[0;35m"
#define TXT_COLOR_CYAN "\033[0;36m"
#define TXT_BOLD_RED "\033[1;31m"
#define TXT_BOLD_GREEN "\033[1;32m"
#define TXT_BOLD_YELLOW "\033[1;33m"
#define TXT_BOLD_BLUE "\033[1;34m"
#define TXT_BOLD_MAGENTA "\033[1;35m"
#define TXT_BOLD_CYAN "\033[1;36m"
//*		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SERVER_ROOT "test_files"
#define SERVER_NAME "IDK 4.2"


namespace ft
{

/**
*	@param method short
*	@param path std::string
*	@param http_version std::string
*	@warning UNDER DESTRUCTION
*/
struct s_request_info
{
	short method;
	std::string path;
	std::string http_version;
};

std::vector <std::string> cpp_split(std::string full_line, char splitter);
std::vector <std::string> cpp_splitNremove(std::string full_line, char splitter, char remove);
std::string file_reader(const std::string &filename, int *status);
std::string to_string(int number);
std::string bytes_metric_formatting(long size);
std::string get_date(time_t in_time, bool is_gmt);
std::vector <std::string> cpp_split(std::string full_line, char splitter);
std::string getMessageFromCode(int status_code);
std::string get_date();
std::string correct_path(const std::string &orig_path);
std::string correct_path(const std::string &orig_path, std::vector <std::string> routes);
void checkpoint(char *text); //! Debugging purposes, please delete before evaluating.

}//Namespace ft

#endif
