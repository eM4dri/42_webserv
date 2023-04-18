/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/18 16:05:35 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
# include <fstream>		// std::ifstream
# include <string>		// std::string
# include <map>			// std::map
namespace ft
{

enum accepted_methods
	{ GET = 0x1, POST = 0x2, DELETE = 0x4 };
static const char *logLevel[] =
{ "GET", "POST", "DELETE"};

class conf{
	public:
	    //Constructor
		conf( const char *filename );

	    //Destructor
		~conf();

		//Getters
		std::string		getIp() const;
		ushort			getPort() const;

	private:
		conf();
		conf( const conf& copy );
		conf & operator=( const conf& assign ); // Assignement Operator

		void _processLine(std::string line);
		void _setPort(std::string str_port);
		void _setAcceptedMethods(std::string accepted_methods);


	private:
		std::string							_ip;
		ushort								_port;
		ushort								_methods;
		std::map<std::string,std::string> 	_conf;
};

}//Namespace ft

#endif

