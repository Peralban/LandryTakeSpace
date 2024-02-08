/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "BasicGates.hpp"

/*-----------------AND GATE-----------------*/

nts::AndGate::AndGate(std::size_t nbPins) : nts::AComponent(nbPins)
{
    for (std::size_t i = 1; i < nbPins; i++)
        setInput(i);
    setOutput(nbPins);
}

nts::Tristate nts::AndGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        bool hasUndefined = false;

        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink(i);
            if (buff == nts::Tristate::False)
                return nts::Tristate::False;
            if (buff == nts::Tristate::Undefined)
                hasUndefined = true;
        }
        if (hasUndefined)
            return nts::Tristate::Undefined;
        return nts::Tristate::True;
    }
    if (isInput(pin))
        return getLink(pin);
    throw nts::Error("Pin index out of range");
}

/*-----------------OR GATE-----------------*/

nts::OrGate::OrGate(std::size_t nbPins) : nts::AComponent(nbPins)
{
    for (std::size_t i = 1; i < nbPins; i++)
        setInput(i);
    setOutput(nbPins);
}

nts::Tristate nts::OrGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        bool hasUndefined = false;
        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink(i);
            if (buff == nts::Tristate::True)
                return nts::Tristate::True;
            if (buff == nts::Tristate::Undefined)
                hasUndefined = true;
        }
        if (hasUndefined)
            return nts::Tristate::Undefined;
        return nts::Tristate::False;
    }
    if (isInput(pin))
        return getLink(pin);
    throw nts::Error("Pin index out of range");
}

/*-----------------XOR GATE-----------------*/

nts::XorGate::XorGate(std::size_t nbPins) : nts::AComponent(nbPins)
{
    for (std::size_t i = 1; i < nbPins; i++)
        setInput(i);
    setOutput(nbPins);
}

nts::Tristate nts::XorGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        size_t nbTrue = 0;

        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink(i);
            if (buff == nts::Tristate::Undefined)
                return nts::Tristate::Undefined;
            if (buff == nts::Tristate::True)
                nbTrue++;
        }
        return nbTrue % 2 ? nts::Tristate::True : nts::Tristate::False;
    }
    if (isInput(pin))
        return getLink(pin);
    throw nts::Error("Pin index out of range");
}

/*-----------------NOT GATE-----------------*/

nts::NotGate::NotGate() : nts::AComponent(2)
{
    setInput(1);
    setOutput(2);
}

nts::Tristate nts::NotGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        nts::Tristate buff = getLink(1);
        if (buff == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;
        return buff == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True;
    }
    if (isInput(pin))
        return getLink(pin);
    throw nts::Error("Pin index out of range");
}

/*-----------------NAND GATE-----------------*/

nts::NAndGate::NAndGate(std::size_t nbPins) : nts::AdvancedComponent(nbPins)
{
    IComponent *andGate = new AndGate(_nbPins);
    IComponent *notGate = new NotGate();
    for (std::size_t i = 1; i < _nbPins; i++) {
        setInput(i);
        setInternLink(i, andGate, i);
    }
    setOutput(_nbPins);
    setInternLink(_nbPins, notGate, 2);
    andGate->setLink(_nbPins, notGate, 1);
}

/*-----------------NOR GATE-----------------*/

nts::NOrGate::NOrGate(std::size_t nbPins) : nts::AdvancedComponent(nbPins)
{
    IComponent *orGate = new OrGate(_nbPins);
    IComponent *notGate = new NotGate();
    for (std::size_t i = 1; i < _nbPins; i++) {
        setInput(i);
        setInternLink(i, orGate, i);
    }
    setOutput(_nbPins);
    setInternLink(_nbPins, notGate, 2);
    orGate->setLink(_nbPins, notGate, 1);
}

/*-----------------NXOR GATE-----------------*/

nts::NXorGate::NXorGate(std::size_t nbPins) : nts::AdvancedComponent(nbPins)
{
    IComponent *xorGate = new XorGate(_nbPins);
    IComponent *notGate = new NotGate();
    for (std::size_t i = 1; i < _nbPins; i++) {
        setInput(i);
        setInternLink(i, xorGate, i);
    }
    setOutput(_nbPins);
    setInternLink(_nbPins, notGate, 2);
    xorGate->setLink(_nbPins, notGate, 1);
}

/*-----------------SPLITTER-----------------*/

nts::Splitter::Splitter(std::size_t nbPins) : nts::AComponent(nbPins)
{
    setInput(1);
    for (std::size_t i = 2; i <= nbPins; i++)
        setOutput(i);
}

nts::Tristate nts::Splitter::compute(std::size_t pin)
{
    if (isOutput(pin) || isInput(pin))
        return getLink(1);
    throw nts::Error("Pin index out of range");
}
