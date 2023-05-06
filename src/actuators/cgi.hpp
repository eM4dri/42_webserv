/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:10 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/05 17:12:53 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
# include <string>	//	std::string
# include <vector>	//	std::vector


namespace ft
{

class server;

class cgi {
	public:
	    //Constructor
		cgi();

	    //Destructor
		~cgi();
		std::string const & get_response() const;

	private:
		cgi( int var );
		cgi( const cgi& copy );
		cgi & operator=( const cgi& assign ); // Assignement Operator
		void _execute(void);
		void _populate_env(void);
		void _add_env(const std::string & input);
		std::string _response;


		std::vector<char *>	_env;

};

}//Namespace ft

#endif

