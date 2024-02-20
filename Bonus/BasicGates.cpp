/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "BasicGates.hpp"

/*-----------------AND GATE-----------------*/

nts::AndGate::AndGate(std::size_t inputs) : nts::AComponent(inputs + 1)
{
    for (std::size_t i = 1; i < _nbPins; i++)
        setInput(i);
    setOutput(_nbPins);
}

nts::Tristate nts::AndGate::compute(std::size_t pin)
{
    checkInfinityCounter();
    if (_stateSet[pin] == 1 || _stateSet[pin] == 2)
        return (nts::Tristate)_state[pin];

    if (isOutput(pin)) {
        bool hasUndefined = false;

        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink((i + _counter) % (_nbPins - 1) + 1);
            if (_stateSet[pin] == 1)
                return (nts::Tristate)_state[pin];
            if (buff == nts::Tristate::False) {
                _stateSet[pin] = 1;
                _state[pin] = nts::Tristate::False;
                return nts::Tristate::False;
            }
            if (buff == nts::Tristate::Undefined) {
                hasUndefined = true;
                _stateSet[pin] = 2;
            }
        }
        if (hasUndefined) {
            _stateSet[pin] = 1;
            _state[pin] = nts::Tristate::Undefined;
            return nts::Tristate::Undefined;
        }
        _stateSet[pin] = 1;
        _state[pin] = nts::Tristate::True;
        return nts::Tristate::True;
    }

    if (isInput(pin))
        return getLink(pin);

    throw nts::Error("Pin index out of range");
}

/*-----------------OR GATE-----------------*/

nts::OrGate::OrGate(std::size_t inputs) : nts::AComponent(inputs + 1)
{
    for (std::size_t i = 1; i < _nbPins; i++)
        setInput(i);
    setOutput(_nbPins);
}

nts::Tristate nts::OrGate::compute(std::size_t pin)
{
    checkInfinityCounter();
    if (_stateSet[pin] == 2 || _stateSet[pin] == 1)
        return (nts::Tristate)_state[pin];

    if (isOutput(pin)) {
        bool hasUndefined = false;
        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink((i + _counter) % (_nbPins - 1) + 1);
            if (_stateSet[pin] == 1)
                return (nts::Tristate)_state[pin];
            if (buff == nts::Tristate::True) {
                _stateSet[pin] = 1;
                _state[pin] = nts::Tristate::True;
                return nts::Tristate::True;
            }
            if (buff == nts::Tristate::Undefined) {
                _stateSet[pin] = 2;
                hasUndefined = true;
            }
        }
        if (hasUndefined) {
            _stateSet[pin] = 1;
            _state[pin] = nts::Tristate::Undefined;
            return nts::Tristate::Undefined;
        }
        _stateSet[pin] = 1;
        _state[pin] = nts::Tristate::False;
        return nts::Tristate::False;
    }

    if (isInput(pin))
        return getLink(pin);

    throw nts::Error("Pin index out of range");
}

/*-----------------XOR GATE-----------------*/

nts::XorGate::XorGate(std::size_t inputs) : nts::AComponent(inputs + 1)
{
    for (std::size_t i = 1; i < _nbPins; i++)
        setInput(i);
    setOutput(_nbPins);
}

nts::Tristate nts::XorGate::compute(std::size_t pin)
{
    checkInfinityCounter();
    if (_stateSet[pin] == 1)
        return (nts::Tristate)_state[pin];

    if (isOutput(pin)) {
        size_t nbTrue = 0;

        for (std::size_t i = 1; i < _nbPins; i++) {
            nts::Tristate buff = getLink((i + _counter) % (_nbPins - 1) + 1);
            if (_stateSet[pin] == 1)
                return (nts::Tristate)_state[pin];
            if (buff == nts::Tristate::Undefined) {
                _stateSet[pin] = 1;
                _state[pin] = nts::Tristate::Undefined;
                return nts::Tristate::Undefined;
            }
            if (buff == nts::Tristate::True)
                nbTrue++;
        }
        _stateSet[pin] = 1;
        _state[pin] = nbTrue % 2 ? nts::Tristate::True : nts::Tristate::False;
        std::cout << "XOR GATE: " << _state[pin] << std::endl;
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
    checkInfinityCounter();
    if (isOutput(pin)) {
        _state[pin] = getLink(1);
        _stateSet[pin] = 1;
        if (_state[pin] == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;
        return _state[pin] == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True;
    }
    if (isInput(pin))
        return getLink(pin);
    throw nts::Error("Pin index out of range");
}

/*-----------------NAND GATE-----------------*/

nts::NAndGate::NAndGate(std::size_t inputs) : nts::AdvancedComponent(inputs + 1)
{
    IComponent *andGate = new AndGate(inputs);
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

nts::NOrGate::NOrGate(std::size_t inputs) : nts::AdvancedComponent(inputs + 1)
{
    IComponent *orGate = new OrGate(inputs);
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

nts::XNorGate::XNorGate(std::size_t inputs) : nts::AdvancedComponent(inputs + 1)
{
    IComponent *xorGate = new XorGate(inputs);
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

nts::Splitter::Splitter(std::size_t outputs) : nts::AComponent(outputs + 1)
{
    setInput(1);
    for (std::size_t i = 2; i <= _nbPins; i++)
        setOutput(i);
}

nts::Tristate nts::Splitter::compute(std::size_t pin)
{
    checkInfinityCounter();
    if (isOutput(pin) || isInput(pin)) {
        _stateSet[pin] = 1;
        _state[pin] = getLink(1);
        return (nts::Tristate)_state[pin];
    }
    throw nts::Error("Pin index out of range");
}
