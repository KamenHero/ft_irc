#include "../../headers/server.hpp"
#include <iostream>
#include <algorithm>

std::map<std::string, Channel *> channels;

void Server::createChannel(std::string &channel, Client &t)
{
    channels[channel] = new Channel(channel, &t);
    // channels[channel]->update_onlinemembers();
    channels[channel]->admin = &t;
    // clients[fd] = t;// useless
    t._channel.push_back(channel);

    // std::map<std::string, Channel *>::iterator it = channels.begin();
    // while (it != channels.end())
    // {
    //     std::cout << it->first << "<>" << it->second->_name << ">>\n";
    //     it++;
    // }
}

void Server::joinChannel(std::string &channel, Client &t)
{
    channels[channel]->_members.push_back(&t);
    t._channel.push_back(channel);
    // channels[channel]->setop(client[fd]);
}


std::string Server::join(Client &client, request &p)
{

    if (p.arg.empty() || p.arg.size() < 1)
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " join :Not enough parameters\r\n");
        return "";
    }
    int i = 0;
    while (i < (int)p.arg.size())
    {
        std::string channel = p.arg[i];
        if (channel[0] != '#')
        {
            send_message(client.socket_fd, ":localhost 461 " + client.nickName + " join : Invalid channel name\r\n");
            continue;
        }

        if (channel.length() > 20)
        {
            send_message(client.socket_fd, ":localhost 405 " + client.nickName + " join : Channel name too long\r\n");
            continue;
        }

        if (channels.count(p.arg[i]))
        {
            std::cout << "chanee sla d as \n";
            if ((std::find(client._channel.begin(), client._channel.end(), p.arg[i])) != client._channel.end())
            {
                send_message(client.socket_fd, ":localhost 461 " + client.nickName + " join : You are already in " + channel + "\r\n");
                ++i;
                continue;
            }
            else
            {
                std::cout << "channel kaina walkin machi member !\n";
                send_message(client.socket_fd, ":localhost 461 " + client.nickName + " join : You are now a memeber in " + channel + "\r\n");
                joinChannel(p.arg[i], client);
                ++i;
                continue;
            }
        }

        std::map<std::string, Channel *>::iterator it = channels.find(p.arg[i]);
        if (it == channels.end())
        {
            createChannel(p.arg[i], client);
            send_message(client.socket_fd, ":localhost 461 " + client.nickName + " join : the channel is created " + channel + "\r\n");
        }
        i++;
    }
    return "";
}

// void Server::writter()
// {
//     std::map<std::string, Channel *>::iterator it = channels.begin();
//     while (it != channels.end())
//     {
//         std::cout << it->first << "<>" << it->second->_name << ">>\n";
//         it++;
//     }
// }
std::string Server::kick(Client &client, request &p)
{
    if (p.arg.size() < 2 || p.arg.empty())
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " kick : Not enough arguments!\r\n");
    }
    else if (std::find(client._channel.begin(), client._channel.end(), p.arg[0]) == client._channel.end()) {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " kick : You are not a member in this channel\r\n");
    }
    else if (client.socket_fd != channels[p.arg[0]]->admin->socket_fd) {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " kick : You are not the admin of the channel\r\n");
    }
    else {

        for (size_t i = 1; i < p.arg.size();i++) {
            //ta loop 3la ga3 users
            if (client.nickName == p.arg[i]) {
                //lakan hadak clinet howa li m3ayt 3la rasso
                send_message(client.socket_fd, ":localhost 461 " + client.nickName + " kick : You can not kick yourself\r\n");
                continue;
            }
            std::vector<Client *>::iterator it = channels[p.arg[0]]->_members.begin();
            //tan9alb 3la kila user fi channel
            for (; it != channels[p.arg[0]]->_members.end(); ++it) {
                if (p.arg[i] == (*it)->nickName)
                {
                    //remove client mn channael
                    (*it)->_channel.erase(std::find((*it)->_channel.begin(), (*it)->_channel.end(), p.arg[0]));
                    send_message((*it)->socket_fd, ":localhost 461 " + p.arg[i] + " You have been kicked !");
                    // remove client mn member
                    channels[p.arg[0]]->_members.erase(it);
                    break;
                }
            }
        }
    }
    return ("");
}

std::string Server::invite(Client &client, request &p)
{

    if (p.arg.size() < 2 || p.arg.empty())
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " invite : Not enough arguments!\r\n");
    }
    else if (std::find(client._channel.begin(), client._channel.end(), p.arg[1]) == client._channel.end())
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " invite : You are not a member in this channel\r\n");
    }
    else if (client.socket_fd != channels[p.arg[1]]->admin->socket_fd)
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " invite : You are not the admin of the channel\r\n");
    }
    else
    {
        if (client.nickName == p.arg[0])
        {
            send_message(client.socket_fd, ":localhost 461 " + client.nickName + " invite : You can not invite yourself\r\n");
        }
        std::vector<Client *>::iterator it;
        std::map<int , Client>::iterator it_1;
        //tan loopi 3la map o victor tan9alb 3la nickname if client
        for (it_1 = clients.begin(); it_1 != clients.end(); ++it_1)
        {
            for (it = channels[p.arg[1]]->_members.begin(); it < channels[p.arg[1]]->_members.end(); ++it)
            {
                if ((*it_1).second.nickName == (*it)->nickName)
                {
                    (*it)->_channel.push_back(*(std::find((*it)->_channel.begin(), (*it)->_channel.end(), p.arg[1])));
                    send_message((*it)->socket_fd, " :localhost 461 " + p.arg[0] + " invite you in ckannel  !");
                    channels[p.arg[1]]->_members.push_back(*it);
                    break;
                }
            }
        }
    }
    return ("");
}
