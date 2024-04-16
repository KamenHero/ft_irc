#include <iostream>

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << "You must include PORT and PASSWORD to proceed." << std::endl;
		return (1);
	}
	(void)argv;
	std::cout << "success..." << std::endl;
	return (0);
}