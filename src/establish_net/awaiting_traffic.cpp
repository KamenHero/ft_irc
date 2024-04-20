#include <server.hpp>

void	acceptIncomingConnection(std::map<int, Client> &clients, fd_set &totalfds, int server_fd)
{
	sockaddr client_s;

	socklen_t client_length;

	int newfd = accept(server_fd, &client_s, &client_length);

	if (newfd < 0) throw std::runtime_error("Systemcall `accept` failed.");

	FD_SET(newfd, &totalfds);

	Client client;

	client.socket_fd = newfd;

	clients.insert(std::make_pair(newfd, client));
}

void	Server::awaitingTraffic()
{
	fd_set totalfds;
	fd_set readfds;
	fd_set writefds;

	FD_ZERO(&totalfds);

	FD_SET(server_fd, &totalfds);

	while(true) {
		readfds = writefds = totalfds;

		int	res = select(FD_SETSIZE, &readfds, &writefds, NULL, NULL);

		if (res < 0) throw std::runtime_error("Systemcall `select()` failed.");

		if (!res) continue ;

		if (FD_ISSET(server_fd, &readfds)) acceptIncomingConnection(this->clients, totalfds, server_fd);

		for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (FD_ISSET(it->first, &readfds)) handleReadRequest(it->second);
			else if (FD_ISSET(it->first, &writefds)) {}
		}
	}
}
