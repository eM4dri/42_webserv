/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverconf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:28:53 by jvacaris          #+#    #+#             */
/*   Updated: 2023/06/05 14:08:30 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverconf.hpp"
#include "utils/log.hpp"

namespace ft
{

serverconf::serverconf(const Filetypes & types):	filetypes(types)
{
}

serverconf::~serverconf()
{
	if(locations.size())
		locations.clear();
}

serverconf::serverconf(const serverconf & tocopy):	address(tocopy.address),
													port(tocopy.port),
													default_root(tocopy.default_root),
													locations(tocopy.locations),
													filetypes(tocopy.filetypes),
													server_name(tocopy.server_name)
{
}
void serverconf::print_serverconf() const
{
	LOG("Listen\t"<< address <<":"<< port );
	LOG("Default_Root\t"<< default_root);
	LOG("Server_name\t"<< server_name);
	std::map<std::string, location>::const_iterator it = locations.begin();
	for ( ; it != locations.end(); ++it){
		LOG("\tLocation " << it->first);
		LOG("\t\tpath\t " << it->second.request_path);
		LOG("\t\tautoindex\t " << it->second.autoindex);
		LOG("\t\tclient_max_body_size\t " << it->second.client_max_body_size);
		LOG("\t\tindex\t " << it->second.index);
		LOG("\t\tmethods\t " << it->second.methods);
		LOG("\t\tredirect\t " << it->second.redirect.first <<  ", " << it->second.redirect.second);
		LOG("\t\tfile_root\t " << it->second.file_root);
		LOG("\t\tupload_store\t " << it->second.upload_store);
		std::map<std::string, std::string>::const_iterator it2 = it->second.cgi_execs.begin();
		for ( ; it2!=it->second.cgi_execs.end(); ++it2)
			LOG("\t\tcgi\t " << it2->first << "\t"<< it2->second);
	}
}

}	// Nammespace ft
