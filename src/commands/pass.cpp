#include "../../headers/server.hpp"


int Server::pass(Client& client, request &p)
{
    if (p.arg.empty())
    {
        send_message(client.socket_fd, ":localhost 461 " + client.nickName + " PASS :Not enough parameters\r\n");
        return(p.statu = 1);
    }

    if (client.authenticated)
    {
        send_message(client.socket_fd, ":localhost 462 " + client.nickName + " :You may not reregister\r\n");
        return(p.statu = 1);
    }

    if (this->password != p.arg[0])  // Assuming _srv->get_password() returns the server's password
    {
        send_message(client.socket_fd, ":localhost 464 " + client.nickName + " :Password incorrect\r\n");
        close(client.socket_fd);
        return(p.statu = 1);
    }

    client.authenticated = true;
    send_message(client.socket_fd, ":localhost 001 " + client.nickName + " :Welcome to the IRC Server\r\n");
    return 0;
}
// void Nick(Client& Client, request &p)
// {

//     if (p.arg.empty() || p.arg[0].empty())
//     {
//         send_message(client->get_socket_fd(), ":localhost 431 " + client->nickName + " :No nickname given\r\n");
//         return;
//     }

//     std::string nickname = p.arg[0];

//     // Check for valid characters in the nickname
//     std::string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|";
//     if (nickname.find_first_not_of(validChars) != std::string::npos)
//     {
//         send_message(client->get_socket_fd(), ":localhost 432 " + client->nickName + " :Erroneous nickname\r\n");
//         return;
//     }

//     // if (_srv->get_client(nickname))
//     // {
//     //     send_message(client->get_socket_fd(), ":localhost 433 " + client->nickName + " :Nickname is already in use\r\n");
//     //     return;
//     // }

//     // client->set_nickname(nickname);
//     // client->welcome();

//     // Inform other clients about the nickname change
//     // std::vector<Client*> clients = _srv->get_clients();
//     // for (size_t i = 0; i < clients.size(); ++i)
//     // {
//     //     if (clients[i]->get_socket_fd() != client->get_socket_fd())
//     //     {
//     //         send_message(clients[i]->get_socket_fd(), ":" + client->get_old_nickname() + " NICK " + nickname + "\r\n");
//     //     }
//     // }
// }

// void user(Client& client, request &p)
// {
//     if (p.arg.size() < 4)
//     {
//         send_message(client.socket_fd, ":localhost 461 " + client.nickName + " USER :Not enough parameters\r\n");
//         return;
//     }

//     if (client.authenticated)
//     {
//         send_message(client.socket_fd, ":localhost 462 " + client.nickName + " :You have already registered\r\n");
//         return;
//     }

//     std::string userName = p.arg[0];
//     std::string realName = p.arg[3].substr(p.arg[3][0] == ':' ? 1 : 0);

//         // Check for valid username
//         if (userName.empty())
//         {
//             send_message(client.socket_fd, ":localhost 461 " + client.nickName + " USER :Not enough parameters\r\n");
//             return;
//         }

//         // Check for valid realname
//         if (realName.empty())
//         {
//             send_message(client.socket_fd, ":localhost 461 " + client.nickName + " USER :Not enough parameters\r\n");
//             return;
//         }

//         // Set client's username and realname
//         client.userName = userName;
//         client.realName = realName;

//         // Check if the client already has a nickName set, if not, set the username as the nickName
//         if (client.nickName.empty())
//         {
//             client.nickName = userName;
//         }

//         // Mark the client as authenticated
//         client.authenticated = true;

//         // Send welcome message
//         send_message(client.socket_fd, ":localhost 001 " + client.nickName + " :Welcome to the IRC Server\r\n");
// }
