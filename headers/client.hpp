#include "irc.hpp"
#include <string>
#define BUFFER_SIZE 1024

struct Client {
	
	int	socket_fd;
	int step;

	/* authentification of client */
	std::string pass;
	std::string nick;
	std::string user;
	std::string realName;
	std::string buffer;

	Client() {

		this->step = C_ESTABLISHING_CONNECTION;
	}
};