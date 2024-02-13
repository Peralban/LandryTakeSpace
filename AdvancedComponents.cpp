/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "AdvancedComponents.hpp"
#include "BasicGates.hpp"

nts::DFlipFlop::DFlipFlop() : AdvancedComponent(6)
{
    setInput(1); // SET
    setInput(2); // DATA
    setInput(3); // CLOCK
    setInput(4); // RESET
    setOutput(5); // Q
    setOutput(6); // Q_NOT

    std::vector<IComponent *> nandGates(6);
    for (std::size_t i = 0; i < 6; i++)
        nandGates[i] = new NAndGate(3);
    std::vector<IComponent *> splitter(10);
    for (std::size_t i = 0; i < 10; i++)
        splitter[i] = new Splitter(3);

    // SET
    setInternLink(1, splitter[0], 1);
    // DATA
    setInternLink(2, splitter[1], 1);
    // CLOCK
    setInternLink(3, splitter[2], 1);
    // RESET
    setInternLink(4, splitter[3], 1);
    // Q
    setInternLink(5, splitter[8], 2);
    // Q_NOT
    setInternLink(6, splitter[9], 2);
    // all internal links are set

    nandGates[0]->setLink(4, splitter[4], 1);
    nandGates[1]->setLink(4, splitter[5], 1);
    nandGates[2]->setLink(4, splitter[6], 1);
    nandGates[3]->setLink(4, splitter[7], 1);
    nandGates[4]->setLink(4, splitter[8], 1);
    nandGates[5]->setLink(4, splitter[9], 1);
    // all nand gates outputs are linked to the splitter inputs

    // SET
    splitter[0]->setLink(2, nandGates[4], 1);
    splitter[0]->setLink(3, nandGates[0], 1);
    splitter[0]->setUnused(4);

    // DATA
    splitter[1]->setLink(2, nandGates[3], 2);
    splitter[1]->setUnused(3);
    splitter[1]->setUnused(4);

    // CLOCK
    splitter[2]->setLink(2, nandGates[1], 2);
    splitter[2]->setLink(3, nandGates[2], 2);
    splitter[2]->setUnused(4);

    // RESET
    splitter[3]->setLink(2, nandGates[1], 3);
    splitter[3]->setLink(3, nandGates[3], 3);
    splitter[3]->setLink(4, nandGates[5], 3);

    // NAndGate 0
    splitter[4]->setLink(2, nandGates[1], 1);
    splitter[4]->setUnused(3);
    splitter[4]->setUnused(4);

    // NAndGate 1
    splitter[5]->setLink(2, nandGates[0], 3);
    splitter[5]->setLink(3, nandGates[4], 2);
    splitter[5]->setLink(4, nandGates[2], 1);

    // NAndGate 2
    splitter[6]->setLink(2, nandGates[5], 2);
    splitter[6]->setLink(3, nandGates[3], 1);
    splitter[6]->setUnused(4);

    // NAndGate 3
    splitter[7]->setLink(2, nandGates[0], 2);
    splitter[7]->setLink(3, nandGates[2], 3);
    splitter[7]->setUnused(4);

    // NAndGate 4 (Q)
    // pin 2 is already used
    splitter[8]->setLink(3, nandGates[5], 1);
    splitter[8]->setUnused(4);

    // NAndGate 5 (Q_NOT)
    // pin 2 is already used
    splitter[9]->setLink(3, nandGates[4], 3);
    splitter[9]->setUnused(4);

}