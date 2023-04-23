/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:35:25 by jvacaris          #+#    #+#             */
/*   Updated: 2023/04/23 17:11:26 by jvacaris         ###   ########.fr       */
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
#include <cstring>			// std::strcmp
#include <iomanip>			// std::setprecision
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

std::vector <std::string> cpp_split(std::string full_line, char splitter);
std::string file_reader(const std::string &filename, int *status);
std::string to_string(int number);
std::string bytes_metric_formatting(long size);
std::string get_date(time_t in_time, bool is_gmt);


#endif
