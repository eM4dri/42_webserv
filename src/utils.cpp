/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:30:58 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/10 20:42:58 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"
#include <errno.h>	//	errno

/*
?	Function will split an std::string into new strings contained in an
?	std::vector, splitting every time a char is found.
*	Consecutive splitting characters are ignored, so they don't create extra strings.
*/
std::vector <std::string> cpp_split(std::string full_line, char splitter)
{
	std::vector <std::string> line_vector;
	std::string::iterator begin = full_line.begin();
	std::string::iterator end = full_line.begin();

	while (end != full_line.end() && *end == splitter)
		end++;
	begin = end;
	while (end != full_line.end())
	{
		while (end != full_line.end() && *end != splitter)
			end++;
		if (end != full_line.end())
		{
			line_vector.push_back(std::string(begin, end));
			while (*end == splitter)
				end++;
		}
		else
			line_vector.push_back(std::string(begin, end));
		begin = end;
	}
	return (line_vector);
}

/*
?	Function will return a whole file in a std::string format, including the
?	'\n' characters. The status field will be set to 0 if all goes well, and
?	errno if something goes wrong (check `man errno`).
*/
std::string file_reader(const std::string &filename, int *status)
{
	std::string		body;
	std::ifstream	file_instream;
	std::string		file_content_buff;
	file_instream.open(filename.c_str());

	if (!file_instream.is_open())
	{
		if (file_instream.fail())
		{
			if (status)
				*status = errno;
		}
		return ("");
	}
	else
	{
		if (status)
			*status = 0;
		while(std::getline(file_instream, file_content_buff))
		{
			body.append(file_content_buff);
			body.append("\n");
		}
		file_instream.close();
		return (body);
	}
}

/*
?	Function recieves a size of something in Bytes and formats it with the
?	most appropriate metric unit in a std::string form.
*/
std::string bytes_metric_formatting(long size)
{
	double		dsize = size;
	int			subdivisions = 0;
	char		units[] = {' ', 'k', 'M', 'G', 'T', 'P', 'E'};
	std::string retval;
	std::stringstream stream;

	while (dsize > 1024.0)
	{
		dsize /= 1024.0;
		subdivisions++;
	}
	if (subdivisions)
	{
		stream << std::fixed << std::setprecision(1) << dsize;
		retval = stream.str();
		retval.append(1, ' ');
		retval.append(1, units[subdivisions]);
	}
	else
	{
		stream << size;
		retval = stream.str();
		retval.append(1, ' ');
	}
	retval.append(1, 'B');
	return (retval);

}


/**
 * Formats the time_t struct passed and returns it as a string.
 * @param in_time Struct with the requested time to be displayed.
 * @param is_gmt Will append "GMT" at the end if true.
 * @retval "WDay, MDay Month Year HH:MM:SS GMT"
*/
std::string get_date(time_t in_time, bool is_gmt)
{
	std::string	retval;
	std::string wdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	std::string ymonths[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	tm *gmt_time;

	if (is_gmt)
		gmt_time = gmtime(&in_time);
	else
		gmt_time = localtime(&in_time);

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
	if (is_gmt)
		retval.append(" GMT");
	return (retval);
}

/**
 * Gets the current GMT date and returns it formatted in a string.
 * @retval "WDay, MDay Month Year HH:MM:SS GMT"
*/
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

/**
 * Recieves an int representing an error code and returns a string
 * with the message associated to the error code.
 * @param status_code Allowed ints: 100-101, 200-205, 300-303, 305-307, 400-406, 408-418, 421, 426, 428-429, 431, 451, 500-506, 510-511  |  Anything else returns "Error (x) not found".
*/
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
	else
	{
		std::string customerror = "Error ";
		customerror.append(to_string(status_code));
		customerror.append(" not found   ");
		customerror.append(TXT_BOLD_RED);
		customerror.append("--- PROBLEM! ---");
		customerror.append(TXT_RESET);
		return (customerror);
	}

}

/*
?	This function takes a string that has a path starting from a root and 
?	checks whether there are attempts to access files over the root or not.
?	If there are, it will delete those attempts remaining within the allowed
?	boundaries and returning a string with a safe path.
*/
std::string correct_path(const std::string &orig_path)
{
	std::vector <std::string> routes = cpp_split(orig_path, '/');
	std::vector<std::string>::iterator curr_route = routes.end() - 1;
	std::vector<std::string>::iterator curr_route_aux = routes.end();
	std::string retval;
	int level = 0;
	if (!routes.size())
		return ("");
	while (curr_route != routes.begin())
	{
		if (*curr_route == "~")
			break;
		else
			curr_route--;
	}
	if (*curr_route == "~")
		curr_route++;
	curr_route_aux = curr_route;

	while (curr_route != routes.end())
	{
		if (*curr_route == "..")
		{
			if (level - 1 < 0)
				routes.erase(curr_route);
			else
			{
				routes.erase(curr_route);
				curr_route--;
				routes.erase(curr_route);
			}
				
		}
		else if (*curr_route == ".")
			routes.erase(curr_route);
		else
		{
			level++;
			curr_route++;
		}

	}
	while (curr_route_aux != routes.end())
	{
		retval.append("/");
		retval.append(*curr_route_aux);
		curr_route_aux++;
	}
	if (retval[0] == '/')
		retval = retval.substr(1, retval.size() - 1);
	return (retval);
	
}

std::string correct_path(const std::string &orig_path, std::vector <std::string> routes)
{
	std::vector<std::string>::iterator curr_route = routes.end() - 1;
	std::vector<std::string>::iterator curr_route_aux = routes.end();
	std::string retval;
	int level = 0;
	if (!routes.size())
		return ("");
	while (curr_route != routes.begin())
	{
		if (*curr_route == "~")
			break;
		else
			curr_route--;
	}
	if (*curr_route == "~")
		curr_route++;
	curr_route_aux = curr_route;

	while (curr_route != routes.end())
	{
		if (*curr_route == "..")
		{
			if (level - 1 < 0)
				routes.erase(curr_route);
			else
			{
				routes.erase(curr_route);
				curr_route--;
				routes.erase(curr_route);
			}
				
		}
		else if (*curr_route == ".")
			routes.erase(curr_route);
		else
		{
			level++;
			curr_route++;
		}

	}
	while (curr_route_aux != routes.end())
	{
		retval.append("/");
		retval.append(*curr_route_aux);
		curr_route_aux++;
	}
	if (retval[0] == '/')
		retval = retval.substr(1, retval.size() - 1);
	return (retval);
	
}

//! Debugging purposes, please delete before evaluating.
void checkpoint(char *text)
{
	std::cout << text << std::endl;
}
