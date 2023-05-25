/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:16:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/05/25 18:26:11 by emadriga         ###   ########.fr       */
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
	: _cgi_exec(cgi_exec), _cgi_script(cgi_script), _request(request), _conf(conf), _cgi_response_status(0)
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

void cgi::_add_header_to_env(const std::string &env_var, const std::string & header)
{
	if (_request.get_headermap().find(header) != _request.get_headermap().end())
		_env.push_back(env_var);
	// else
	// 	_env.push_back(env_var + "=" + header);

}

void cgi::_populate_env(  )
{
	_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("SERVER_SOFTWARE=42WebServer/1.0");

	_env.push_back("REMOTE_ADDR=" + _conf.address);
	_env.push_back("REQUEST_METHOD=" + _request.get_method_txt());
	_env.push_back("SERVER_NAME=" + _conf.server_name);
	_env.push_back("SERVER_PORT=" + to_string(_conf.port) );
	// if (_request.get_method_txt() == "POST")
	// 	_env.push_back("QUERY_STRING=user_login=marvin&user_message=marvin+al+habla");
	if (!_request.get_body().empty())
	// 	_env.push_back("QUERY_STRING");
	// else
		_env.push_back("QUERY_STRING=" + _request.get_body());
	// _env.push_back("PATH_INFO");
	// _env.push_back("PATH_TRANSLATED");
	if (_cgi_script.length())
	{
		_env.push_back("SCRIPT_FILENAME=" + _cgi_script);
		std::size_t name_pos = _cgi_script.find_last_of('/');
		if (name_pos != std::string::npos)
			_env.push_back("SCRIPT_NAME=" + _cgi_script.substr(_cgi_script.find_last_of('/')));
	}
	_add_header_to_env("AUTH_TYPE", "Authorization");
	_add_header_to_env("CONTENT_LENGTH", "Content-Length");
	_add_header_to_env("CONTENT-TYPE", "Content-Type");
	_add_header_to_env("HTTP_ACCEPT", "Accept");
	_add_header_to_env("HTTP_ACCEPT_ENCODING", "Accept-Encoding");
	_add_header_to_env("HTTP_ACCEPT_LANGUAGE", "Accept-Language");
	_add_header_to_env("HTTP_USER_AGENT", "User-Agent");
	_add_header_to_env("HTTP_COOKIE", "Cookie");
	_add_header_to_env("HTTP_HOST", "Host");
	_add_header_to_env("HTTP_FORWARDED", "Forwarded");
	_add_header_to_env("HTTP_ACCEPT_CHARSET", "Accept-Charset");
	_add_header_to_env("HTTP_PROXY_AUTHORIZATION", "Proxy-Authorization");
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
		LOG_ERROR("execve() returns only on error");	//	execve() returns only on error // exec not available or not enough access on Asscess Control List
		exit(EXIT_FAILURE);
	}
	else	//	father
	{
		close(fd[WRITE_END]);
		char	buff[USHRT_MAX]={0};
		std::memset(buff, 0, USHRT_MAX);
		read(fd[READ_END], buff, USHRT_MAX);
		close(fd[READ_END]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
			{
				LOG_ERROR("CGI exits with status " << status);
				_cgi_response_status = 500;
			}
		}
		std::ostringstream ss;
		ss << buff;
		_cgi_response = ss.str();
		if (_cgi_response_status != 500)
			_cgi_response_status = (_cgi_response.find("Location") != std::string::npos) ? 302 : 200;
		LOG_COLOR(YELLOW, "_cgi_response_status " << _cgi_response_status);
	}
}

std::string const & cgi::get_cgi_response() const
{
	return _cgi_response;
}

int const & cgi::get_cgi_response_status() const
{
	return _cgi_response_status;
}

}	// Nammespace ft
