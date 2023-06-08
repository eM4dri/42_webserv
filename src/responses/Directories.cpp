#include "Response.hpp"

#ifdef __APPLE__
#ifndef st_mtime
#define st_mtime st_mtimespec.tv_sec
#endif
#endif

namespace ft
{

std::string Response::create_directory_index()
{
	DIR			*directorylist;
	dirent		*directoryitem;
	std::string retval;
	struct stat fileinfo;
	std::string fullpath;

	directorylist = opendir(_request.get_path_abs().c_str());

	directoryitem = readdir(directorylist);
	directoryitem = readdir(directorylist);
	retval.append("<html>\n");
	retval.append("<head><title>Webserv</title><meta charset=\"UTF-8\"></head>\n");
	retval.append("<body>\n");
	retval.append("\t<h1>Index of /");
	retval.append(_request.get_path_rel());
	retval.append("</h1>\n<hr>");

	if (_request.get_path_rel().size() > 1)
	{
		retval.append("\t<table>\n");
		retval.append("\t\t<tbody>\n");
		retval.append("\t\t\t<tr><td>🔙</td> <td><a href=\"./..\">[parent directory]</a></td><tr>\n");
		retval.append("\t\t</tbody>\n");
		retval.append("\t</table>\n\n");

		directoryitem = readdir(directorylist);
	}

	retval.append("\t<table>\n");
	retval.append("\t\t<thead>\n");
	retval.append("\t\t\t<th></th> <th> Name </th> <th> Size </th> <th>    Date Modified    </th>");
	retval.append("\t\t</thead>\n");
	retval.append("\t\t<tbody>\n");

	while (directoryitem)
	{
		if (std::strcmp(directoryitem->d_name, ".."))
		{
			fullpath = _request.get_path_abs();
			fullpath.append("/");
			fullpath.append(directoryitem->d_name);
			if (stat(fullpath.c_str(), &fileinfo))
				perror(fullpath.c_str());
			retval.append("<tr>");
			retval.append("<td>");
			if (directoryitem->d_type == 4)
				retval.append("📁");
			else if (directoryitem->d_type == 8)
				retval.append("📄");
			else
				retval.append("❌ THIS SHOULD NOT BE PRINTED ❌");
			retval.append("</td><td>");
			retval.append("<a href=\"./");
			retval.append(directoryitem->d_name);
			retval.append("\">");
			retval.append(directoryitem->d_name);
			retval.append("</a></td><td style=\"padding:0 20px 0 20px;\">");
			if (directoryitem->d_type == 8)
				retval.append(bytes_metric_formatting(fileinfo.st_size));
			retval.append("</td><td style=\"padding:0 20px 0 20px;\">");
			retval.append(get_date((time_t)fileinfo.st_mtime, false));
			retval.append("</td>");
			retval.append("</tr>\n");
		}
		directoryitem = readdir(directorylist);
	}

	retval.append("\t\t</tbody>\n");
	retval.append("\t</table>\n");
	retval.append("</body>\n");
	retval.append("</html>\n");
	closedir(directorylist);
	return (retval);
}

}	// Nammespace ft
