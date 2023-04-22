/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:24:37 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/21 23:25:47 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <string>		// std::string
# define DEFAULT_PATH "/"
# define DEFAULT_INDEX "index.html"
# define DEFAULT_CLIENT_MAX_BODY_SIZE 1024
# define DEFAULT_AUTOINDEX false
# define DEFAULT_METHOD GET


namespace ft
{
enum e_accepted_methods
{ GET = 0x1, POST = 0x2, DELETE = 0x4 };

struct location{
	// public:
	unsigned short	methods; //Accepted methods GET POST DELETE
	bool			autoindex;
	std::string		path;
	size_t			client_max_body_size;
	std::string		index;
	std::string		redirect;

};

}//Namespace ft

#endif

