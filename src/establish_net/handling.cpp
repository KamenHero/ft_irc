#include "../../headers/server.hpp"
#include <string>

void Server::send_message(int sockfd, const std::string& message)
{
    if (send(sockfd, message.c_str(), message.size(), 0) == -1)
        std::cerr << "send() faild" << std::endl;
}

