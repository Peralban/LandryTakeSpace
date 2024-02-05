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
    _pinIn = 0;
    _pinOut = 0;
    _links = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins);
    _internLink = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins);
    _advanced = advanced;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent* other, std::size_t otherPin)
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    if (otherPin >= other.getNbPins())
        throw nts::Error("Other pin index out of range");
    if (isOutput(pin) && other->isOutput(otherPin))
        throw nts::Error("Output pin cannot be linked to an output pin");
    if (isInput(pin) && other->isInput(otherPin))
        throw nts::Error("Input pin cannot be linked to an input pin");
    if (_links[pin].second != nullptr)
        throw nts::Error("Pin already linked");
    _links[pin] = std::make_pair(otherPin, other);
    if (isAdvanced())
        _internLink[pin].second->setLink(_internLink[pin].first, other, otherPin);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) const
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    return _links[pin].second.compute(_links[pin].first);
}

nts::Tristate nts::AComponent::getInternLink(std::size_t pin) const
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    return _internLink[pin].second->compute(_internLink[pin].first);
}

std::size_t nts::AComponent::getNbPins() const
{
    return _nbPins;
}

bool nts::AComponent::isInput(std::size_t pin) const
{
    return pin < _pinIn;
}

bool nts::AComponent::isOutput(std::size_t pin) const
{
    return pin >= _pinIn && pin < _pinOut;
}

bool nts::AComponent::isAdvanced() const
{
    return _advanced;
}

/*__________________________________________________________________________*/
