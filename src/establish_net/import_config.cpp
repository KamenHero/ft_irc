/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:20:28 by oryadi            #+#    #+#             */
/*   Updated: 2024/04/17 23:00:32 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.hpp>

int	importPort(std::string importedPort) {
	for (size_t i = 0; i < importedPort.size(); i++)
		if (!isdigit(importedPort[i])) return -1;

	int parsedPort = std::atoi(importedPort.data());

	if (parsedPort > USHRT_MAX) return -1;

	return parsedPort;
}

void	Server::importConfig(std::string importedPort, std::string importedPassword)
{
	port = importPort(importedPort);

	if (port < 0) throw std::invalid_argument(importedPort + " is invalid PORT.");

	if (!importedPassword.size()) throw std::invalid_argument("No PASSWORD was given.");

	password = importedPassword;
}
