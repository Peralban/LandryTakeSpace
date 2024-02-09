/*
** EPITECH PROJECT, 2024
** ParseFike.cpp
** File description:
** Abstract for components
*/

#include "ParseFile.hpp"
#include <fstream>

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
    if (std::string(av[1]).find(".nts") == std::string::npos) {
        std::cerr << "Error: invalid file extension" << std::endl;
        exit(84);
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

static bool checkName(std::vector<std::string> type, std::string name)
{
    for (size_t i = 0; i < type.size(); i++) {
        if (name == type[i])
            return true;
        if (type[i] == "end") {
            std::cerr << "Error: invalid component name" << std::endl;
            return false;
        }
    }
    return true;
}

static std::pair<std::vector<std::pair</*nts::IComponent **/std::string, std::string>>, std::vector<std::pair<std::pair</*First Name*/std::string, /*First PIN*/std::string>, std::pair</*Second Name*/std::string, /*Second PIN*/std::string>>>> ParseData(std::vector<std::string> fileContent)
{
    std::vector<std::pair</*nts::IComponent **/std::string, std::string>> components;
    std::vector<std::pair<std::pair</*First Name*/std::string, /*First PIN*/std::string>, std::pair</*Second Name*/std::string, /*Second PIN*/std::string>>> links;
    nts::ParseState state = nts::ParseState::NONE;
    std::vector<std::string> names;
    names.push_back("end");
    for (auto &line : fileContent) {
        if (line.empty() || line[0] == '#')
            continue;
        if (line.find(".chipsets:") != std::string::npos) {
            state = nts::ParseState::CHIPSETS;
            continue;
        }
        if (line.find(".links:") != std::string::npos) {
            state = nts::ParseState::LINKS;
            continue;
        }
        if (state == nts::ParseState::CHIPSETS) {
            std::string componentName = line.substr(0, line.find(" "));
            if (!checkName(nts::type, componentName))
                exit(84);
            std::string name = line.substr(line.find(" ") + 1);
            names.pop_back();
            names.push_back(name);
            names.push_back("end");
            components.push_back(std::make_pair(CreateComponent(componentName), name));
        }
        if (state == nts::ParseState::LINKS) {
            std::string firstName = line.substr(0, line.find(":"));
            if (!checkName(names, firstName))
                exit(84);
            line = line.substr(line.find(":") + 1);
            std::string firstPin = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ") + 1);
            std::string secondName = line.substr(0, line.find(":"));
            if (!checkName(names, secondName))
                exit(84);
            line = line.substr(line.find(":") + 1);
            std::string secondPin = line;
            links.push_back(std::make_pair(std::make_pair(firstName, firstPin), std::make_pair(secondName, secondPin)));
        }
    }
    return std::make_pair(components, links);
}

//static std::vector<std::pair</*nts::IComponent **/std::string, std::string>> LinkComponents(std::vector<std::pair</*nts::IComponent **/std::string, std::string>> components, std::vector<std::pair<std::pair</*First Name*/std::string, /*First PIN*/std::string>, std::pair</*Second Name*/std::string, /*Second PIN*/std::string>>> links)
//{
    //std::vector<std::pair</*nts::IComponent **/std::string, std::string>> LinkedComponents;
    //for (size_t i = 0; i < components.size(); i++) {
    //    for (size_t j = 0; j < links.size(); j++) {
    //        if (components[i].second == links[j].first.first) {
    //            LinkedComponents.push_back(std::make_pair(components[i].first, links[j].first.second));
    //        }
    //        if (components[i].second == links[j].second.first) {
    //            LinkedComponents.push_back(std::make_pair(components[i].first, links[j].second.second));
    //        }
    //    }
    //}
    //return LinkedComponents;
//}

void parseFile(int ac, char **av)
{
    error_case(ac, av);
    std::vector<std::string> fileContent = fileInVector(av[1]);
    std::pair<std::vector<std::pair</*nts::IComponent **/std::string, std::string>>, std::vector<std::pair<std::pair</*First Name*/std::string, /*First PIN*/std::string>, std::pair</*Second Name*/std::string, /*Second PIN*/std::string>>>> ParsedFile = ParseData(fileContent);
    std::vector<std::pair</*nts::IComponent **/std::string, std::string>> components = ParsedFile.first;
    std::vector<std::pair<std::pair</*First Name*/std::string, /*First PIN*/std::string>, std::pair</*Second Name*/std::string, /*Second PIN*/std::string>>> links = ParsedFile.second;
    //for (size_t i = 0; i < components.size(); i++) {
    //    std::cout << components[i].first << " " << components[i].second << std::endl;
    //}
    //for (size_t i = 0; i < links.size(); i++) {
    //    std::cout << links[i].first.first << " " << links[i].first.second << " " << links[i].second.first << " " << links[i].second.second << std::endl;
    //}
    //std::vector<std::pair</*nts::IComponent **/std::string, std::string>> LinkedComponents = LinkComponents(components, links);
}