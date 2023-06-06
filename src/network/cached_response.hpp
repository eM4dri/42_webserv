/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cached_response.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:24:15 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/05 18:47:37 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CACHED_RESPONSE_HPP
# define CACHED_RESPONSE_HPP
# include <ctime>				//	std::time
# include <string>				//	std::string

namespace ft
{
struct cached_key{
	int				fd;
	std::string		request;
};

struct cached_value{
	std::time_t			expired;
	std::string			response;
};

struct cache_cmp {
	bool operator()(const cached_key lhs, const cached_key rhs) const
	{
		if (lhs.fd < rhs.fd)
			return true;
		else if (lhs.fd > rhs.fd)
			return false;
		else
			return (lhs.request < rhs.request);
	}
};


}//Namespace ft

#endif
