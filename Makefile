COMPILER = c++

CPPFLAGS = -I headers/ -Wall -Werror -Wextra -std=c++98

SRCS = src/main.cpp src/establish_net/import_config.cpp \
		src/establish_net/host_server.cpp \
		src/establish_net/client_response.cpp \
		src/establish_net/awaiting_traffic.cpp

HEADERS = headers/server.hpp headers/client.hpp

NAME = ircserv

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(COMPILER) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re