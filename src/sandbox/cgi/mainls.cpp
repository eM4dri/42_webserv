#include <unistd.h>	//	execve, fork, pipe
#include <cstring>	//	menset, fork, pipe
#include <sstream>	// std::stringstream
#include <iostream> //	std::cout, std::endl

enum e_pipe_fd
{
	READ_END,
	WRITE_END
};

/*
g++ -Wall -Wextra -Werror mainls.cpp -o testls && ./testls && rm testls
*/
int main(void)
{
	int		status;
	pid_t	pid;
	int		fd[2];
	const char *argv[] = {"/bin/ls", "-la", NULL};
	char **envp;
	envp = NULL;

	pipe(fd);
	pid = fork();
	if (!pid)	//	son
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve(argv[0], const_cast<char **>(argv), envp);
	}
	else	//	father
	{
		char	buff[USHRT_MAX]={0};
		std::memset(buff, 0, USHRT_MAX);
		read(fd[READ_END], buff, USHRT_MAX - 1);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		waitpid(pid, &status, 0);
		std::ostringstream ss;
		ss << buff;
		std::cerr << buff << std::endl;
	}
}