/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <jvacaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:30:58 by jvacaris          #+#    #+#             */
/*   Updated: 2023/05/05 20:44:10 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"

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
