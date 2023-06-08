/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:32:30 by emadriga          #+#    #+#             */
/*   Updated: 2023/06/06 17:04:31 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf.hpp"
#include "../utils/log.hpp"
#include <string>		// std::string, std::getline
#include <vector>		// std::vector
#include <set>			// std::set
#include <fstream>		// std::ifstream
#include <sstream>		// std::stringstream
#include <iostream>		// std::out, std::endl
#include <locale>		// std::locale, std::isspace
#include <cstdlib>		// std::exit
#include <cstring>		// std::strcpy
#include <limits.h>		// UCHAR_MAX, USHRT_MAX
#include <math.h>		// pow() function

#define ERROR_OPENING_FILE "Error opening file"
#define ISSPACE_CHARACTERS " \t\n\v\f\r"
#define NUMBER_CHARACTERS "0123456789"

#define LOG_ERROR_CONF(ERROR) LOG_ERROR("Invalid configuration file, " ERROR)
#define INVALID_FILE_END "not allowed ending directory "
#define INVALID_FILE_BRACES "curly braces not closed"
#define INVALID_UNKOWN_DIRECTIVE "unknown key directive "
#define INVALID_LISTEN "only accepts IPv4 (BYTE.BYTE.BYTE.BYTE:PORT & PORT)"
#define WRONG_LOCATION "wrong location "
#define WRONG_METHOD "wrong method "
#define WRONG_PATH "wrong path "
#define WRONG_SERVER_NAME "wrong server_name "
#define WRONG_REDIRECTION "wrong redirection "
#define WRONG_INDEX "wrong index "

#define THROW_INVALID_FILE_END "Invalid configuration file, not allowed ending directory"
#define THROW_INVALID_FILE_BRACES "Invalid configuration file, curly braces not closed"
#define THROW_INVALID_UNKOWN_DIRECTIVE "Invalid configuration file, unknown key directive"
#define THROW_INVALID_LISTEN "Invalid configuration file, only accepts IPv4 (BYTE.BYTE.BYTE.BYTE:PORT & PORT)"
#define THROW_WRONG_LOCATION "Invalid configuration file, wrong location "
#define THROW_WRONG_METHOD "Invalid configuration file, wrong method "
#define THROW_WRONG_PATH "Invalid configuration file, wrong path "
#define THROW_WRONG_SERVER_NAME "Invalid configuration file, wrong server_name "
#define THROW_WRONG_REDIRECTION "Invalid configuration file, wrong redirection "
#define THROW_WRONG_INDEX "Invalid configuration file, wrong index "


enum e_curly_braces_level{
	CLOSED,
	OPEN_SERVER,
	OPEN_LOCATION
};

namespace ft
{
//Constructor
conf::conf( const char* filename, const Filetypes & types )
{
	std::ifstream ifs;
	ifs.open (filename, std::ifstream::in);

	if (ifs.is_open() == false)
	{
		LOG_ERROR(ERROR_OPENING_FILE);
		std::exit(1);
	}

	_process_conf_file(ifs);
	// _print_processed_conf();
	_validate_processed_conf();
	_load_configuration(types);
	// print_loaded_conf();
	std::vector<serverconf>::iterator it= this->_tmp_servers.begin();
	for ( ; it!=_tmp_servers.end(); it++){
		serverconf server(*it);
		server.default_root = correct_path(server.default_root);
		server.locations.clear();
		std::map<std::string, location>::iterator it2= it->locations.begin();
		for ( ; it2!=it->locations.end(); it2++){
			location location;
			// location._file_root = correct_path(it2->second._file_root);
			location.request_path = correct_path(it2->second.request_path);
			location.file_root = it2->second.file_root;
			location.methods = it2->second.methods;
			location.autoindex = it2->second.autoindex;
			location.client_max_body_size = it2->second.client_max_body_size;
			location.index = it2->second.index;
			location.upload_store = it2->second.upload_store;
			location.redirect = it2->second.redirect;
			location.cgi_execs = it2->second.cgi_execs;
			server.locations.insert(std::make_pair(location.request_path, location));
		}
		// print_serverconf(*it);
		// print_serverconf(server);
		servers.push_back(server);
	}
	_tmp_servers.clear();

}

//Destructor
conf::~conf()
{
	if (_conf.size())
		_conf.clear();
	if (_tmp_servers.size())
	{
		for (std::vector<serverconf>::iterator it = _tmp_servers.begin(); it != _tmp_servers.end(); it++) {
			if (it->locations.size())
				it->locations.clear();
		}
		_tmp_servers.clear();
	}
	// delete pimpl_;
}

bool valid_path_end(const std::string &path)
{
	u_short		i = 0;
	const char *invalid_end[] = { "/", "{", "/.", "/..", "/~", NULL};
	const size_t len[] = {1, 1, 2, 3, 2};
	while (invalid_end[i] != NULL)
	{
		size_t pos = path.size() - len[i];
		if (path.compare(pos, len[i], invalid_end[i]) == 0)
			return false;
		i++;
	}
	return true;
}

bool conf::_valid_path(const std::string &path)
{
	const char	*invalid[] = {"//", "/./", "/../", "/~/", NULL};
	u_short		i = 0;

	if (path[0] != '/')	// Only starting char allowed for any conf path
		return false;
	else if (path == "/") // '/' is default valid path
		return true;
	while (invalid[i] != NULL)
	{
		if (path.find(invalid[i]) != std::string::npos)
			return false;
		i++;
	}
	return valid_path_end(path);
}

void conf::_parse_file_root(const std::string &file_root, location *location)
{
	if (!_valid_path(file_root))
		throw std::invalid_argument(THROW_WRONG_PATH + file_root);
		// LOG_ERROR_CONF(WRONG_PATH << COLOR(RED, file_root));
	location->file_root = std::string(file_root); // ltrim(str,'/')
}

void conf::_parse_upload_store(const std::string &upload_store, location *location)
{
	if (!_valid_path(upload_store))
		throw std::invalid_argument(THROW_WRONG_PATH + upload_store);
		// LOG_ERROR_CONF(WRONG_PATH << COLOR(RED, upload_store));
	location->upload_store = std::string(upload_store); // ltrim(str,'/')
}

void conf::_parse_request_path(const std::string &request_path, location *location)
{
	if (!_valid_path(request_path))
		throw std::invalid_argument(THROW_WRONG_LOCATION + request_path);
		// LOG_ERROR_CONF(WRONG_LOCATION << COLOR(RED, request_path));
	location->request_path = std::string(request_path); // ltrim(str,'/')
}

void conf::_parse_cgi(const std::string &cgi, location *location)
{
	//TODO validate format
	std::stringstream ss(cgi);

	std::string key;
	const size_t  key_end = cgi.find_first_of(ISSPACE_CHARACTERS, 0);
	if (key_end == std::string::npos)
		location->cgi_execs.insert(std::make_pair(cgi, "\0"));
	else
	{
		std::getline(ss, key, cgi[key_end]);
		std::string value;
		std::getline(ss, value, '\0');
		value.erase(0, value.find_first_not_of(ISSPACE_CHARACTERS,0)); //ltrim isspace
		location->cgi_execs.insert(std::make_pair(key, value));
	}
}

void conf::_parse_methods(const std::string &methods, location *location)
{
	location->methods &= 0; // to address default initialization of locations's methods
	std::stringstream ss(methods);
	std::string method;
	while (std::getline(ss, method, ' ')){
		if (method == "GET")
			location->methods |= GET;
		else if (method == "POST")
			location->methods |= POST;
		else if (method == "DELETE")
			location->methods |= DELETE;
		else
			throw std::invalid_argument(THROW_WRONG_METHOD);
			// LOG_ERROR_CONF(WRONG_METHOD << COLOR(RED,method));//!Error or Warning
	}
}
void conf::_parse_autoindex(const std::string &autoindex, location *location)
{
	//TODO validate format
	location->autoindex = (autoindex == "on");
}
void conf::_parse_client_max_body_size(const std::string &client_max_body_size, location *location)
{
	char	units[] = {'k', 'M', 'G', 'T', 'P', 'E'};
	std::string::const_iterator str_ptr = client_max_body_size.begin();
	while (str_ptr != client_max_body_size.end() && *str_ptr >= '0' && *str_ptr <= '9')
		str_ptr++;
	location->client_max_body_size = std::atoi(client_max_body_size.c_str());
	if (str_ptr != client_max_body_size.end())
	{
		for (unsigned int i = 0; i < 6; i++)
		{
			if (*str_ptr == units[i])
			{
				location->client_max_body_size = location->client_max_body_size * (size_t)(pow(1024, i + 1));
				break;
			}
		}
	}
}

bool conf::_valid_index(const std::string &index, const Filetypes &types)
{
	if (index.empty())
		return false;
	if (index[0] == '/')
		return false;
	if (index.find_last_of('.') == std::string::npos)
		return true;
	if (types.get_suffix(index) != "text/html")
		return false;
	return true;
}

void conf::_parse_index(const std::string &index, location *location, const Filetypes &filetypes)
{
	if (!_valid_index(index, filetypes))
		throw std::invalid_argument(THROW_WRONG_INDEX);
		// LOG_ERROR_CONF(WRONG_INDEX << COLOR(RED, index));
	else
		location->index = (index.find_last_of('.') == std::string::npos) ? index + ".hmtl" : index; //append html to non extenion files
}

bool _valid_redirect_code(const std::string &code)
{
	const int allowedRedirectionCodes[] = {301, 302, 303, 307, 308};
	std::set<int> codes (allowedRedirectionCodes, allowedRedirectionCodes + 5);
	const size_t len = code.length();

	if (len != 3)
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if(!std::isdigit(code[i]))
			return false;
	}
	if ( codes.find(std::atoi(code.c_str())) == codes.end())
		return false;
	return true;
}

bool conf::_valid_redirect_url(const std::string &url)
{
	const char	*valid[] = {"http://", "https://", NULL};
	u_short		i = 0;
	size_t		http_index;

	while (valid[i] != NULL)
	{
		http_index = url.find(valid[i]);
		if (http_index == 0)
			return true;
		i++;
	}
	return _valid_path(url);
}


void conf::_parse_redirect(const std::string &redirect, location *location_, const serverconf &server)
{
	std::stringstream ss(redirect);
	std::string code;
	std::string url;
	const size_t  key_end = redirect.find_first_of(ISSPACE_CHARACTERS, 0);
	if (key_end == std::string::npos)
		throw std::invalid_argument(THROW_WRONG_REDIRECTION);
		// LOG_ERROR_CONF(WRONG_REDIRECTION << 1 << COLOR(RED, redirect));
	else
	{
		std::getline(ss, code, redirect[key_end]);
		if (!_valid_redirect_code(code))
			throw std::invalid_argument(THROW_WRONG_REDIRECTION);
			// LOG_ERROR_CONF(WRONG_REDIRECTION << 2 << COLOR(RED, redirect));

		std::getline(ss, url, '\0');
		url.erase(0, url.find_first_not_of(ISSPACE_CHARACTERS,0)); //ltrim isspace
		if (!_valid_redirect_url(url))
			throw std::invalid_argument(THROW_WRONG_REDIRECTION);
			// LOG_ERROR_CONF(WRONG_REDIRECTION << 3 << COLOR(RED, redirect));
	}
	std::string copy(url); // ltrim(str,'/')
	std::map<std::string, location>::const_iterator it = server.locations.find(copy);
	while (1)	//	Avoding circular references a > b, b > c & c > a -> c > ''
	{
		if (it == server.locations.end() || it->second.redirect.second == "")
			break;
		copy = it->second.redirect.second;
		it = server.locations.find(copy);
	}
	if ( location_->request_path != copy )
		location_->redirect = std::make_pair(std::atoi(code.c_str()), copy);
}

void conf::_parse_location_directive(const std::pair <std::string,std::string> &directive, location *location, const serverconf &server)
{
	if (directive.first == "location")
	{
		std::string directive_val(directive.second, 0, directive.second.find_first_of(ISSPACE_CHARACTERS));
		_parse_request_path(directive_val, location);
	}
	std::stringstream ss(directive.second);
	std::string directive_val;
	std::getline(ss, directive_val, ';');
	if (directive.first == "index")
		_parse_index(directive_val, location, server.filetypes);
	else if (directive.first == "client_max_body_size")
		_parse_client_max_body_size(directive_val, location);
	else if (directive.first == "autoindex")
		_parse_autoindex(directive_val, location);
	else if (directive.first == "return")
		_parse_redirect(directive_val, location, server);
	else if (directive.first == "methods")
		_parse_methods(directive_val, location);
	else if (directive.first == "root")
		_parse_file_root(directive_val, location);
	else if (directive.first == "upload_store")
		_parse_upload_store(directive_val, location);
	else if (directive.first == "cgi")
		_parse_cgi(directive_val, location);
}


bool _valid_byte(const std::string &byte)
{
	size_t len = byte.length();

	if (len > 3)
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if(!std::isdigit(byte[i]))
			return false;
	}
	if (std::atoi(byte.c_str()) > UCHAR_MAX)
		return false;
	return true;
}

bool _valid_port(const std::string &port)
{
	size_t len = port.length();

	if (len > 5)
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if(!std::isdigit(port[i]))
			return false;
	}
	if (std::atoi(port.c_str()) > USHRT_MAX)
		return false;
	return true;
}

bool _validate_listen(const std::string &listen)
{
	if (listen.find_first_of(".") != std::string::npos)
	{
		std::stringstream ss(listen);
		std::string byte;
		std::getline(ss, byte, '.'); // X.0.0.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, '.'); // 0.X.0.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, '.'); // 0.0.X.0:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, ':'); // 0.0.0.X:00
		if (!_valid_byte(byte))
			return false;
		std::getline(ss, byte, ';'); // 0.0.0.0:XX
		if (!_valid_port(byte))
			return false;
	}
	else if (!_valid_port(listen))
		return false;
	return true;
}

unsigned short _setPort(const std::string &str_port)
{
	return (std::atoi(str_port.c_str()));
}

void conf::_parse_listen(const std::string &listen, serverconf *server)
{
	if (!_validate_listen(listen))
		throw std::invalid_argument(THROW_INVALID_LISTEN + listen);
		// LOG_ERROR_CONF(INVALID_LISTEN << COLOR(RED, listen));
	size_t port_start = listen.find_first_of(":");
	if (port_start == std::string::npos)
		server->port = std::atoi(listen.c_str());
	else
	{
		server->address = listen.substr(0, port_start);
		server->port = _setPort(&listen[port_start + 1]);
	}
}

void conf::_parse_default_root(const std::string &default_root, serverconf *server)
{
	if (!_valid_path(default_root))
		throw std::invalid_argument(THROW_WRONG_PATH + default_root);
		// LOG_ERROR_CONF(WRONG_PATH << COLOR(RED, default_root));
	server->default_root = default_root;
}

void conf::_parse_server_name(const std::string &server_name, serverconf *server)
{
	for (size_t i = 0; i != server_name.size() ; i++ ){
		if ( !std::isalpha(server_name[i]) )
			throw std::invalid_argument(THROW_WRONG_SERVER_NAME + server_name);
			// LOG_ERROR_CONF(WRONG_SERVER_NAME << COLOR(RED, server_name));
	}
	server->server_name = server_name;
}

void conf::_parse_server_directive(const std::pair<std::string,std::string> &directive, serverconf *server)
{
	std::stringstream ss(directive.second);
	std::string directive_val;
	std::getline(ss, directive_val, ';');
	if (directive.first == "listen")
		_parse_listen(directive_val, server);
	else if (directive.first == "root")
		_parse_default_root(directive_val, server);
	else if (directive.first == "server_name")
		_parse_server_name(directive_val, server);
}

void conf::_set_location_defaults(location *location)
{
	location->methods = GET;
	location->autoindex = DEFAULT_AUTOINDEX;
	location->request_path = DEFAULT_PATH;
	location->client_max_body_size = DEFAULT_CLIENT_MAX_BODY_SIZE;
	location->index = DEFAULT_INDEX;
	location->redirect = DEFAULT_REDIRECT;
	location->upload_store = DEFAULT_UPLOAD_STORE;
	location->file_root = DEFAULT_FILE_ROOT;
	if (!location->cgi_execs.empty())
		location->cgi_execs.clear();
}

void conf::_set_server_defaults(serverconf *server, location *location)
{
	server->address = DEFAULT_ADDRESS;
	server->port = DEFAULT_PORT;
	server->default_root = DEFAULT_ROOT;
	server->server_name = DEFAULT_SERVER_NAME;
	if (server->locations.size())
		server->locations.clear();

	// Insert '/' default location, this location would be overwritten if is later defined
	_set_location_defaults(location);
	server->locations.insert(std::make_pair(location->request_path, *location));
}

void conf::push_back_server(serverconf &server)
{
	// Iterate thorugh locations to set file_root not setted previously
	for (std::map<std::string, location>::iterator it = server.locations.begin(); it != server.locations.end(); it++ ){
		if (it->second.file_root.empty())
		{
			if (server.default_root != "/")
				it->second.file_root += server.default_root;
			if (it->first != "/" || it->second.file_root.empty())
				it->second.file_root += it->first;
		}
	}
	this->_tmp_servers.push_back(server);
}

void conf::_load_configuration(const Filetypes & types)
{
	int	curly_braces_level = CLOSED;
	serverconf server(types);
	location location;
	// _load_acepted_methods();
	for (std::vector< std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first == "}")
		{
			curly_braces_level--;
			if (curly_braces_level == CLOSED)
				push_back_server(server);
			else if (curly_braces_level == OPEN_SERVER)
				server.locations[location.request_path] = location; // Using access instead of insert because I need to overwritte
		}
		else if (it->second[it->second.length() - 1] == '{')
		{
			curly_braces_level++;
			if (curly_braces_level == OPEN_SERVER)
				_set_server_defaults(&server, &location);
			else if (curly_braces_level == OPEN_LOCATION)
				_set_location_defaults(&location);
		}
		if (curly_braces_level == OPEN_SERVER)
			_parse_server_directive(*it, &server);
		else if (curly_braces_level == OPEN_LOCATION)
			_parse_location_directive(*it, &location, server);
	}
}

void conf::print_serverconf( const serverconf& serverconf ) const
{
	LOG("Listen\t"<<serverconf.address <<":"<< serverconf.port );
	LOG("Default_Root\t"<<serverconf.default_root);
	LOG("Server_name\t"<<serverconf.server_name);
	std::map<std::string, location>::const_iterator it = serverconf.locations.begin();
	for ( ; it!=serverconf.locations.end(); ++it){
		LOG("\tLocation " << it->first);
		LOG("\t\tpath\t " << it->second.request_path);
		LOG("\t\tautoindex\t " << it->second.autoindex);
		LOG("\t\tclient_max_body_size\t " << it->second.client_max_body_size);
		LOG("\t\tindex\t " << it->second.index);
		LOG("\t\tmethods\t " << it->second.methods);
		LOG("\t\tredirect\t " << it->second.redirect.first <<  ", " << it->second.redirect.second);
		LOG("\t\tfile_root\t " << it->second.file_root);
		LOG("\t\tupload_store\t " << it->second.upload_store);
		std::map<std::string, std::string>::const_iterator it3 = it->second.cgi_execs.begin();
		for ( ; it3!=it->second.cgi_execs.end(); ++it3)
			LOG("\t\tcgi\t " << it3->first << "\t"<< it3->second);
	}
}

void conf::print_loaded_conf(const std::vector<serverconf> & servers) const
{
	LOG(servers.size() << " server configurations loaded");
	std::vector<serverconf>::const_iterator it= servers.begin();
	for ( ; it!= servers.end(); ++it){
		print_serverconf(*it);
	}
}

void conf::_print_processed_conf()
{
	int	curly_braces_count;
	curly_braces_count = 0;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		if (it->first == "}")
			curly_braces_count--;
		for(int i = 0; i != curly_braces_count; i++)
			std::cout << "\t";
		LOG(it->first << "\t" << it->second );
		if (it->second[it->second.length() - 1] == '{')
			curly_braces_count++;
	}
}

void load_valid_conf_keys(std::set<std::string> & valid_conf_keys)
{
	valid_conf_keys.insert("}");
	valid_conf_keys.insert("location");
	valid_conf_keys.insert("root");
	valid_conf_keys.insert("listen");
	valid_conf_keys.insert("methods");
	valid_conf_keys.insert("index");
	valid_conf_keys.insert("autoindex");
	valid_conf_keys.insert("server");
	valid_conf_keys.insert("return");
	valid_conf_keys.insert("server_name");
	valid_conf_keys.insert("client_max_body_size");
	valid_conf_keys.insert("cgi");
	valid_conf_keys.insert("upload_store");
}

void conf::_validate_processed_conf()
{
	std::set<std::string>	valid_conf_keys;
	load_valid_conf_keys(valid_conf_keys);
	int	curly_braces_count;
	curly_braces_count = 0;
	char second_back;
	for (std::vector<std::pair<std::string,std::string> >::iterator it=_conf.begin(); it!=_conf.end(); ++it){
		second_back = (it->second.length() == 0) ? '\0' : it->second[it->second.length() - 1];
		if (it->first != "}" && second_back != '{' && second_back != ';')
			// Every directive ends with semicolon or cruly braces (simple/block directive)
			throw std::invalid_argument(THROW_INVALID_FILE_END);
			// LOG_ERROR_CONF(INVALID_FILE_END << COLOR(RED,it->first << " " << it->second));
		else
		{
			if (it->first == "}")
				curly_braces_count--;
			else if (second_back == '{')
				curly_braces_count++;
			if (valid_conf_keys.find(it->first) == valid_conf_keys.end() )
				// Unkown key directive
				throw std::invalid_argument(THROW_INVALID_UNKOWN_DIRECTIVE);
				// LOG_ERROR_CONF(INVALID_UNKOWN_DIRECTIVE << COLOR(RED,it->first));
		}
	}
	if (curly_braces_count != 0)
		// Curly braces must have start & end
		throw std::invalid_argument(THROW_INVALID_FILE_BRACES);
		// LOG_ERROR_CONF(INVALID_FILE_BRACES);
}

void conf::_process_conf_line(std::string &line)
{
	size_t	key_start = 0;
	while (std::isspace(line[key_start], std::locale()))
			key_start++;
	if (key_start > 0)
		line.erase(0, key_start);
	size_t comment_start = line.find_first_of('#', 0);
	if (comment_start != std::string::npos)	//remove comments
	{
		while (comment_start > 0 && std::isspace(line[comment_start - 1]))
			comment_start--;
		line.erase(comment_start, line.length());
	}
	if (line.length())
	{
		std::stringstream ss(line);

		std::string key;
		const size_t  key_end = line.find_first_of(ISSPACE_CHARACTERS, key_start);
		if (key_end == std::string::npos)
			_conf.push_back(std::pair<std::string,std::string>(line,"\0"));
		else
		{
			std::getline(ss, key, line[key_end]);
			std::string value;
			std::getline(ss, value, '\0');
			value.erase(0, value.find_first_not_of(ISSPACE_CHARACTERS,0)); //ltrim isspace
			_conf.push_back(std::pair<std::string,std::string>(key,value));
		}
	}
}

void conf::_process_conf_file(std::ifstream &ifs)
{
	std::string	line;
	while (std::getline(ifs, line))
		_process_conf_line(line);
}
}	// Nammespace ft
