#include "responses.hpp"

/*
?	Everything here are old functions.
! 	The file will be deleted in the following commits.
*/

// std::string return_error_message(int status_code)
// {
// 	std::string		error_reason;
// 	std::string		retvalue;
// 	int				status;
// 	std::string		body  = file_reader(ERROR_TEMPLATE, &status);

// 	error_reason.append(to_string(status_code));
// 	error_reason.append(" ");
// 	error_reason.append(getMessageFromCode(status_code));

// 	if (body.size() > 2)
// 	{
// 		body.replace(body.find("{PAGE_TITLE}", 0), sizeof("{PAGE_TITLE}") - 1, error_reason);
// 		body.replace(body.find("{H1_TITLE}", 0), sizeof("{H1_TITLE}") - 1, error_reason);
// 	}

// 	retvalue.append("HTTP/1.1 ");
// 	retvalue.append(to_string(status_code));
// 	retvalue.append(" ");
// 	retvalue.append(getMessageFromCode(status_code));
// 	retvalue.append("\nDate: ");
// 	retvalue.append(get_date());
// 	retvalue.append("\nServer: WTF IDK LOL");
// 	retvalue.append("\nContent-Length: ");
// 	retvalue.append(to_string(body.length()));
// 	retvalue.append("\nContent-Type: ");
// 	retvalue.append("text/html");

// 	retvalue.append("\n\n");
// 	retvalue.append(body);
// 	return(retvalue);
// }

// std::string file_status_custom_error(int file_status, std::string path)
// {
// 	std::string retval;
// 	if (file_status == ENOENT)			//?	File Not found
// 		retval = return_error_message(404);
// 	else if (file_status == EACCES)		//?	Permission denied
// 		retval = return_error_message(500);
// 	else if (file_status == EISDIR)		//?	Is a directory
// 	{
// 		retval = create_directory_index(path);
// 	}
// 	else
// 		retval = return_error_message(501);
// 	return (retval);
// }

// std::string get_file(std::string filename, std::string &mod_date, int *status)
// {
// 	std::string		file_content;
// 	struct stat file_info;
// 	int			file_status = 0;
// 	int			is_dir;

// 	file_content = file_reader(filename, &file_status);
// 	is_dir = stat(filename.c_str(), &file_info);
// 	if (file_status)
// 	{
// 		*status = file_status;
// 		return("");
// 	}
// 	else if (file_info.st_mode & S_IFDIR)
// 	{
// 		*status = EISDIR;
// 		return("");
// 	}
// 	else
// 		mod_date = get_date(file_info.st_mtime, true);
// 	*status = 0;
// 	return(file_content);
// }

// std::string return_content(int status_code, std::string filename)
// {
// 	std::string retvalue = "HTTP/1.1 ";
// 	std::string mod_date;
// 	int status = 0;
// 	std::string body = get_file(filename, mod_date, &status);
// 	Filetypes	get_filetype;

// 	if (status)
// 	{
// 		retvalue = file_status_custom_error(status, filename);
// 		return (retvalue);
// 	}
// 	retvalue.append(to_string(status_code));
// 	retvalue.append(" ");
// 	retvalue.append(getMessageFromCode(status_code));
// 	retvalue.append("\nDate: ");
// 	retvalue.append(get_date());
// 	retvalue.append("\nServer: WTF IDK LOL");
// 	retvalue.append("\nContent-Length: ");
// 	retvalue.append(to_string(body.length()));
// 	retvalue.append("\nContent-Type: ");
// 	retvalue.append(get_filetype.get_suffix(filename));
// 	retvalue.append("\nLast-Modified: ");
// 	retvalue.append(mod_date);

	

// 	retvalue.append("\n\n");
// 	retvalue.append(body);
// 	return (retvalue);
// }

