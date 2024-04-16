#pragma once

#include <iostream>
#include <vector>
#include "client.hpp"

class Server {
	private:
		int			port;
		std::string	password;
		std::vector<Client>	clients;

	public:
		void	importConfig(char **argv);
		void	hostServer();
		void	awaitingTraffic();
};