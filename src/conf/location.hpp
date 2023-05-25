/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:24:37 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/25 11:36:23 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <string>		// std::string
# include <map>			// std::map
# define DEFAULT_PATH ""
# define DEFAULT_UPLOAD_STORE ""
# define DEFAULT_FILE_ROOT ""
# define DEFAULT_REDIRECT std::pair<unsigned short,std::string>(0, "")
# define DEFAULT_INDEX "index.html"
# define DEFAULT_CLIENT_MAX_BODY_SIZE 1024
# define DEFAULT_AUTOINDEX false
# define DEFAULT_METHOD GET

namespace ft
{
enum e_accepted_methods
{ GET = 0x1, POST = 0x2, DELETE = 0x4 };

/**
 * @param methods	(unsigned short) usage (methods & GET/POST/DELETE)
 * @param autoindex	(bool) autoindex allowed (list of files in a dir)
 * @param request_path	(std::string)
 * @param client_max_body_size	(size_t)
 * @param index	(std::string) default file if the requested resource is a dir and autoindex is false. //! Check '..'
 * @param redirect	(std::string)
 * @warning Declare a struct with ft::location.
*/
struct location{
	// public:
	unsigned short							methods;	// usage (methods & GET/POST/DELETE)
	bool									autoindex;
	std::string								request_path;
	size_t									client_max_body_size;
	std::string								index;
	std::string								file_root;
	std::string								upload_store;
	std::pair<unsigned short,std::string>	redirect;
	std::map<std::string, std::string>		cgi_execs;

};

}//Namespace ft

#endif
