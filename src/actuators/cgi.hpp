/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:10 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/21 17:18:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
# include <string>	//	std::string
# include <vector>	//	std::vector
#include "requests/Request.hpp"
# include "conf/conf.hpp"

namespace ft
{

class cgi {
	public:
	    //Constructor
		cgi( const std::string & cgi_exec, const std::string & cgi_script, const Request & request , const serverconf & conf );

	    //Destructor
		~cgi();
		std::string const & get_cgi_response() const;

	private:
		cgi(); // not necesary
		cgi( const cgi& copy ); // not necesary
		cgi & operator=( const cgi& assign ); // not necesary

		void _execute(void);
		void _populate_env();

		std::vector<std::string>	_env;
		const std::string &			_cgi_exec;
		const std::string &			_cgi_script;
		const Request &				_request;
		const serverconf &			_conf;
		std::string					_cgi_response;

};

}//Namespace ft

#endif

