#include <iostream>
#include <cstring>

int main() {
    const int MAX_BUF_SIZE = 1024;
    char buf[MAX_BUF_SIZE];
    std::string command;

    while (true) {
        std::cout << "Enter command (Ctrl+D to send): ";
        while (std::cin.getline(buf, MAX_BUF_SIZE)) {
            // Concatenate the received data to the command
            command += buf;

            // Check for Ctrl+D (EOF)
            if (std::cin.eof()) 
            {
                // Process the complete command
                std::cout << "Received command 1 : " << command << std::endl;
                command.clear(); // Clear the command buffer for next input
            }

            // Check for newline character indicating end of command
            if (buf[strlen(buf) - 1] == '\n') {
                // Process the complete command
                std::cout << "Remceived comand 2 : " << command << std::endl;
                command.clear(); // Clear the command buffer for next input
                break;
            }
        }
        if (std::cin.eof()) {
            break; // Exit loop if Ctrl+D is pressed
        }
    }

    std::cout << "Exiting program." << std::endl;
    return 0;
}
