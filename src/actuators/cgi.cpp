/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/12 17:02:10 by emadriga         ###   ########.fr       */
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
cgi::cgi( const std::string & cgi_exec, const std::string & cgi_script, const Request & request , const serverconf & conf )
	: _cgi_exec(cgi_exec), _cgi_script(cgi_script), _request(request), _conf(conf)
{
	_populate_env();
	_execute();
}

//Destructor
cgi::~cgi() {
	if (_env.size())
	{
		_env.clear();
	}
}

void cgi::_populate_env(  )
{
	_env.push_back("AUTH_TYPE");
	_env.push_back("CONTENT_LENGTH");
	_env.push_back("CONTENT-TYPE");
	_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	_env.push_back("PATH_INFO");
	_env.push_back("PATH_TRANSLATED");
	_env.push_back("QUERY_STRING");
	_env.push_back("REMOTE_ADDR=" + _conf.address);
	_env.push_back("REMOTE_HOST");
	_env.push_back("REQUEST_METHOD=" + _request.get_method_txt());
	_env.push_back("SCRIPT_NAME=./tests/www/localhost/reply.py");
	_env.push_back("SERVER_NAME=localhost");
	_env.push_back("SERVER_PORT=" + to_string(_conf.port) );
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("SERVER_SOFTWARE=42WebServer/1.0");
	_env.push_back("HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
	_env.push_back("HTTP_ACCEPT_ENCODING=gzip, deflate, br");
	_env.push_back("HTTP_ACCEPT_LANGUAGE=en_US,en;q=0.5");
	_env.push_back("HTTP_COOKIE=HIPPIE_COOKIE=42");
	_env.push_back("HTTP_USER_AGENT=Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:108.0) Gecko/20100101 Firefox/108.0");
}

void cgi::_execute(void)
{
	const char *argv[] = {_cgi_exec.c_str(), _cgi_script.c_str(), NULL};
	int			status;
	pid_t		pid;
	int			fd[2];

	pipe(fd);
	pid = fork();
	if (!pid)	//	son
	{
		// print_vector(_env);
		char **envp = new char *[_env.size() + 1];
		for (size_t i = 0; i != _env.size(); i++ )
		{
			envp[i] = new char [_env[i].length() + 1];
			std::strcpy (envp[i], _env[i].c_str());
		}
		envp[_env.size()] = NULL;
		// print_array_null_ending(envp);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (_cgi_exec == "")
			execve(argv[1], const_cast<char **>(&argv[1]), envp);
		else
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
		_cgi_response = ss.str();
	}
}

std::string const & cgi::get_cgi_response() const
{
	return _cgi_response;
}

}	// Nammespace ft
