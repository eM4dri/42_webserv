/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:23 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/28 19:42:56 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include <errno.h>	//	error codes
#include "utils/log.hpp"

namespace ft
{

/*Response::Response(): request(Request())
{
}*/

Response::Response(const Request &_request): _request(_request),_is_cgi_response(false)
{
	if (_request.get_method() < 0)
	{
		if (_request.get_method() == -1)
			return_error_message(400);
		else if (_request.get_method() == -2)
			return_error_message(505);
		_head_params["Content-Type"] = "text/html";
	}
	else if (!(_request.get_location()->methods & _request.get_method()))
	{
		return_error_message(405);
		_head_params["Content-Type"] = "text/html";
	}
	else if (_request.get_location()->redirect.first != 0)
	{
		return_error_message(_request.get_location()->redirect.first);
		_head_params["Location"] = _request.get_location()->redirect.second;
	}
	else
	{
		if (_request.get_method() == GET)
			return_content();
		else if (_request.get_method() == POST)
			post_content();

	}
	std::cout << std::endl << generate_response() << std::endl;	//! Delete when testing ends.
}

void Response::return_error_message(int error_code)
{
	std::string retval;
	std::string error_reason = to_string(error_code);
	error_reason.append(" ");
	error_reason.append(getMessageFromCode(error_code));

	_status_code = error_code;
	retval.append("<html>\n");
	retval.append("\t<head><title>");
	retval.append(error_reason);
	retval.append("</title></head>\n");
	retval.append("\t<body>\n");
	retval.append("\t\t<h1><center>");
	retval.append(error_reason);
	retval.append("</center></h1>\n");
	retval.append("\t\t<hr>\n");
	retval.append("\t\t<p><center>Webserv</center></p>\n");
	retval.append("\t</body>\n");
	retval.append("</html>");
	_body = retval;
}

void Response::return_error_message(int error_code, std::string custom_reason)
{
	std::string retval;
	std::string error_reason = to_string(error_code);
	error_reason.append(" ");
	error_reason.append(getMessageFromCode(error_code));

	_status_code = error_code;
	retval.append("<html>\n");
	retval.append("\t<head><title>");
	retval.append(error_reason);
	retval.append("</title></head>\n");
	retval.append("\t<body>\n");
	retval.append("\t\t<h1><center>");
	retval.append(error_reason);
	retval.append("</center></h1>\n");
	retval.append("\t\t<p><center><b>Custom reason:</b> ");
	retval.append(custom_reason);
	retval.append("</center></p>\n");
	retval.append("\t\t<hr>\n");
	retval.append("\t\t<p><center>Webserv</center></p>\n");
	retval.append("\t</body>\n");
	retval.append("</html>");
	_body = retval;
}

std::string get_file(std::string filename, std::string &mod_date, int *status)
{
	std::string		file_content;
	struct stat file_info;
	int			file_status = 0;

	file_content = file_reader(filename, &file_status);
	stat(filename.c_str(), &file_info);
	if (file_status)
	{
		*status = file_status;
		return("");
	}
	else if (file_info.st_mode & S_IFDIR)
	{
		*status = EISDIR;
		return("");
	}
	else
	{
		mod_date = get_date(file_info.st_mtime, true);
	}
	*status = 0;
	return(file_content);
}


void Response::file_status_custom_error(int file_status)
{
	std::string retval;
	std::string mod_date;
	int			file_read_status;
	if (file_status == ENOENT)			//?	File Not found
		_status_code = 404;
	else if (file_status == EACCES)		//?	Permission denied
		_status_code = 500;
	else if (file_status == EISDIR)		//?	Is a directory. Permissions have been checked previously so there should be no errors from now on.
	{
		const ft::location *location = _request.get_location();
		if (location->autoindex)
		{
			_status_code = 200;
			retval = create_directory_index();
			_body = retval;
			return ;
		}
		else if (!location->index.empty())
		{
			std::string file_to_get = _request.get_path_abs();

			file_to_get.append("/");
			file_to_get.append(location->index);
			std::string get_body = get_file(file_to_get, mod_date, &file_read_status);
			if (file_read_status == ENOENT)								//?	File Not found
				_status_code = 404;
			else if (file_read_status == EACCES || file_read_status == EISDIR)	//?	Permission denied or is a directory
				_status_code = 500;
			else if (!file_read_status)
			{
				_status_code = 200;
				_head_params["Last-Modified"] = mod_date;
				_head_params["Content-Type"] = _request.config.filetypes.get_suffix(location->index);
				_body = get_body;
				return ;
			}
			else
				_status_code = 501;
		}
		else
		{
			_status_code = 501;
		}



	}
	else
		_status_code = 501;				//?	"Not implemented" error
	return_error_message(_status_code);
}

void Response::post_content()
{
//	struct stat file_info;
	std::map<std::string, std::string>::const_iterator item = _request.get_headermap().find("Transfer-Encoding");
	if (item != _request.get_headermap().end() && item->second == "chunked")
	{
		return_error_message(501, "Attempted to make a POST request encoded as \"chunked\".");
		_status_code = 501;
		return ;
	}
	item = _request.get_headermap().find("Content-Length");
	if (std::strtoul(item->second.c_str(), NULL, 10) > _request.get_location()->client_max_body_size)
	{
		return_error_message(413);
		_status_code = 413;
		return ;
	}
//	stat(_request.get_path_abs().c_str(), &file_info);
	std::string file_extension;
	size_t last_period = _request.get_path_rel().find_last_of('.');
	if (last_period != std::string::npos)
	{
		file_extension = _request.get_path_rel().substr(last_period + 1, _request.get_path_rel().size());
		std::map<std::string, std::string>::const_iterator cgi_item = _request.get_location()->cgi_execs.find(file_extension);
		if (cgi_item != _request.get_location()->cgi_execs.end())		//*	There's a CGI.
		{
			ft::cgi real_cgi(cgi_item->second, _request.get_path_abs(), _request, _request.config);
				//? or just call a formated error response
			_status_code = real_cgi.get_cgi_response_status();
			_body = real_cgi.get_cgi_response();
			LOG_COLOR(CYAN,"get_cgi_response_status" << real_cgi.get_cgi_response_status() << " " << _status_code );
			if (_status_code == 200 || _status_code == 302)
				_is_cgi_response = true;

			return ;
		}
		else															//* No CGI found
		{
			std::ofstream created_file;
			created_file.open(_request.get_path_abs());
			if (created_file.fail())
			{
				return_error_message(500, "The file couldn't be created.");
				_status_code = 500;
				return ;
			}
		}
	}
}

void Response::return_content()		//?		GET request
{
	std::cout << "";					//?	Fixes a Sanitizer error somehow.
	std::string mod_date;
	int status = 0;
	std::string get_body = get_file(_request.get_path_abs(), mod_date, &status);
	bool filetype_status;
	Filetypes get_filetype(&filetype_status);	//TODO	To be removed

	if (!filetype_status)
	{
		return_error_message(500, "The file containing the allowed file types can't be accessed.");
		_status_code = 500;
		_head_params["Content-Type"] = "text/html";
	}
	else if (status)
	{
		file_status_custom_error(status);
		if (_status_code != 200)
			_head_params["Content-Type"] = get_filetype.get("html");
	}
	else							//*	The file exists, has permissions and it's not a directory.
	{
		std::string file_extension;
		size_t last_period = _request.get_path_rel().find_last_of('.');
		if (last_period != std::string::npos)
		{
			file_extension = _request.get_path_rel().substr(last_period + 1, _request.get_path_rel().size());
			std::map<std::string, std::string>::const_iterator cgi_item = _request.get_location()->cgi_execs.find(file_extension);
			if (cgi_item != _request.get_location()->cgi_execs.end())				//*		The file IS part of the CGI list.
			{
				ft::cgi real_cgi(cgi_item->second, _request.get_path_abs(), _request, _request.config);				//*		Creating a cgi class.
				_status_code = real_cgi.get_cgi_response_status();
				_body = real_cgi.get_cgi_response();
				LOG_COLOR(CYAN,"get_cgi_response_status" << real_cgi.get_cgi_response_status() << " " << _status_code );
				if (_status_code == 200 || _status_code == 302)
					_is_cgi_response = true;
				return ;
			}
		}
						//*		vvv    The file is not part of the CGI    vvv
		_status_code = 200;
		_body = get_body;
		_head_params["Content-Type"] = get_filetype.get_suffix(_request.get_path_rel());
		_head_params["Last-Modified"] = mod_date;
	}
}

std::string Response::generate_response()
{
	std::string retval;
	retval.append("HTTP/1.1 ");
	retval.append(to_string(_status_code));
	retval.append(" ");
	retval.append(getMessageFromCode(_status_code));
	retval.append("\n");

	_head_params["Server"] = _request.config.server_name;
	_head_params["Content-Length"] = to_string(_body.length());
	_head_params["Date"] = get_date();
	for (std::map<std::string, std::string>::const_iterator it = _head_params.begin(); it != _head_params.end(); it++)
	{
		if (!(it->first == "Content-Type" && _is_cgi_response == true))
		{
			retval.append(it->first);
			retval.append(": ");
			retval.append(it->second);
			retval.append("\n");
		}
	}
	if (_is_cgi_response == false)
		retval.append("\n");
	retval.append(_body);
	return (retval);
}

}	// Nammespace ft
