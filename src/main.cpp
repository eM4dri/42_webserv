/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/03 20:25:31 by jvacaris         ###   ########.fr       */
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
#include "general.hpp"
#include "actuators/methods.hpp"
#include "requests/Request.hpp"
#include "responses/Response.hpp"

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
		newconf.print_loaded_conf();
	}
	if (argc > 1 && !std::strcmp(argv[1], "serverconf"))
	{
		ft::conf newconf("conf/example.conf");
		for(std::vector<ft::serverconf>::iterator it = newconf.servers.begin(); it != newconf.servers.end(); it++)
			ft::server server(*it);
	}
	if (argc > 1 && !std::strcmp(argv[1], "mime"))
	{
		LOG(std::endl << " *\t Test Load mime.types \t* ");
		Filetypes filetypes;
		std::cout << "html:  "<< filetypes.get("html") << std::endl;
		std::cout << "png:  "<< filetypes.get("png") << std::endl;
		std::cout << "mp3:  "<< filetypes.get("mp3") << std::endl;
		std::cout << "zip:  "<< filetypes.get("zip") << std::endl;
		std::cout << "pdf:  "<< filetypes.get("pdf") << std::endl;
		std::cout << "fdf:  "<< filetypes.get("fdf") << std::endl;
		std::cout << "gif:  "<< filetypes.get("gif") << std::endl;
	}
	if (argc >  1 && !std::strcmp(argv[1], "error"))
	{
		LOG(std::endl << " *\t Test return error message \t* ");
		LOG(return_error_message(404));
	}
	if (argc >  1 && !std::strcmp(argv[1], "dirpage"))
	{
		std::string result;
		std::cout << "Showing the content of the generated html file showing the index of a directory." << std::endl;
		result = create_directory_index("src/");
		std::cout << result << std::endl;
	}
	if (argc >  1 && !std::strcmp(argv[1], "headerparser"))
	{
		int read_status;
		
		Request newrequest(file_reader("test_files/get_request", &read_status));

		std::cout << "Abs path: " << newrequest.get_path_abs() << std::endl;
		std::cout << "Rel path: " << newrequest.get_path_rel() << std::endl;
		std::cout << "Raw path: " << newrequest.get_path_raw() << std::endl << std::endl;
		
		std::cout << "Method: " << newrequest.get_method_txt() << std::endl << std::endl;

		std::cout << "------ BODY ------" << std::endl;
		std::cout << newrequest.get_body() << std::endl << std::endl;
	}
	if (argc >  1 && !std::strcmp(argv[1], "gettest"))
	{
		int read_status = 1;
		Request request(file_reader("test_files/get_request_dir", &read_status));
		if (read_status)
			std::cout << TXT_COLOR_RED << "SOMETHING WENT WRONG IN THE MAIN!" << TXT_RESET << std::endl << "Error code: " << read_status << std::endl;

		Response response(request);

	}
	// if (argc >  1 && !std::strcmp(argv[1], "gettest"))
	// {
	// 	struct s_request_info header_struct;
	// 	std::map<std::string, std::string> header_map;
	// 	std::string body;
	// 	int read_status;

	// 	std::string file_read = file_reader("test_files/get_request", &read_status); //! Please include the complete path of the file containing the GET request relative to the executable.
	// 	if (read_status)
	// 		std::cout << TXT_COLOR_RED << "SOMETHING WENT WRONG IN THE MAIN!" << TXT_RESET << std::endl << "Error code: " << read_status << std::endl;
	// 	header_parser(file_read, header_struct, header_map, body);

	// 	method_get(header_struct);
	// }
	// if (argc >  1 && !std::strcmp(argv[1], "getdirtest"))
	// {
	// 	struct s_request_info header_struct;
	// 	std::map<std::string, std::string> header_map;
	// 	std::string body;
	// 	int read_status;

	// 	std::string file_read = file_reader("test_files/get_request_dir", &read_status); //! Please include the complete path of the file containing the GET request relative to the executable.
	// 	if (read_status)
	// 		std::cout << TXT_COLOR_RED << "SOMETHING WENT WRONG IN THE MAIN!" << TXT_RESET << std::endl << "Error code: " << read_status << std::endl;
	// 	header_parser(file_read, header_struct, header_map, body);

	// 	method_get(header_struct);
	// }



	return (0);
}
