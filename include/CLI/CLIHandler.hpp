#ifndef CLI_HANDLER_HPP
#define CLI_HANDLER_HPP

#include "CLI/CLIOptions.hpp"

class CLIHandler {
    CLIOptions options;
    int quantityArguments;
public:
    CLIHandler(int argc, char** argv);

    bool validOptions();
    int execute();
};

#endif