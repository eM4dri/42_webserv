/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:24:29 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/11 20:34:33 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

#ifndef LOG_HPP
# define LOG_HPP

#define ERROR_MSG "Error:\n\t"
# define LOG(A) std::cout << A << std::endl
# define LOG2(A) std::cout << A
# define LOG_ERROR(A) std::cerr << ERROR_MSG << A << std::endl
#endif
