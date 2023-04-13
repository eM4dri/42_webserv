/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/13 11:38:18 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/fdlibc-network.hpp"
#include <iostream>
#include "utils/log.hpp"
#include "network/server.hpp"
#include <cstring>

// void ft_leaks(void)
// {
// 	system("leaks containers");
// }

int main(int argc, char **argv)
{
	// atexit(ft_leaks);
	if (argc > 1 && !std::strcmp(argv[1], "granular"))
	{
		ft::SelectServer T(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
		std::cout << "Starting..." << std::endl;
		// std::cout << "Socket..." << std::endl;
		// ft::ASocket as = ft::ASocket(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80);
		std::cout << "Binding Socket..." << std::endl;
		ft::BindSocket bd = ft::BindSocket(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080);
		std::cout << "Listening Socket..." << std::endl;
		ft::ListenSocket ld = ft::ListenSocket(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8081, 5);
		//atexit(ft_leaks);
		// BindSocket();
		(void)bd;
		(void)ld;

		std::cout << "Success!" << std::endl;
	}
	{
		if (argc == 1) // Test Simple server 
			ft::server T("0.0.0.0", 8080, 5);
			
		else if (!std::strcmp(argv[1], "select")) // Test Select server 
			ft::SelectServer T(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
			
		else if (!std::strcmp(argv[1], "poll")) // Test Poll server 
			ft::PollServer T(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
	}


	return (0);
}
