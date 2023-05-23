/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:24:29 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/23 17:10:43 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>	//	std::vector
#include <map>	//	std::map
#ifndef LOG_HPP
# define LOG_HPP

# define	RESET_COLOR "\033[0m"

enum e_ansi_color{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

#define ERROR_MSG "Error:\n\t"
# define LOG(A) std::cout << A << std::endl
# define LOG2(A) std::cout << A
# define LOG_ERROR(A) std::cerr << ERROR_MSG << A << std::endl
# define LOG_COLOR(COLOR, A) std::cout << "\033[0;3" << COLOR <<"m" << A << RESET_COLOR <<std::endl
# define LOG_BCOLOR(COLOR, A) std::cout << "\033[0;4" << COLOR <<"m" << A << RESET_COLOR <<std::endl
# define COLOR(COLOR, A) "\033[0;3" << COLOR <<"m" << A << RESET_COLOR
# define BCOLOR(COLOR, A) "\033[0;4" << COLOR <<"m" << A << RESET_COLOR

template <typename T>
void print_vector(std::vector<T> & vector)
{
	for (typename std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
		LOG(*it);
}


template <typename T1, typename T2>
void print_map(std::map<T1,T2> & map)
{
	for (typename std::map<T1, T2>::const_iterator it = map.begin(); it != map.end(); it++)
		LOG(it->first << "\t" << it->second);
}

template <typename T>
void print_array_null_ending(T **array)
{
	if (*array != NULL)
		while (*array != NULL)
			LOG(*array++);
}

#endif
