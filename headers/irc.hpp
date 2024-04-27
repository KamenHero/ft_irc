#pragma once

#define C_ESTABLISHING_CONNECTION 1
#define C_READ_REQUEST 2
#define C_RESPONSE_TO_REQUEST 3
#define C_CLOSE_CONNECTION 4


#define RPL_WELCOME(nickname)   (nickname + " : Welcome to the localhost Network, \r\n")
#define RPL_CREATED(nickname)   (nickname + " :Your host is <servername>, running version <version>\r\n")
#define RPL_MYINFO(nickname)    (nickname + " <client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]\r\n")
#define ERR_PASSWDMISMATCH()    (" ERROR (464) :Password incorrect\r\n")
#define ERR_NEEDMOREPARAMS(cmd) (cmd + " ERROR (461) :Not enough parameters\r\n")
#define ERR_NICKNAMEINUSE(nick) (nick + " Error (443) :Nickname is already in use\r\n")
#define ERR_NONICKNAMEGIVEN() (" ERROR (431) :No nickname given\r\n")