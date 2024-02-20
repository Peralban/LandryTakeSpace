/*
** EPITECH PROJECT, 2024
** AComponent.cpp
** File description:
** Abstract for components
*/

#include "AComponent.hpp"

nts::AComponent::AComponent(std::size_t nbPins, bool advanced)
{
    _nbPins = nbPins;
    _links = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins, std::make_pair(0, nullptr));
    _internLink = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins, std::make_pair(0, nullptr));
    _advanced = advanced;
    _inputPins = std::vector<nts::Tristate>(nbPins, nts::Tristate::Undefined);
    _counter = 0; // infinity loop counter
    _state = std::vector<int>(nbPins + 1, 0);
    _stateSet = std::vector<int>(nbPins + 1, 0);
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (otherPin > other->getNbPins() || otherPin == 0)
        throw nts::Error("Other pin index out of range");
    if (isUnused(pin) || other->isUnused(otherPin))
        throw nts::Error("Unused pin cannot be linked");
    if (isOutput(pin) && other->isOutput(otherPin))
        throw nts::Error("Output pin cannot be linked to an output pin");
    if (isInput(pin) && other->isInput(otherPin))
        throw nts::Error("Input pin cannot be linked to an input pin");
    if (isLinked(pin))
        throw nts::Error("Pin already linked (" + std::to_string(_links[pin - 1].first) + ", " + std::to_string(otherPin) + ")");
    _links[pin - 1] = std::make_pair(otherPin, other);
    try {
        other->setLink(otherPin, this, pin);
    } catch (nts::Error &e) {}
    if (isAdvanced() && isInput(pin))
        _internLink[pin - 1].second->setLink(_internLink[pin - 1].first, other, otherPin);
}

void nts::AComponent::setInternLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
{
    if (!isAdvanced())
        throw nts::Error("Component should not have internal links");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (isUnused(pin) || other->isUnused(otherPin))
        throw nts::Error("Unused pin cannot be linked");
    if (otherPin > other->getNbPins() || otherPin == 0)
        throw nts::Error("Other pin index out of range");
    if (isOutput(pin) && other->isInput(otherPin))
        throw nts::Error("Output pin cannot be internally linked to an input pin");
    if (isInput(pin) && other->isOutput(otherPin))
        throw nts::Error("Input pin cannot be internally linked to an output pin");
    if (_internLink[pin - 1].second != nullptr)
        throw nts::Error("Internal pin already linked (" + std::to_string(_internLink[pin - 1].first) + ", " + std::to_string(otherPin) + ")");
    _internLink[pin - 1] = std::make_pair(otherPin, other);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (_links[pin - 1].second == nullptr)
        return nts::Tristate::Undefined;
    return _links[pin - 1].second->compute(_links[pin - 1].first);
}

nts::Tristate nts::AComponent::getInternLink(std::size_t pin) const
{
    if (!isAdvanced())
        throw nts::Error("Component has no internal link");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (_internLink[pin - 1].second == nullptr)
        return nts::Tristate::Undefined;
    return _internLink[pin - 1].second->compute(_internLink[pin - 1].first);
}

std::size_t nts::AComponent::getNbPins() const
{
    return _nbPins;
}

void nts::AComponent::setInput(std::size_t pin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _inputPins[pin - 1] = nts::Tristate::True;
}

void nts::AComponent::setOutput(std::size_t pin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _inputPins[pin - 1] = nts::Tristate::False;
}

void nts::AComponent::setUnused(std::size_t pin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _inputPins[pin - 1] = nts::Tristate::Undefined;
}

bool nts::AComponent::isInput(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _inputPins[pin - 1] == nts::Tristate::True;
}

bool nts::AComponent::isOutput(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _inputPins[pin - 1] == nts::Tristate::False;
}

bool nts::AComponent::isUnused(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _inputPins[pin - 1] == nts::Tristate::Undefined;
}

bool nts::AComponent::isAdvanced() const
{
    return _advanced;
}

bool nts::AComponent::isLinked(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _links[pin - 1].second != nullptr;
}

bool nts::AComponent::isInternLinked(std::size_t pin) const
{
    if (!isAdvanced())
        throw nts::Error("Component has no internal link");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _internLink[pin - 1].second != nullptr;
}

nts::IComponent *nts::AComponent::linkedTo(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _links[pin - 1].second;
}

nts::IComponent *nts::AComponent::internLinkedTo(std::size_t pin) const
{
    if (!isAdvanced())
        throw nts::Error("Component has no internal link");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _internLink[pin - 1].second;
}

void nts::AComponent::checkInfinityCounter()
{
    if (_counter > 1000)
        throw nts::Error("Infinity loop detected");
    _counter++;
}

void nts::AComponent::resetInfinityCounter()
{
    if (_counter == 0)
        return;
    _counter = 0;
    for (std::size_t i = 0; i < _nbPins; i++)
        if (_links[i].second != nullptr)
            _links[i].second->resetInfinityCounter();
    if (isAdvanced())
        for (std::size_t i = 0; i < _nbPins; i++)
            if (_internLink[i].second != nullptr)
                _internLink[i].second->resetInfinityCounter();
}

void nts::AComponent::clearStateSet(size_t pin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (isInput(pin)) {
        _stateSet[pin] = 0;
        if (isAdvanced()) {
            if (isInput(pin) && internLinkedTo(pin) != nullptr)
                internLinkedTo(pin)->clearStateSet(getOtherInternPin(pin));
        }
        for (std::size_t i = 1; i <= getNbPins(); i++) {
            _stateSet[i] = 0;
            if (isOutput(i) && _state[i] != compute(i)) {
                clearStateSet(i);
            }
        }
    }
    if (isOutput(pin)) {
        IComponent *linked = linkedTo(pin);
        if (linked == nullptr)
            return;
        linkedTo(pin)->clearStateSet(getOtherPin(pin));
    }
    if (isUnused(pin))
        throw nts::Error("Unused pin cannot be cleared");
}

int nts::AComponent::getState(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _state[pin];
}

void nts::AComponent::setState(std::size_t pin, nts::Tristate state)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _state[pin] = (int)state;
}

void nts::AComponent::setState(std::size_t pin, int state)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _state[pin] = state;
}

int nts::AComponent::getStateSet(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _stateSet[pin];
}

void nts::AComponent::setStateSet(std::size_t pin, int state)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    _stateSet[pin] = state;
}

std::size_t nts::AComponent::getOtherPin(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _links[pin - 1].first;
}

std::size_t nts::AComponent::getOtherInternPin(std::size_t pin) const
{
    if (!isAdvanced())
        throw nts::Error("Component has no internal link");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _internLink[pin - 1].first;
}

/*__________________________________________________________________________*/

nts::Tristate nts::AdvancedComponent::compute(std::size_t pin)
{
    checkInfinityCounter();
    if (isInput(pin))
        return getLink(pin);
    else if (isOutput(pin)) {
        if (_stateSet[pin] == 1)
            return (nts::Tristate)_state[pin];
        nts::Tristate buff = getInternLink(pin);
        _stateSet[pin] = 1;
        _state[pin] = (int)buff;
        return buff;
    }
    else
        throw nts::Error("Pin index out of range");
}
