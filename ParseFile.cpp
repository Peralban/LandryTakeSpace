/*
** EPITECH PROJECT, 2024
** ParseFike.cpp
** File description:
** Abstract for components
*/

#include "ParseFile.hpp"
#include <regex>

std::vector<std::string> nts::ParseFile::fileInVector(void)
{
    std::ifstream file(_fileName);
    if (!file.is_open())
        throw nts::Error("Could not open file");
    std::string line;
    while (std::getline(file, line))
        _fileContent.push_back(line);
    file.close();
    return _fileContent;
}

void nts::ParseFile::checkName(std::vector<std::string> type, std::string name)
{
    for (size_t i = 0; i < type.size(); i++) {
        if (name == type[i])
            return;
        if (type[i] == "end")
            throw nts::Error("Unknow component name '" + name + "'");
    }
}

void nts::ParseFile::saveLinkInVector(std::string line, std::vector<std::string> &names)
{
    while (line[0] == ' ' || line[0] == '\t')
        line = line.substr(1);
    std::string firstName = line.substr(0, line.find(":"));
    checkName(names, firstName);
    line = line.substr(line.find(":") + 1);
    std::string firstPin = line.substr(0, line.find(" "));
    int n = line.find(" ") > line.find("\t") ? line.find("\t") : line.find(" ");
    line = line.substr(n);
    while (line[0] == ' ' || line[0] == '\t')
        line = line.substr(1);
    std::string secondName = line.substr(0, line.find(":"));
    checkName(names, secondName);
    n = line.find(":") > line.find("\t") ? line.find("\t") : line.find(":");
    line = line.substr(line.find(":") + 1, n);
    std::string secondPin = line;
    _links.push_back(std::make_pair(std::make_pair(firstName, firstPin), std::make_pair(secondName, secondPin)));
}

static bool isInput(std::string name)
{
    for (size_t i = 0; i < nts::inputList.size(); i++) {
        if (name == nts::inputList[i])
            return true;
    }
    return false;
}

void nts::ParseFile::saveShipsetInVector(std::string line, std::vector<std::string> &names)
{
    while (line[0] == ' ' || line[0] == '\t')
        line = line.substr(1);
    int n = line.find(" ") > line.find("\t") ? line.find("\t") : line.find(" ");
    std::string componentName = line.substr(0, n);
    line = line.substr(n);
    while (line[0] == ' ' || line[0] == '\t')
        line = line.substr(1);
    checkName(nts::type, componentName);
    n = line.find(" ") > line.find("\t") ? line.find("\t") : line.find(" ");
    std::string name = line.substr(0, n);
    names.pop_back();
    names.push_back(name);
    names.push_back("end");
    std::unique_ptr<nts::IComponent> componentUnique = createComponent(componentName);
    nts::IComponent *component = componentUnique.release();
    if (isInput(componentName)) {
        _nbInput++;
        _inputsVector.push_back(std::make_pair(component, name));
    }
    if (componentName == "output") {
        _nbOutput++;
        _outputsVector.push_back(std::make_pair(component, name));
    }
    _components.push_back(std::make_pair(component, name));
}

static bool isFlag(std::string line, nts::ParseState &state)
{
    for (size_t i = 0; i < nts::flags.size(); i++) {
        if (line == nts::flags[i]) {
            state = static_cast<nts::ParseState>(i);
            return true;
        }
    }
    return false;
}

static void checkLine(std::string line, nts::ParseState state)
{
    std::regex reg;

    if (state == nts::ParseState::CHIPSETS) {
        reg = std::regex("^([ \\t]+)?([a-zA-Z0-9]+)\\s+(\\w+)(\\s+)?(#.*)?$", std::regex_constants::ECMAScript | std::regex_constants::multiline);
    } else if (state == nts::ParseState::LINKS) {
        reg = std::regex("^([ \\t]+)?([a-zA-Z0-9_]+)((\\s+)?:(\\s+)?)([0-9]+)\\s+([a-zA-Z0-9_]+)((\\s+)?:(\\s+)?)([0-9]+)([ \\t]+)?(#.*)?", std::regex_constants::ECMAScript | std::regex_constants::multiline);
    }
    if (!std::regex_match(line, reg)) {
        throw nts::Error("Invalid line");
    }
}


void nts::ParseFile::parseData(void) {
    nts::ParseState state = nts::ParseState::NONE;
    std::vector <std::string> names;
    names.push_back("end");
    for (auto &line: _fileContent) {
        if (line.empty() || line[0] == '#')
            continue;
        if (isFlag(line, state))
            continue;
        checkLine(line, state);
        if (state != nts::ParseState::NONE)
            (this->*SaveInVector[state])(line, names);
    }
    if (_nbInput == 0 && _nbOutput == 0)
        throw nts::Error("No input and output found");
    if ((_nbInput == 0) xor (_nbOutput == 0))
        throw nts::Error(((_nbInput == 0) ? "No input found" : "No output found"));
}

void nts::ParseFile::linkComponents(void)
{
    for (size_t i = 0; i < _components.size(); i++)
        for (size_t j = 0; j < _links.size(); j++)
            if (_components[i].second == _links[j].first.first)
                for (size_t k = 0; k < _components.size(); k++)
                    if (_components[k].second == _links[j].second.first)
                        _components[i].first->setLink(std::stoi(_links[j].first.second), _components[k].first, std::stoi(_links[j].second.second));
}

std::unique_ptr<nts::IComponent> nts::ParseFile::createComponent(const std::string &type)
{
    if (componentFactory.find(type) != componentFactory.end())
        return componentFactory[type]();
    throw nts::Error("Component not found");
}
