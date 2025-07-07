#include <fstream>
#include <iostream>

#include "CLI/CLIHandler.hpp"

int main(int argc, char** argv) {
    CLIHandler cli(argc, argv);

    if (!cli.validOptions()) {
        std::cerr << "Argumentos inválidos!\n"
                 << "O comando deve ser dado na seguinte forma:\n"
                 << "freq [tipo] [nome_arquivo.txt]\n"
                 << "As opções disponíveis são: \n"
                 << "dictionary_avl\n"
                 << "dictionary_redblack\n"
                 << "dictionary_chained\n"
                 << "dictionary_open" << std::endl;
        
        return 1;
    }

    return cli.execute();
}