/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/17 19:58:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_HPP
# define CONF_HPP
# include <fstream>		// std::ifstream
# include <string>		// std::string
# include <map>			// std::map
namespace ft
{

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

	
	private:
		std::string							_ip;
		ushort								_port;
		std::map<std::string,std::string> 	_conf;
};

}//Namespace ft

#endif 

