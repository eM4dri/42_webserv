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

#include "SelectServer.hpp"
#define WELCOME_MESSAGE "Hello from server\n"
#define BUFFER_SIZE 256

//Private
//Functions to handle connections
void ft::SelectServer::_accepter()
{
	ListenSocket wsSocket = get_listening_socket();
	struct sockaddr_in	wsAddress = wsSocket.get_address();
	int wsAddressLen = sizeof(wsAddress);
	int newclientSocket_fd = accept(wsSocket.get_socketfd(), (struct sockaddr *)&wsAddress, (socklen_t*)&wsAddressLen);
    FD_SET(newclientSocket_fd, &_master); // add to master set
    if (newclientSocket_fd > _fdmax)
    { // keep track of the max
        _fdmax = newclientSocket_fd;
    }
    printf("selectserver: new connection on socket %d\n", newclientSocket_fd); // molaría printear la IP
    _responder(newclientSocket_fd);
}
void ft::SelectServer::_handler(int client_fd)
{
    char 	buffer[BUFFER_SIZE];

    size_t nbytes = recv(client_fd, buffer, sizeof buffer, 0);
	if (nbytes > 0 )
    {
        std::cout << "client(socket " << client_fd << ")  says: " << buffer;
        _echo(client_fd, buffer, nbytes);
        return;
    }
    // got error or connection closed by client
    if (nbytes == 0)
    {
        // connection closed
        printf("selectserver: socket %d hung up\n", client_fd);
    }
    else
    {
        perror("recv");
    }                        
    close(client_fd);           // bye!
    FD_CLR(client_fd, &_master); // remove from master set
}

void ft::SelectServer::_responder(int client_fd)
{
    const size_t len = strlen(WELCOME_MESSAGE);
    send(client_fd, WELCOME_MESSAGE, len, 0);
}

void ft::SelectServer::_echo(int client_fd, char const *str, size_t nbytes)
{
    for (int fd = 0; fd <= _fdmax; fd++)
    {
        if (FD_ISSET(fd, &_master))
        {
            if (fd != client_fd && fd != get_listening_socket().get_socketfd())
                send(fd, str, nbytes, 0);
        }
    }
}

//Public
//Constructor
ft::SelectServer::SelectServer(int domain, int type, int protocol, u_long interface, int port, int backlog) 
	: AServer(domain, type, protocol, interface, port, backlog)
{
	launch();
}

//Function to  launch server
void ft::SelectServer::launch(void)
{
    int listener = get_listening_socket().get_socketfd();
    // add the listener to the master set
    FD_SET(listener, &_master);

    // keep track of the biggest file descriptor
    _fdmax = listener; // so far, it's this one
	while (true)
	{
		_read_fds = _master; // copy it
        if (select(_fdmax+1, &_read_fds, NULL, NULL, NULL) == -1) 
		{
            perror("select");
            exit(4);
        }
		// run through the existing connections looking for data to read
        for (int fd = 0; fd <= _fdmax; fd++)
        {
			if (FD_ISSET(fd, &_read_fds))
            { // we got one!!
                if (fd == get_listening_socket().get_socketfd())
                    _accepter();    // handle new connections
                else
                    _handler(fd);
            }     // END got new incoming connection
        }         // END looping through file descriptors
	}
}
