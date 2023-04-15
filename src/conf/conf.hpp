/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:27 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/15 18:17:40 by emadriga         ###   ########.fr       */
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
		conf( const char* filename );
	
	    //Destructor
		~conf();
	
	private:	
		conf();
		conf( const conf& copy );
		conf & operator=( const conf& assign ); // Assignement Operator
	
		// int		getVar() const;
		// void	setVar( int input );
	
	private:
		std::map<std::string,std::string> 	_conf;
};

}//Namespace ft

#endif 

