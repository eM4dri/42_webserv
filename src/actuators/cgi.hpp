/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:10 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/03 18:07:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
# include <string>	//	std::string
# include <vector>	//	std::vector


namespace ft
{

class cgi{
	public:
	    //Constructor
		cgi();

	    //Destructor
		~cgi();

	private:
		cgi( int var );
		cgi( const cgi& copy );
		cgi & operator=( const cgi& assign ); // Assignement Operator
		void _execute(void);
		void _populate_env(void);
		void _add_env(const std::string & input);

		std::vector<char *>	_env;

};

}//Namespace ft

#endif

