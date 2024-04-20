/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:34:44 by oryadi            #+#    #+#             */
/*   Updated: 2024/04/19 16:01:57 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.hpp>

void	Server::hostServer()
{
	
	sockaddr_in address;
	
	address.sin_family = AF_INET;

	address.sin_port = htons(port);
	
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Cannot create a socket.");

	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Cannot make socket NON_BLOCK.");

	if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)
		throw std::runtime_error("Cannot bind the socket.");

	if (listen(server_fd, SOMAXCONN) < 0)
		throw std::runtime_error("Cannot listen to socket.");

	std::cout << "irc is listening at 0.0.0.0:" << port << std::endl;
}
