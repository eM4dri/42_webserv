/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:44:23 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/03 20:24:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(const Request _request): request(_request)
{
	return_content();
	std::cout << std::endl << "--------------" << std::endl << generate_response() << std::endl << "--------------" << std::endl;
}

std::string Response::reply()
{
	if (request.get_method() == GET)
	{
		
	}
	return (""); // TODO
}


std::string return_error_message(int status_code)
{
	std::string		error_reason;
	std::string		retvalue;
	int				status;
	std::string		body  = file_reader(ERROR_TEMPLATE, &status);

	error_reason.append(to_string(status_code));
	error_reason.append(" ");
	error_reason.append(getMessageFromCode(status_code));

	if (body.size() > 2)
	{
		body.replace(body.find("{PAGE_TITLE}", 0), sizeof("{PAGE_TITLE}") - 1, error_reason);
		body.replace(body.find("{H1_TITLE}", 0), sizeof("{H1_TITLE}") - 1, error_reason);
	}

	retvalue.append("HTTP/1.1 ");
	retvalue.append(to_string(status_code));
	retvalue.append(" ");
	retvalue.append(getMessageFromCode(status_code));
	retvalue.append("\nDate: ");
	retvalue.append(get_date());
	retvalue.append("\nServer: WTF IDK LOL");
	retvalue.append("\nContent-Length: ");
	retvalue.append(to_string(body.length()));
	retvalue.append("\nContent-Type: ");
	retvalue.append("text/html");

	retvalue.append("\n\n");
	retvalue.append(body);
	return(retvalue);
}

std::string Response::file_status_custom_error(int file_status)
{
	std::string retval;
	if (file_status == ENOENT)			//?	File Not found
		status_code = 404;
	else if (file_status == EACCES)		//?	Permission denied
		status_code = 500;
	else if (file_status == EISDIR)		//?	Is a directory
	{
		retval = create_directory_index(request.get_path_abs());
		return (retval);
	}
	else
		status_code = 501;
	retval = return_error_message(status_code);
	return (retval);
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
		body = file_status_custom_error(status);
	}
	else
	{
		status_code = 200;
		body = get_body;
	}
	head_params["Date"] = get_date();
	head_params["Server"] = "IDK 4.2"; 		// TODO
	head_params["Content-Length"] = to_string(body.length());
	head_params["Content-Type"] = get_filetype.get_suffix(request.get_path_rel());
	head_params["Last-Modified"] = mod_date;


}

std::string Response::generate_response()
{
	std::string retval;

	retval.append("HTTP/1.1 ");
	retval.append(to_string(status_code));
	retval.append(" ");
	retval.append(getMessageFromCode(status_code));
	retval.append("\n");

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

