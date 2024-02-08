/*
** EPITECH PROJECT, 2024
** AComponent.cpp
** File description:
** Abstract for components
*/

#include "AComponent.hpp"

//rename the pin form [0 to nbPins - 1] to [1 - nbPins]

nts::AComponent::AComponent(std::size_t nbPins, bool advanced)
{
    _nbPins = nbPins;
    _links = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins, std::make_pair(0, nullptr));
    _internLink = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins, std::make_pair(0, nullptr));
    _advanced = advanced;
    _inputPins = std::vector<nts::Tristate>(nbPins, nts::Tristate::Undefined);
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (otherPin > other->getNbPins() || otherPin == 0)
        throw nts::Error("Other pin index out of range");
    if (isOutput(pin) && other->isOutput(otherPin))
        throw nts::Error("Output pin cannot be linked to an output pin");
    if (isInput(pin) && other->isInput(otherPin))
        throw nts::Error("Input pin cannot be linked to an input pin");
    if (isLinked(pin) || (other->linkedTo(otherPin) != this && other->linkedTo(otherPin) != nullptr))
        throw nts::Error("Pin already linked");
    _links[pin - 1] = std::make_pair(otherPin, other);
    if (isAdvanced())
        _internLink[pin - 1].second->setLink(_internLink[pin - 1].first, other, otherPin);
    try {
        other->setLink(otherPin, this, pin);
    } catch (nts::Error &e) {}
}

void nts::AComponent::setInternLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin)
{
    if (!isAdvanced())
        throw nts::Error("Component should not have internal links");
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    if (otherPin > other->getNbPins() || otherPin == 0)
        throw nts::Error("Other pin index out of range");
    if (isOutput(pin) && other->isInput(otherPin))
        throw nts::Error("Output pin cannot be internally linked to an input pin");
    if (isInput(pin) && other->isOutput(otherPin))
        throw nts::Error("Input pin cannot be internally linked to an output pin");
    if (_internLink[pin - 1].second != nullptr)
        throw nts::Error("Pin already linked");
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

nts::IComponent *nts::AComponent::linkedTo(std::size_t pin) const
{
    if (pin > _nbPins || pin == 0)
        throw nts::Error("Pin index out of range");
    return _links[pin - 1].second;
}

/*__________________________________________________________________________*/

nts::Tristate nts::AdvancedComponent::compute(std::size_t pin)
{
    if (isInput(pin))
        return getLink(pin);
    else if (isOutput(pin))
        return getInternLink(pin);
    else
        throw nts::Error("Pin index out of range");
}
