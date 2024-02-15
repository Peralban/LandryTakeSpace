/*
** EPITECH PROJECT, 2024
** CreateComponent.cpp
** File description:
** Interface for components
*/

#include "CreateComponent.hpp"

std::unique_ptr<nts::IComponent> nts::createComponent(const std::string &type)
{
    if (type == "and")
        return std::unique_ptr<nts::IComponent>(new nts::AndGate());
    else if (type == "or")
        return std::unique_ptr<nts::IComponent>(new nts::OrGate());
    else if (type == "xor")
        return std::unique_ptr<nts::IComponent>(new nts::XorGate());
    else if (type == "not")
        return std::unique_ptr<nts::IComponent>(new nts::NotGate());
    else if (type == "nand")
        return std::unique_ptr<nts::IComponent>(new nts::NAndGate());
    else if (type == "nor")
        return std::unique_ptr<nts::IComponent>(new nts::NOrGate());
    else if (type == "nxor")
        return std::unique_ptr<nts::IComponent>(new nts::NXorGate());
    else if (type == "splitter")
        return std::unique_ptr<nts::IComponent>(new nts::Splitter());
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
    throw nts::Error("Component not found");
}