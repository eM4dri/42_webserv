#include "responses.hpp"

std::string getMessageFromCode(int status_code)
{
	//?	Informational responses
	if (status_code == 100)
		return("Continue");
	else if (status_code == 101)
		return("Switching Protocols");

	//?	Successful responses
	else if (status_code == 200)
		return("OK");
	else if (status_code == 201)
		return("Created");
	else if (status_code == 202)
		return("Accepted");
	else if (status_code == 203)
		return("Non-Authoritative Information");
	else if (status_code == 204)
		return("No Content");
	else if (status_code == 205)
		return("Reset Content");

	//?	Redirection responses
	else if (status_code == 300)
		return("Multiple Choices");
	else if (status_code == 301)
		return("Moved Permanently");
	else if (status_code == 302)
		return("Found");
	else if (status_code == 303)
		return("See Other");
	else if (status_code == 305)
		return("Use Proxy");
	else if (status_code == 306)
		return("(Unused)");
	else if (status_code == 307)
		return("Temporary Redirect");

	//?	Client error responses
	else if (status_code == 400)
		return("Bad Request");
	else if (status_code == 401)
		return("Unauthorized");
	else if (status_code == 402)
		return("Payment Required");
	else if (status_code == 403)
		return("Forbidden");
	else if (status_code == 404)
		return("Not Found");
	else if (status_code == 405)
		return("Method Not Allowed");
	else if (status_code == 406)
		return("Not Acceptable");
	else if (status_code == 408)
		return("Request Timeout");
	else if (status_code == 409)
		return("Conflict");
	else if (status_code == 410)
		return("Gone");
	else if (status_code == 411)
		return("Length Required");
	else if (status_code == 412)
		return("Precondition Failed");
	else if (status_code == 413)
		return("Payload Too Large");
	else if (status_code == 414)
		return("URI Too Long");
	else if (status_code == 415)
		return("Unsupported Media Type");
	else if (status_code == 416)
		return("Range Not Satisfiable");
	else if (status_code == 417)
		return("Expectation Failed");
	else if (status_code == 418)
		return("I'm a teapot");
	else if (status_code == 421)
		return("Misdirected Request");
	else if (status_code == 426)
		return("Upgrade Required");
	else if (status_code == 428)
		return("Precondition Required");
	else if (status_code == 429)
		return("Too Many Requests");
	else if (status_code == 431)
		return("Request Header Fields Too Large");
	else if (status_code == 451)
		return("Unavailable For Legal Reasons");

	//?	Server error responses
	else if (status_code == 500)
		return("Internal Server Error");
	else if (status_code == 501)
		return("Not Implemented");
	else if (status_code == 502)
		return("Bad Gateway");
	else if (status_code == 503)
		return("Service Unavailable");
	else if (status_code == 504)
		return("Gateway Timeout");
	else if (status_code == 505)
		return("HTTP Version Not Supported");
	else if (status_code == 506)
		return("Variant Also Negotiates");
	else if (status_code == 510)
		return("Not Extended");
	else if (status_code == 511)
		return("Network Authentication Required");
	return ("Error not found");
}

std::string get_date()
{
	std::string	retval;
	std::string wdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	std::string ymonths[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	time_t now = time(NULL);
	tm *gmt_time = gmtime(&now);

	retval.append(wdays[gmt_time->tm_wday]);
	retval.append(", ");
	retval.append(to_string(gmt_time->tm_mday));
	retval.append(" ");
	retval.append(ymonths[gmt_time->tm_mon]);
	retval.append(" ");
	retval.append(to_string(gmt_time->tm_year + 1900));
	retval.append(" ");
	if (gmt_time->tm_hour < 10)
		retval.append("0");
	retval.append(to_string(gmt_time->tm_hour));
	retval.append(":");
	if (gmt_time->tm_min < 10)
		retval.append("0");
	retval.append(to_string(gmt_time->tm_min));
	retval.append(":");
	if (gmt_time->tm_sec < 10)
		retval.append("0");
	retval.append(to_string(gmt_time->tm_sec));
	retval.append(" GMT");
	return (retval);
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

std::string file_status_custom_error(int file_status, std::string path)
{
	std::string retval;
	if (file_status == ENOENT)			//?	File Not found
		retval = return_error_message(404);
	else if (file_status == EACCES)		//?	Permission denied
		retval = return_error_message(500);
	else if (file_status == EISDIR)		//?	Is a directory
	{
		retval = create_directory_index(path);
	}
	else
		retval = return_error_message(501);
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

std::string return_content(int status_code, std::string filename)
{
	std::string retvalue = "HTTP/1.1 ";
	std::string mod_date;
	int status = 0;
	std::string body = get_file(filename, mod_date, &status);
	Filetypes	get_filetype;

	if (status)
	{
		retvalue = file_status_custom_error(status, filename);
		return (retvalue);
	}
	retvalue.append(to_string(status_code));
	retvalue.append(" ");
	retvalue.append(getMessageFromCode(status_code));
	retvalue.append("\nDate: ");
	retvalue.append(get_date());
	retvalue.append("\nServer: WTF IDK LOL");
	retvalue.append("\nContent-Length: ");
	retvalue.append(to_string(body.length()));
	retvalue.append("\nContent-Type: ");
	retvalue.append(get_filetype.get_suffix(filename));
	retvalue.append("\nLast-Modified: ");
	retvalue.append(mod_date);

	

	retvalue.append("\n\n");
	retvalue.append(body);
	return (retvalue);
}
