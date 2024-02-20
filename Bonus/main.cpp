/*
** EPITECH PROJECT, 2024
** Main.cpp
** File description:
** main.cpp
*/

#include "NanotekSpice.hpp"
#include "SFMLModule.hpp"

static void error_case(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Error: invalid number of arguments" << std::endl;
        exit(84);
    }
    if (std::string(av[1]) == "-h") {
        std::cout << "USAGE" << std::endl;
        std::cout << "    ./nanotekspice file.nts" << std::endl;
        std::cout << "DESCRIPTION" << std::endl;
        std::cout << "    file    file describing the circuit" << std::endl;
        exit(0);
    }
    if (std::string(av[1] + strlen(av[1]) - 4) != ".nts") {
        std::cerr << "Error: invalid file extension" << std::endl;
        exit(84);
    }
}

int main(int ac, char **av)
{
    error_case(ac, av);
    nts::ParseFile parseFile;
    try {
        parseFile.setFileName(av[1]);
        parseFile.fileInVector();
        parseFile.parseData();
        parseFile.linkComponents();
    } catch (nts::Error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    nts::NanotekSpice nanotekSpice(parseFile.getInputsVector(), parseFile.getOutputsVector());
    nts::SFMLModule sfmlModule(parseFile.getComponents(), parseFile.getOutputsVector(), parseFile.getInputsVector());
    nanotekSpice.execShell(sfmlModule);
    return 0;
}