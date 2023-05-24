/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:23 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/24 15:43:12 by emadriga         ###   ########.fr       */
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

Response::Response(const Request &_request): _request(_request)
{
	if (_request.get_method() < 0)
	{
		if (_request.get_method() == -1)
			return_error_message(400);
		else if (_request.get_method() == -2)
			return_error_message(505);
		_head_params["Content-Type"] = "text/html";
	}
	else if (_request.get_location()->redirect.first != 0)
	{
		return_error_message(_request.get_location()->redirect.first);
		_head_params["Location"] = _request.get_location()->redirect.second;
	}
	else
	{
		return_content();
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
		const location *location = _request.get_location();
		LOG_COLOR(YELLOW, location->index);
		LOG_COLOR(YELLOW, location->request_path);
		LOG_COLOR(YELLOW, location->methods);

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


void Response::return_content()
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
	else
	{
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

	_head_params["Server"] = SERVER_NAME;
	_head_params["Content-Length"] = to_string(_body.length());
	_head_params["Date"] = get_date();
	for (std::map<std::string, std::string>::const_iterator it = _head_params.begin(); it != _head_params.end(); it++)
	{
		retval.append(it->first);
		retval.append(": ");
		retval.append(it->second);
		retval.append("\n");
	}
	retval.append("\n");
	retval.append(_body);
	return (retval);
}

}	// Nammespace ft
