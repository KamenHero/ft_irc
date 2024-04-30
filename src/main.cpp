/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:29:06 by oryadi            #+#    #+#             */
/*   Updated: 2024/05/01 00:21:41 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../headers/server.hpp"

extern std::map<std::string, Channel *> channels;

int main(int argc, char **argv) {
	if (argc != 3) {

		std::cerr << "You must include PORT and PASSWORD to proceed." << std::endl;

		return (1);
	}

	Server server;

	try {
		server.importConfig(argv[1], argv[2]);
		server.hostServer();
		server.awaitingTraffic();

	} catch (const std::exception &e) {
		std::cerr << "Error : " << e.what() << std::endl;

		return (1);
	}

	std::cout << "success..." << std::endl;

	return (0);
}
