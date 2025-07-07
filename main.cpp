#include <fstream>
#include <iostream>

#include "CLI/CLIHandler.hpp"
#include "Exceptions/CLIExceptions.hpp"

int main(int argc, char **argv) {
  try {
    CLIHandler cli(argc, argv);

    if (!cli.validOptions()) {
      throw ArgumentsInvalidException();

      return 1;
    }

    return cli.execute();
  } catch (const ArgumentsInvalidException& e) {
    std::cerr << e.what() << std::endl;
  }
}