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


int Server::getAuthentified(Client& cli, request& req)
{   
    if (req.cmd == "PRIVMSG")
    {
        int client_dest;
        std::string msg;
        // send message to a client :
        // 1 serching for nickname
        std::map<int, Client>::iterator it;

        for (it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->second.nickName == req.arg[0])
            {
                // 2 get the nickname and take his fd_socket
                client_dest = it->first;
            }
        }
        // for (size_t i = 1; i < req.arg.size(); i++)
        // {
            // std::cout << "arg : " << req.arg[i] << std::endl;
            // msg = ":" + cli.nickName + " PRIVMSG " + req.arg[0]  + " :" + req.arg[i] + "\r\n";
            // send(client_dest, msg.c_str(), msg.size(), 0);
        // }
        // 3 put the fd_socket on send function

    }
    else if (req.cmd == "PASS" || req.cmd == "pass")
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
    else
        std::cout << req.cmd << " not a command" << std::endl;

    return (cli.count);
}