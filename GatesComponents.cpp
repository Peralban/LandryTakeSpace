/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "GatesComponents.hpp"
#include "BasicGates.hpp"
#include "SpecialComponents.hpp"

// ! temporary !
// This function is used to create a component based on the type given in parameter

nts::IComponent *createComponent(std::string type)
{
    if (type == "and")
        return new nts::AndGate();
    if (type == "or")
        return new nts::OrGate();
    if (type == "xor")
        return new nts::XorGate();
    if (type == "not")
        return new nts::NotGate();
    if (type == "nand")
        return new nts::NAndGate();
    if (type == "nor")
        return new nts::NOrGate();
    if (type == "nxor")
        return new nts::NXorGate();
    if (type == "splitter")
        return new nts::Splitter();
    if (type == "true")
        return new nts::TrueComponent();
    if (type == "false")
        return new nts::FalseComponent();
    throw nts::Error("Invalid component type");
}

// ! temporary ! end

nts::FourGates::FourGates(std::string name) : AdvancedComponent(14)
{
    for (std::size_t i = 1; i <= 14; i++)
        setInput(i);
    setUnused(7);
    setUnused(14);
    setOutput(3);
    setOutput(4);
    setOutput(10);
    setOutput(11);

    if (name != "and" && name != "or" && name != "xor" && name != "nand" && name != "nor" && name != "nxor")
        throw nts::Error("Invalid gate type");

    // may change the way of doing this
    std::vector<IComponent *> gates(4);
    for (std::size_t i = 0; i < 4; i++)
        gates[i] = createComponent(name);

    std::size_t tmp = 0;
    for (std::size_t i = 0; i < 4; i++) {
        try {
            setInternLink(i * 3 + (i % 2 == 0 ? 1 : 3) + tmp, gates[i], 1);
            setInternLink(i * 3 + 2 + tmp, gates[i], 2);
            setInternLink(i * 3 + (i % 2 == 0 ? 3 : 1) + tmp, gates[i], 3);
            if (i == 1)
                tmp = 1;
        } catch (nts::Error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

nts::Component4069::Component4069() : AdvancedComponent(14)
{
    for (std::size_t i = 0; i < 7; i++) {
        setInput(i * 2 + 1);
        setOutput(i * 2 + 2);
    }
    setUnused(7);
    setUnused(14);

    std::vector<IComponent *> gates(6);
    for (std::size_t i = 0; i < 6; i++)
        gates[i] = createComponent("not");

    for (std::size_t i = 0; i < 3; i++) {
        try {
            setInternLink(i * 2 + 1, gates[i], 1);
            setInternLink(i * 2 + 2, gates[i], 2);
            setInternLink(i * 2 + 8, gates[i + 3], 2);
            setInternLink(i * 2 + 9, gates[i + 3], 1);
        } catch (nts::Error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
