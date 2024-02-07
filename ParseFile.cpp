/*
** EPITECH PROJECT, 2024
** ParseFike.cpp
** File description:
** Abstract for components
*/

#include "ParseFile.hpp"
#include "IComponent.hpp"
#include <fstream>
#include <vector>

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
}

static std::vector<std::string> fileInVector(std::string fileName)
{
    std::ifstream file(fileName);
    std::vector<std::string> fileContent;
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << fileName << std::endl;
        exit(84);
    }
    std::string line;
    while (std::getline(file, line))
        fileContent.push_back(line);
    file.close();
    return fileContent;
}

static std::string CreateComponent(std::string componentName)
{
    return componentName;
}

static void ParseData(std::vector<std::string> fileContent)
{
    std::vector<std::pair</*nts::IComponent **/std::string, std::string>> components;
    nts::ParseState state = nts::ParseState::NONE;
    for (auto &line : fileContent) {
        if (line.empty())
            continue;
        if (line.find("#") != std::string::npos)
            continue;
        if (line.find(".chipsets:") != std::string::npos) {
            state = nts::ParseState::CHIPSETS;
            continue;
        }
        if (line.find(".links:") != std::string::npos)
            state = nts::ParseState::LINKS;
        if (state != nts::ParseState::CHIPSETS)
            continue;
        std::string componentName = line.substr(0, line.find(" "));
        std::string name = line.substr(line.find(" ") + 1);
        components.push_back(std::make_pair(CreateComponent(componentName), name));
    }
    for (size_t i = 0; i < components.size(); i++)
        std::cout << components[i].first << " " << components[i].second << std::endl;
}

void parseFile(int ac, char **av)
{
    error_case(ac, av);
    std::vector<std::string> fileContent = fileInVector(av[1]);
    for (auto &line : fileContent) {
        std::cout << line << std::endl;
    }
    ParseData(fileContent);
}