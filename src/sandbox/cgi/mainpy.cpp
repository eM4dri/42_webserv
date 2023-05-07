#include <unistd.h>	//	execve, fork, pipe
#include <cstring>	//	menset, fork, pipe
#include <sstream>	//	std::stringstream
#include <iostream> //	std::cout, std::endl

enum e_pipe_fd
{
	READ_END,
	WRITE_END
};

/*
g++ -Wall -Wextra -Werror mainpy.cpp -o testpy && ./testpy && rm testpy
*/
int main(void)
{
	int		status;
	pid_t	pid;
	int		fd[2];
	const char *argv[] = {"/usr/local/bin/python3",	"reply.py", NULL};
	const char *envp[] = {
		"AUTH_TYPE",
		"CONTENT_LENGTH",
		"CONTENT-TYPE",
		"GATEWAY_INTERFACE=CGI/1.1",
		"PATH_INFO",
		"PATH_TRANSLATED",
		"QUERY_STRING",
		"REMOTE_ADDR=127.0.0.1",
		"REMOTE_HOST",
		"REQUEST_METHOD=GET",
		"SCRIPT_NAME=./tests/www/localhost/reply.py",
		"SERVER_NAME=localhost",
		"SERVER_PORT=9000",
		"SERVER_PROTOCOL=HTTP/1.1",
		"SERVER_SOFTWARE=42WebServer/1.0",
		"HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
		"HTTP_ACCEPT_ENCODING=gzip, deflate, br",
		"HTTP_ACCEPT_LANGUAGE=en_US,en;q=0.5",
		"HTTP_COOKIE=HIPPIE_COOKIE=42",
		"HTTP_USER_AGENT=Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:108.0) Gecko/20100101 Firefox/108.0",
		NULL
	};
	pipe(fd);
	pid = fork();
	if (!pid)	//	son
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		execve(argv[0], const_cast<char **>(argv), const_cast<char **>(envp));
	}
	else	//	father
	{
		char	buff[USHRT_MAX]={0};
		std::memset(buff, 0, USHRT_MAX);
		read(fd[READ_END], buff, USHRT_MAX);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		waitpid(pid, &status, 0);
		std::ostringstream ss;
		ss << buff;
		std::cout << buff << std::endl;
	}
}