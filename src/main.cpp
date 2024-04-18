/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:29:06 by oryadi            #+#    #+#             */
/*   Updated: 2024/04/17 22:58:41 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "You must include PORT and PASSWORD to proceed." << std::endl;
		
		return (1);
	}

	Server server;

	try {
		server.importConfig(argv[1], argv[2]);

		server.hostServer();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		
		return (1);
	}

	std::cout << "success..." << std::endl;
	
	return (0);
}