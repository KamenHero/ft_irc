/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentication_cmd.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchaguer <hchaguer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:47:59 by hchaguer          #+#    #+#             */
/*   Updated: 2024/04/27 20:40:32 by hchaguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/server.hpp"
#include <cstddef>


int Server::pass(Client& client, request &p)
{
    if (p.arg.size() != 1)
    {
        send_message(client.socket_fd, ERR_NEEDMOREPARAMS(p.cmd));
    }
    else if (p.arg[0] != this->password)
    {
        send_message(client.socket_fd, ERR_PASSWDMISMATCH());
    }
    else
    {
        std::cout << "hello from pass cmd " <<   std::endl;
        send_message(client.socket_fd, ":localhost 462 " + client.nickName + " :You may not reregister\r\n");
        
    }
    client.authenticated = true;
    return 0;
}


void Server::Nick(Client& cli, request &p)
{
    std::string nick = p.cmd;
    bool etat = true;
    std::map<int,Client>::iterator it;

    for (it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.nickName == p.arg[0])
        {
            etat = false;
            send_message(cli.socket_fd, ERR_NICKNAMEINUSE(p.arg[0]));
        }
    }
    if (etat == true)
    {
        cli.nickName = p.arg[0];
        clients[cli.socket_fd] = cli;
        send_message(cli.socket_fd, ":localhost 462 " + cli.nickName + " :You may not reregister\r\n");
    }
    
}

void Server::user(Client& client, request &p)
{
    (void)client;
    std::string user = p.cmd;
    
    if (p.arg.size() == 4)
    {
        client.userName = p.arg[0];
        client.hostName = p.arg[1];
        client.serverName = p.arg[2];
        client.realName = p.arg[3];
    }

    // user hostname realname
        // std::cout << "this nick : " << user << std::endl;
    // for (size_t i = 0; i < p.arg.size(); i++)
    // {
    //     std::cout << "arg : " << p.arg.at(i) << std::endl;
    // }
}
