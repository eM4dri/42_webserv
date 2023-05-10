/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:24:29 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/10 16:39:35 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

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
#endif
