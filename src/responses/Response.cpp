/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:23 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/05 20:48:34 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"


Response::Response(): request(Request())
{
}

Response::Response(const Request _request): request(_request)
{
	return_content();
	std::cout << std::endl << generate_response() << std::endl;
}

void Response::return_error_message(int error_code)
{
	std::string retval;
	std::string error_reason = to_string(error_code);
	error_reason.append(" ");
	error_reason.append(getMessageFromCode(error_code));

	status_code = error_code;
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
	retval.append("\t</body>");
	retval.append("</html>");
	body = retval;
}

void Response::file_status_custom_error(int file_status)
{
	std::string retval;
	if (file_status == ENOENT)			//?	File Not found
		status_code = 404;
	else if (file_status == EACCES)		//?	Permission denied
		status_code = 500;
	else if (file_status == EISDIR)		//?	Is a directory. Permissions have been chacked previously so there should be no errors from now on.
	{
		status_code = 200;
		retval = create_directory_index();
		body = retval;
		return ;
	}
	else
		status_code = 501;				//?	"Not implemented" error
	return_error_message(status_code);
}

std::string get_file(std::string filename, std::string &mod_date, int *status)
{
	std::string		file_content;
	struct stat file_info;
	int			file_status = 0;
	int			is_dir;

	file_content = file_reader(filename, &file_status);
	is_dir = stat(filename.c_str(), &file_info);
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
		mod_date = get_date(file_info.st_mtime, true);
	*status = 0;
	return(file_content);
}


void Response::return_content()
{
	std::string mod_date;
	int status = 0;
	std::string get_body = get_file(request.get_path_abs(), mod_date, &status);
	Filetypes get_filetype;

	if (status)
	{
		/*body = */file_status_custom_error(status);
		head_params["Content-Type"] = get_filetype.get("html");
	}
	else
	{
		status_code = 200;
		body = get_body;
		head_params["Content-Type"] = get_filetype.get_suffix(request.get_path_rel());
		head_params["Last-Modified"] = mod_date;
	}
	head_params["Server"] = "IDK 4.2"; 		// TODO
	head_params["Content-Length"] = to_string(body.length());
}

std::string Response::generate_response()
{
	std::string retval;

	retval.append("HTTP/1.1 ");
	retval.append(to_string(status_code));
	retval.append(" ");
	retval.append(getMessageFromCode(status_code));
	retval.append("\n");

	head_params["Date"] = get_date();
	for (std::map<std::string, std::string>::const_iterator it = head_params.begin(); it != head_params.end(); it++)
	{
		retval.append(it->first);
		retval.append(": ");
		retval.append(it->second);
		retval.append("\n");
	}
	retval.append("\n");
	retval.append(body);
	return (retval);
}

