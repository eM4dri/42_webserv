/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:24:37 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 18:53:11 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <string>		// std::string

namespace ft
{

class location{
	public:
		//Constructor
		location():	_methods(0x1),
					_autoindex(false),
					_root("/"),
					_client_max_body_size(1024),
					_index("index.html"),
					_return("")
			{};

		//Destructor
		~location();

		void set_methods(uint16_t methods);
		void set_autoindex(bool index);
		void set_root(std::string root);
		void set_client_max_body_size(size_t client_max_body_size);
		void set_index(std::string index);
		void set_return(std::string return_);

		const uint16_t & get_methods();
		const bool &  get_autoindex();
		const std::string &  get_root();
		const size_t &  get_client_max_body_size();
		const std::string &  get_index();
		const std::string &  get_return();

	private:
		location( int var );
		location( const location& copy );

		location & operator=( const location& assign ); // Assignement Operator

	private:
		u_int16_t		_methods; //Accepted methods GET POST DELETE
		bool			_autoindex;
		std::string		_root;
		size_t			_client_max_body_size;
		std::string		_index;
		std::string		_return;
};

}//Namespace ft

#endif

