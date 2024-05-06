#include "../../headers/server.hpp"
#include <string>

void Server::send_message(int sockfd, const std::string& message)
{
    if (send(sockfd, message.c_str(), message.size(), 0) == -1)
        std::cerr << "send() faild" << std::endl;
}
void Server::send_all_member(int sockfd, const std::string &message)
{
    std::map<int, Client>::iterator it = clients.begin();
    for (; it != clients.end();it++)
    {
        if (it->second.socket_fd != sockfd)
        {
            if (send(it->second.socket_fd, message.c_str(), message.size(), 0) == -1)
                std::cerr << "send() faild" << std::endl;
        }
    }
}
void Server::send_just_member(const std::string &message, std::string chanle)
{
    std::vector<Client*> ::iterator it = channels[chanle]->_members.begin();
    for (; it != channels[chanle]->_members.end(); it++)
    {
        if (send((*it)->socket_fd, message.c_str(), message.size(), 0) == -1)
            std::cerr << "send() faild" << std::endl;
    }
}
