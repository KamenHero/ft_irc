#include "irc.hpp"

struct Client {
	int	socket_fd;
	int step;

	Client() {
		this->step = C_ESTABLISHING_CONNECTION;
	}
};