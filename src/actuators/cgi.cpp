/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/03 18:08:17 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include <unistd.h>	//	execve, fork, pipe

# define SON 0
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
	_add_env(std::string("AUTH_TYPE"));
	_add_env(std::string("CONTENT_LENGTH"));
	_add_env(std::string("CONTENT-TYPE"));
	_add_env(std::string("GATEWAY_INTERFACE=CGI/1.1"));
	_add_env(std::string("PATH_INFO"));
	_add_env(std::string("PATH_TRANSLATED"));
	_add_env(std::string("QUERY_STRING"));
	_add_env(std::string("REMOTE_ADDR=127.0.0.1"));
	_add_env(std::string("REMOTE_HOST"));
	_add_env(std::string("REQUEST_METHOD=GET"));
	_add_env(std::string("SCRIPT_NAME=./tests/www/localhost/reply.py"));
	_add_env(std::string("SERVER_NAME=localhost"));
	_add_env(std::string("SERVER_PORT=9000"));
	_add_env(std::string("SERVER_PROTOCOL=HTTP/1.1"));
	_add_env(std::string("SERVER_SOFTWARE=42WebServer/1.0"));
	_add_env(std::string("HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"));
	_add_env(std::string("HTTP_ACCEPT_ENCODING=gzip, deflate, br"));
	_add_env(std::string("HTTP_ACCEPT_LANGUAGE=en_US,en;q=0.5"));
	_add_env(std::string("HTTP_COOKIE=HIPPIE_COOKIE=42"));
	_add_env(std::string("HTTP_USER_AGENT=Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:108.0) Gecko/20100101 Firefox/108.0"));
}

void cgi::_add_env(const std::string & input)
{
	char *cstr = new char[input.length() + 1];
	strcpy(cstr, input.c_str());
	// do stuff
	_env.push_back(cstr);
	delete [] cstr;

}


template<class InputIterator, class OutputIterator>
  OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
{
  while (first!=last) {
    *result = *first;
    ++result; ++first;
  }
  return result;
}

void cgi::_execute(void)
{
	char	**envp;
	char	*argv[2];
	pid_t	pid;
	int		fd[2];
	const std::string exe("/usr/local/bin/python3");
	const std::string binary("tests_files/reply.py");


	argv[0] = const_cast<char *>(exe.c_str());
	argv[1] = const_cast<char *>(binary.c_str());
	pid = fork();
	if (pid < 0)
		;	// error
	if (pid == SON)
	{
		if (pipe(fd) < 0)
			;	//	error
		dup2(fd[READ_END], STDIN_FILENO);
		dup2(fd[WRITE_END], STDOUT_FILENO);
	}
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	if (pid == SON)
	{
		envp = new char *[_env.size()+1];
		std::copy(_env.begin(), _env.end(), envp);
		execve(argv[0], argv, envp);
	}
}


//Private

}	// Nammespace ft

