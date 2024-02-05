/*
** EPITECH PROJECT, 2024
** AComponent.cpp
** File description:
** Abstract for components
*/

#include "AComponent.hpp"

nts::AComponent::AComponent(std::size_t nbPins)
{
    _nbPins = nbPins;
    _pinIn = 0;
    _pinOut = 0;
    _links = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins);
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent* other, std::size_t otherPin)
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    if (otherPin >= other.getNbPins())
        throw nts::Error("Other pin index out of range");
    _links[pin] = std::make_pair(otherPin, other);
}

nts::Tristate nts::AComponent::getLink(std::size_t pin) const
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    return _links[pin].second.compute(_links[pin].first);
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

/*__________________________________________________________________________*/

nts::AdvancedComponent::AdvancedComponent(std::size_t nbPins) : AComponent(nbPins)
{
    _internLink = std::vector<std::pair<std::size_t, nts::IComponent*>>(nbPins);
}

nts::Tristate nts::AdvancedComponent::getInternLink(std::size_t pin) const
{
    if (pin >= _nbPins)
        throw nts::Error("Pin index out of range");
    return _internLink[pin].second->compute(_internLink[pin].first);
}

nts::Tristate nts::AdvancedComponent::compute(std::size_t pin)
{
    if (isInput(pin))
        return getLink(pin);
    else if (isOutput(pin))
        return getInternLink(pin);
    else
        throw nts::Error("Pin index out of range");
}