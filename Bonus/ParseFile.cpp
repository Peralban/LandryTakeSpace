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
    std::string firstName = line.substr(0, line.find(":"));
    checkName(names, firstName);
    line = line.substr(line.find(":") + 1);
    std::string firstPin = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ") + 1);
    std::string secondName = line.substr(0, line.find(":"));
    checkName(names, secondName);
    line = line.substr(line.find(":") + 1, line.find(" "));
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
    std::string componentName = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ") + 1);
    checkName(nts::type, componentName);
    std::string name = line.substr(0, line.find(" "));
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
        reg = std::regex("^[\\w]+ [\\w]+( #.*)?$");
    } else if (state == nts::ParseState::LINKS) {
        reg = std::regex("^[\\w]+:[\\d]+ [\\w]+:[\\d]+( #.*)?$");
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
    for (size_t i = 0; i < _components.size(); i++) {
        for (size_t j = 0; j < _links.size(); j++) {
            if (_components[i].second == _links[j].first.first) {
                for (size_t k = 0; k < _components.size(); k++) {
                    if (_components[k].second == _links[j].second.first) {
                        std::cout << _components[i].second << " " << _links[j].first.second << " " << _components[k].second << " " << _links[j].second.second << std::endl;
                        _components[i].first->setLink(std::stoi(_links[j].first.second), _components[k].first, std::stoi(_links[j].second.second));
                    }
                }
            }
        }
    }
}

std::unique_ptr<nts::IComponent> nts::ParseFile::createComponent(const std::string &type)
{
    if (type == "and")
        return std::unique_ptr<nts::IComponent>(new nts::AndGate());
    else if (type == "or")
        return std::unique_ptr<nts::IComponent>(new nts::OrGate());
    else if (type == "xor")
        return std::unique_ptr<nts::IComponent>(new nts::XorGate());
    else if (type == "not")
        return std::unique_ptr<nts::IComponent>(new nts::NotGate());
    else if (type == "true")
        return std::unique_ptr<nts::IComponent>(new nts::TrueComponent());
    else if (type == "false")
        return std::unique_ptr<nts::IComponent>(new nts::FalseComponent());
    else if (type == "4081")
        return std::unique_ptr<nts::IComponent>(new nts::Component4081());
    else if (type == "4071")
        return std::unique_ptr<nts::IComponent>(new nts::Component4071());
    else if (type == "4069")
        return std::unique_ptr<nts::IComponent>(new nts::Component4069());
    else if (type == "4030")
        return std::unique_ptr<nts::IComponent>(new nts::Component4030());
    else if (type == "4011")
        return std::unique_ptr<nts::IComponent>(new nts::Component4011());
    else if (type == "4001")
        return std::unique_ptr<nts::IComponent>(new nts::Component4001());
    else if (type == "input")
        return std::unique_ptr<nts::IComponent>(new nts::InputComponent());
    else if (type == "output")
        return std::unique_ptr<nts::IComponent>(new nts::OutputComponent());
    else if (type == "clock")
        return std::unique_ptr<nts::IComponent>(new nts::ClockComponent());
    else if (type == "4008")
        return std::unique_ptr<nts::IComponent>(new nts::Component4008());
    else if (type == "4013")
        return std::unique_ptr<nts::IComponent>(new nts::Component4013());
    throw nts::Error("Component not found");
}
