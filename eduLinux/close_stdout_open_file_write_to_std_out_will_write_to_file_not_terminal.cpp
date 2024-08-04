#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <fcntl.h>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    int fd  = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    close(1);
    dup2(fd, 1);

    std::cout<< "hwokhdkwejhd";
    return result;
}

int main() {
    std::string command = "ls -la"; // Replace with your command
    std::string output = exec(command.c_str());
    return 0;
}
