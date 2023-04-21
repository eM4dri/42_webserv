/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/22 00:30:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network/fdlibc-network.hpp"
#include <iostream>
#include "utils/log.hpp"
#include "network/server.hpp"
#include "conf/conf.hpp"
#include "responses/Filetypes.hpp"
#include "responses/responses.hpp"
#include <cstring>
#include "responses/responses.hpp"

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
	if (argc > 1 && !std::strcmp(argv[1], "server"))
	{
		ft::server server("0.0.0.0", 8080, 5);
	}
	if (argc > 1 && !std::strcmp(argv[1], "conf"))
	{
		LOG(std::endl << " *\t Test Load *.conf \t* ");
		ft::conf newconf("conf/example.conf");
	}
	if (argc > 1 && !std::strcmp(argv[1], "mime"))
	{
		LOG(std::endl << " *\t Test Load mime.types \t* ");
		Filetypes filetypes;
	}
	if (argc >  1 && !std::strcmp(argv[1], "error"))
	{
		LOG(std::endl << " *\t Test return error message \t* ");
		LOG(return_error_message(404));
	}
	if (argc >  1 && !std::strcmp(argv[1], "html"))
	{
		std::string result;
		std::cout << "Showing the content of the generated html file showing the index of a directory." << std::endl;
		result = create_directory_index("src/");
		std::cout << result << std::endl;
	}

	return (0);
}
