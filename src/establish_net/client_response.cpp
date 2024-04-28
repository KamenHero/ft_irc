
#include "../../headers/server.hpp"
#include <sys/socket.h>


void Server::commands(request& req, Client& client)
{
    if (req.arg[0] == "join")
    {
        join(client, req);
    }
}