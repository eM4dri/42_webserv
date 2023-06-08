/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/08 13:58:57 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/log.hpp"
#include "network/server.hpp"
#include <exception>			//	std::exception

#define HOW_TO_USE "\nUsage:  ./webserv [CONFIGURATION_FILE]\n"\
"\nConfiguration file:  you can find some examples at ./conf\n"

int main(int argc, char **argv)
{
	if (argc != 2)
		LOG(HOW_TO_USE);
	else
	{
		try
		{
			ft::server server(argv[1]);
		}
		catch(const std::exception& e)
		{
			LOG_ERROR(e.what());
		}
	}
}
