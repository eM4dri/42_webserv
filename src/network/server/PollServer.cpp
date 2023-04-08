/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:15:12 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/02 01:17:10 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollServer.hpp"
#define WELCOME_MESSAGE "Hello from server\n"
#define INITIAL_POLL_FD_SIZE 5

//Private
//Functions to handle connections
void ft::PollServer::_accepter()
{
	ListenSocket wsSocket = get_listening_socket();
	struct sockaddr_in	wsAddress = wsSocket.get_address();
	int wsAddressLen = sizeof(wsAddress);
	int newclientSocket_fd = accept(wsSocket.get_socketfd(), (struct sockaddr *)&wsAddress, (socklen_t*)&wsAddressLen);
	if (newclientSocket_fd == -1)
	{
		perror("accept");
	}
	else
	{
		_add_to_pfds(newclientSocket_fd);
		printf("pollserver: new connection on socket %d\n", newclientSocket_fd); // molaría printear la IP
		_responder(newclientSocket_fd);
	}
}

void ft::PollServer::_handler(int index_fd)
{
    char 	buffer[BUFFER_SIZE];

    size_t nbytes = recv(_pfds[index_fd].fd, buffer, sizeof buffer, 0);
	if (nbytes > 0 )
    {
        std::cout << "client(socket " << _pfds[index_fd].fd << ")  says: " << buffer;
        _echo(index_fd, buffer, nbytes);
        return;
    }
    // got error or connection closed by client
    if (nbytes == 0)
    {
        // connection closed
        printf("selectserver: socket %d hung up\n", _pfds[index_fd].fd);
    }
    else
    {
        perror("recv");
    }                        
	close(_pfds[index_fd].fd); // Bye!

	_del_from_pfds(index_fd);
}

void ft::PollServer::_responder(int client_fd)
{
    const size_t len = strlen(WELCOME_MESSAGE);
    send(client_fd, WELCOME_MESSAGE, len, 0);
}

// Add a new file descriptor to the set
void ft::PollServer::_add_to_pfds(int newfd)
{
    // If we don't have room, add more space in the pfds array
    if (_poll_fd_count == _poll_fd_size)
    {
        _poll_fd_size *= 2; // Double it

        _pfds = (struct pollfd *)realloc(_pfds, sizeof (*_pfds) * _poll_fd_size);
    }
	_pfds[_poll_fd_count].fd = newfd;
	_pfds[_poll_fd_count].events = POLLIN; // Check ready-to-read
    _poll_fd_count++;
}

// Remove an index from the set
void ft::PollServer::_del_from_pfds(int index_fd)
{
    // Copy the one from the end over this one
   _pfds[index_fd] = _pfds[_poll_fd_count - 1];

    _poll_fd_count--;
}

void ft::PollServer::_echo(int index_fd, char const *str, size_t nbytes)
{
    for (int i = 0; i <= _poll_fd_count; i++)
    {
		if (i != index_fd && i != 0)
			send(_pfds[i].fd, str, nbytes, 0);
    }
}

//Public
//Constructor
ft::PollServer::PollServer(int domain, int type, int protocol, u_long interface, int port, int backlog) 
	: AServer(domain, type, protocol, interface, port, backlog), _poll_fd_size(INITIAL_POLL_FD_SIZE)
{
	_pfds = (struct pollfd *)malloc(sizeof (*_pfds) * _poll_fd_size);
	// Add the listener to set
    _pfds[0].fd = get_listening_socket().get_socketfd();
    _pfds[0].events = POLLIN; // Report ready to read on incoming connection
	_poll_fd_count++;
	launch();
}

//Function to  launch server
void ft::PollServer::launch(void)
{
	while (true)
	{
		int poll_count = poll(_pfds, _poll_fd_count, -1);
        if (poll_count == -1)
        {
            perror("poll");
            exit(1);
        }
		for (int i = 0; i < _poll_fd_count; i++)
        {
			// Check if someone's ready to read
            if (_pfds[i].revents & POLLIN)
            { // We got one!!
				  if (i == 0) //server
					_accepter();
				else
					_handler(i);
			}     // END got ready-to-read from poll()

		}    // END looping through file descriptors
	}
}
