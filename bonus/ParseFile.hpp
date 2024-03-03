/*
** EPITECH PROJECT, 2024
** ParseFile.hpp
** File description:
** Abstract for components
*/

#pragma once

#include "BasicGates.hpp"
#include "SpecialComponents.hpp"
#include "GatesComponents.hpp"
#include "AdvancedComponents.hpp"
#include <memory>
#include <fstream>
#include <map>
#include <cstring>
#include <functional>

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
        "4512",
        "4514",
        "4801",
        "2716",
        "logger",
        "end"
    };

    static std::vector<std::string> inputList = {
        "input",
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

    static std::map<std::string, std::function<std::unique_ptr<nts::IComponent> ()>> componentFactory = {
            {"input", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::InputComponent>(); }},
            {"output", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::OutputComponent>(); }},
            {"clock", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::ClockComponent>(); }},
            {"true", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::TrueComponent>(); }},
            {"false", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::FalseComponent>(); }},
            {"and", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::AndGate>(); }},
            {"or", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::OrGate>(); }},
            {"xor", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::XorGate>(); }},
            {"not", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::NotGate>(); }},
            {"4001", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4001>(); }},
            {"4008", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4008>(); }},
            {"4011", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4011>(); }},
            {"4013", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4013>(); }},
            {"4030", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4030>(); }},
            {"4069", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4069>(); }},
            {"4071", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4071>(); }},
            {"4081", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4081>(); }},
            {"4017", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4017>(); }},
            {"4040", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4040>(); }},
            {"4512", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Component4512>(); }},
            {"logger", []() -> std::unique_ptr <nts::IComponent> { return std::make_unique<nts::Logger>(); }}
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
        std::vector<std::string> fileInVector(void);
        void linkComponents(void);
        void parseData(void);

        void setFileName(std::string fileName) { _fileName = fileName; }

        componentAndNameInVector &getComponents() { return _components; }
        LinkInVector getLinks() { return _links; }
        std::vector<std::string> getFileContent() { return _fileContent; }
        allInputAndNameInVector getInputsVector() { return _inputsVector; }
        allOutputAndNameInVector getOutputsVector() { return _outputsVector; }
        size_t getNbInput() { return _nbInput; }
        size_t getNbOutput() { return _nbOutput; }
        size_t getNbComponents() { return _components.size(); }
        size_t getNbPin() { return (_nbInput + _nbOutput); }

        static std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

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
        size_t _nbInput;
        size_t _nbOutput;
    };

}  // namespace nts
