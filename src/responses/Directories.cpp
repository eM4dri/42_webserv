#include "../general.hpp"

std::string create_directory_index(std::string path)
{
	DIR			*directorylist;
	dirent		*directoryitem;
	std::string retval;
	struct stat fileinfo;
	std::string fullpath;

	directorylist = opendir(path.c_str());

	directoryitem = readdir(directorylist);
	directoryitem = readdir(directorylist);
	retval.append("<html>\n");
	retval.append("<head><title>Webserv</title></head>\n");
	retval.append("<body>\n");
	retval.append("\t<h1>Index of ");
	retval.append(path);
	retval.append("</h1>\n<hr>");

	if (!strcmp(directoryitem->d_name, ".."))
	{
		retval.append("\t<table>\n");
		retval.append("\t\t<tbody>\n");
		retval.append("\t\t\t<tr><td>🔙</td> <td><a href=\"./..\">[parent directory]</a></td><tr>\n");
		retval.append("\t\t</tbody>\n");
		retval.append("\t</table>\n");
		
		directoryitem = readdir(directorylist);
	}

	retval.append("\t<table>\n");
	retval.append("\t\t<thead>\n");
	retval.append("\t\t\t<th></th> <th> Name </th> <th> Size </th> <th>    Date Modified    </th>");
	retval.append("\t\t</thead>\n");
	retval.append("\t\t<tbody>\n");

	while (directoryitem)
	{
		fullpath = path;
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
		retval.append(get_date((time_t)fileinfo.st_mtimespec.tv_sec, false));
		retval.append("</td>");


		retval.append("</tr>\n");
		directoryitem = readdir(directorylist);
	}

	retval.append("\t\t</tbody>\n");
	retval.append("\t</table>\n");
	retval.append("</body>\n");
	retval.append("</html>\n");

	return (retval);
}
