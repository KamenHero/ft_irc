#pragma once

#include <iostream>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <stdexcept>
#include <limits.h>
#include <netinet/in.h>
#include "client.hpp"


class Server {
	private:
		int			port;
		std::string	password;
		int server_fd;
		std::map<int, Client>	clients;


	public:
		void	importConfig(std::string importedPort, std::string importedPassword);
		void	hostServer();
		void	awaitingTraffic();
		void	clientResponse();

		void	handleReadRequest(Client &client);
};