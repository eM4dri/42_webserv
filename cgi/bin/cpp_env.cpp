#include <iostream>

int main(int argc, char **agrv, char **envp)
{
	(void)argc;
	(void)agrv;
	unsigned int i = 0;
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<title>CGI Environment Variables</title>\n";
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	while (envp[i] != NULL)
	{
		std::cout << "<div>" << envp[i] << "</div>\n";
		i++;
	}
	std::cout << "</body>\n";
	std::cout << "</html>\n";
	return 0;
}
