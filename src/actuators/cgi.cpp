/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/07 09:49:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include "utils/log.hpp"
#include <unistd.h>		//	execve, fork, pipe
#include <cstring>		//	menset, fork, pipe
#include <sstream>		//	std::stringstream
#include <climits>		//	USHRT_MAX
#include <sys/types.h>	//	waitpid
#include <sys/wait.h>	//	waitpid

enum e_pipe_fd
{
	READ_END,
	WRITE_END
};
namespace ft
{

//Constructor
cgi::cgi()
{
	_populate_env();
	_execute();
}

//Destructor
cgi::~cgi() {
	if (_env.size())
		_env.clear();
}

void cgi::_populate_env(void)
{
	// _env.push_back(strdup());
	_env.push_back(strdup("AUTH_TYPE"));
	_env.push_back(strdup("CONTENT_LENGTH"));
	_env.push_back(strdup("CONTENT-TYPE"));
	_env.push_back(strdup("GATEWAY_INTERFACE=CGI/1.1"));
	_env.push_back(strdup("PATH_INFO"));
	_env.push_back(strdup("PATH_TRANSLATED"));
	_env.push_back(strdup("QUERY_STRING"));
	_env.push_back(strdup("REMOTE_ADDR=127.0.0.1"));
	_env.push_back(strdup("REMOTE_HOST"));
	_env.push_back(strdup("REQUEST_METHOD=GET"));
	_env.push_back(strdup("SCRIPT_NAME=./tests/www/localhost/reply.py"));
	_env.push_back(strdup("SERVER_NAME=localhost"));
	_env.push_back(strdup("SERVER_PORT=9000"));
	_env.push_back(strdup("SERVER_PROTOCOL=HTTP/1.1"));
	_env.push_back(strdup("SERVER_SOFTWARE=42WebServer/1.0"));
	_env.push_back(strdup("HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	_env.push_back(strdup("HTTP_ACCEPT_ENCODING=gzip, deflate, br"));
	_env.push_back(strdup("HTTP_ACCEPT_LANGUAGE=en_US,en;q=0.5"));
	_env.push_back(strdup("HTTP_COOKIE=HIPPIE_COOKIE=42"));
	_env.push_back(strdup("HTTP_USER_AGENT=Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:108.0) Gecko/20100101 Firefox/108.0"));
}

// void cgi::_add_env(const std::string & input)
// {
// 	char *cstr = new char[input.length() + 1];
// 	strcpy(cstr, input.c_str());
// 	_env.push_back(cstr);
// }

template <typename T>
void _print_vector(std::vector<T> & vector)
{
	for (typename std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
		LOG(*it);
}

template <typename T>
void _print_array_null_ending(T **array)
{
	if (*array != NULL)
		while (*array != NULL)
			LOG(*array++);
}

void cgi::_execute(void)
{
	const char *argv[] = {"/usr/local/bin/python3", "test_files/reply.py", NULL};
	int			status;
	pid_t		pid;
	int			fd[2];

	pipe(fd);
	pid = fork();
	if (!pid)	//	son
	{
		char **envp = new char *[_env.size() + 1];
		std::copy(_env.begin(), _env.end(), envp);
		envp[_env.size()] = NULL;
		// _print_array_null_ending(envp);
		// _print_vector(_env);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		execve(argv[0], const_cast<char **>(argv), envp);
	}
	else	//	father
	{
		close(fd[WRITE_END]);
		char	buff[USHRT_MAX]={0};
		std::memset(buff, 0, USHRT_MAX);
		read(fd[READ_END], buff, USHRT_MAX);
		close(fd[READ_END]);
		waitpid(pid, &status, 0);
		std::ostringstream ss;
		ss << buff;
		_response = ss.str();;
	}
}

std::string const & cgi::get_response() const
{
	return _response;
}

}	// Nammespace ft
