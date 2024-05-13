// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Authentification.cpp                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hchaguer <hchaguer@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/25 16:55:12 by hchaguer          #+#    #+#             */
// /*   Updated: 2024/04/26 17:32:29 by hchaguer         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// /*  step 1 : connecting to the server
//     step 2 : authentification the user
//     step 3 : join the channel
// */

#include "../../headers/server.hpp"
#include <cstddef>
#include <linux/limits.h>

int Server::searchForDestination(request& req)
{
    int client_dest = 0;
    std::map<int, Client>::iterator it;
    std::map<int, Client>::iterator it1;

    for (it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.nickName == req.arg[0])
            client_dest = it->first;
        return (client_dest);
    }
    return (0);
}

void Server::sendMessageToClient(request& req, Client& cli, int client_dest)
{
    std::string msg;
    std::string str;

    if (searchForDestination(req) == 0)
        send_message(cli.socket_fd, ERR_NOSUCHNICK(req.arg[0]));
    else
    {
        for (size_t i = 1; i < req.arg.size(); i++)
            str += req.arg[i] + " ";

        msg = ":" + cli.nickName + " PRIVMSG " + req.arg[0] + " :" + str + "\r\n";
        send(client_dest, msg.c_str(), msg.size(), 0);
    }
}

int Server::getAuthentified(Client& cli, request& req)
{
    std::cout << "cmd : "<< req.cmd <<std::endl; 
    if (req.cmd == "QUIT" || req.cmd == "quit")
	{
		send_message(cli.socket_fd, "QUIT :Leaving the chat\r\n");
	}
    else if (req.cmd == "PRIVMSG")
    {
        if (req.arg[0][0] == '#')
        {
            sendMSGToChannel(cli, req);
        }
        else
        {
            int client_dest;

            client_dest = searchForDestination(req);
            sendMessageToClient(req, cli, client_dest);
        }
    }
    else if (req.cmd == "CAP")
    {
        send_message(cli.socket_fd, "*\r\n");
    }
    else if (req.cmd == "WHOIS")
    {
        send_message(cli.socket_fd, RPL_ENDOFWHOIS(cli.nickName));
    }
    else if (req.cmd == "PING")
    {
        send_message(cli.socket_fd, "PONG :irc.server.com\r\n");
    }
    else if (req.cmd == "MODE")
    {
        Mode(cli,req);
    }
    else if (req.cmd == "join" || req.cmd == "JOIN")
    {
        join(cli, req);
    }
    else if (req.cmd == "INVITE")
    {
        invite(cli, req);
    }
    else if (req.cmd == "KICK")
    {
        kick(cli, req);
    }
    else if (req.cmd == "TOPIC")
    {
        Topic(cli, req);
    }
    else if ((req.cmd == "PASS" || req.cmd == "pass") && cli.count == 0)
    {
        cli.count = 1;
        pass(cli, req);
    }
    else if ((req.cmd == "NICK" || req.cmd == "nick") && cli.count == 1)
    {
        cli.count = 2;
        Nick(cli, req);
    }
    else if ((req.cmd == "USER" || req.cmd == "user") && cli.count == 2)
    {
        cli.count = 3;
        user(cli, req);
    }
	else if (req.cmd == "KAMEN" || req.cmd == "kamen")
	{
		bot(cli, req);
	}
    else
        std::cout << req.cmd << " not a command" << std::endl;

    return (cli.count);
}
