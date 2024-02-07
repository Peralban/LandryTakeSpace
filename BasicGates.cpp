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
    setOutput(_nbPins - 1);
}

nts::Tristate nts::AndGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        bool hasUndefined = false;

        for (std::size_t i = 0; i < _nbPins - 1; i++) {
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
    setOutput(_nbPins - 1);
}

nts::Tristate nts::OrGate::compute(std::size_t pin)
{
    if (isOutput(pin)) {
        bool hasUndefined = false;
        for (std::size_t i = 0; i < _nbPins - 1; i++) {
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
    setOutput(_nbPins - 1);
}

nts::Tristate nts::XorGate::compute(std::size_t pin)
{
    {
        if (isOutput(pin)) {
            size_t nbTrue = 0;

            for (std::size_t i = 0; i < _nbPins - 1; i++) {
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
}
