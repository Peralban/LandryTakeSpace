/*
** EPITECH PROJECT, 2024
** ParseFile.hpp
** File description:
** Abstract for components
*/

#pragma once

#include "CreateComponent.hpp"
#include <fstream>
#include <cstring>

namespace nts
{
    static std::vector<std::string> type = {
        "input",
        "output",
        "clock",
        "true",
        "false",
        "and",
        "or",
        "xor",
        "not",
        "4001",
        "4008",
        "4011",
        "4013",
        "4017",
        "4030",
        "4040",
        "4069",
        "4071",
        "4081",
        "4094",
        "4514",
        "4801",
        "end"
    };

    static std::vector<std::string> inputList = {
        "input",
        "output",
        "clock",
        "true",
        "false",
    };

    enum ParseState {
        CHIPSETS,
        LINKS,
        NONE
    };

    static std::vector <std::string> flags = {
        ".chipsets:",
        ".links:"
    };

    typedef std::vector<std::pair<nts::IComponent *, std::string>> componentAndNameInVector;
    typedef std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>>> LinkInVector;
    typedef std::vector<std::pair<nts::IComponent *, std::string>> allInputAndNameInVector;
    typedef std::vector<std::pair<nts::IComponent *, std::string>> allOutputAndNameInVector;

    class ParseFile
    {
    public:
        ParseFile(void) : _nbInput(0), _nbOutput(0) {}
        ~ParseFile() = default;
        void error_case(int ac, char **av);
        std::vector<std::string> fileInVector(void);
        void linkComponents(void);
        void parseData(void);

        void setFileName(std::string fileName) { _fileName = fileName; }

        componentAndNameInVector getComponents() { return _components; }
        LinkInVector getLinks() { return _links; }
        std::vector<std::string> getFileContent() { return _fileContent; }
        allInputAndNameInVector getInputsVector() { return _inputsVector; }
        allOutputAndNameInVector getOutputsVector() { return _outputsVector; }
        void setCircuit();
        IComponent *getCircuit() { return circuit; }
        unsigned int getNbInput() { return _nbInput; }
        unsigned int getNbOutput() { return _nbOutput; }


        void saveShipsetInVector(std::string line, std::vector<std::string> &names);
        void saveLinkInVector(std::string line, std::vector<std::string> &names);
        void (ParseFile::*SaveInVector[2])(std::string line, std::vector<std::string> &names) = {
            &nts::ParseFile::saveShipsetInVector,
            &nts::ParseFile::saveLinkInVector
        };

    private:
        void checkName(std::vector<std::string> type, std::string name);

        std::string _fileName;
        std::vector<std::string> _fileContent;
        componentAndNameInVector _components;
        LinkInVector _links;
        allInputAndNameInVector _inputsVector;
        allOutputAndNameInVector _outputsVector;
        unsigned int _nbInput;
        unsigned int _nbOutput;
        IComponent *circuit;
    };

}  // namespace nts
