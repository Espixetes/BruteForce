#include "BruteForceEngine.hpp"


int main(size_t argc, char* argv[])
{
    std::vector<std::string> commandLineArgument;
    for (int i = 0; i < argc; ++i) {commandLineArgument.push_back(argv[i]);}
    
    if (commandLineArgument.size() < 1)
    {
        std::cerr << "Invalid argument" << std::endl;
        Sleep(3000);
        return 0;
    }
    bruteforce::Bruteforce h;
    h.Start(commandLineArgument[1]);
}
