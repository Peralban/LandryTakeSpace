/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "SpecialComponents.hpp"

nts::TrueComponent::TrueComponent() : AComponent(1)
{
    setOutput(1);
}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (isOutput(pin))
        return nts::Tristate::True;
    throw nts::Error("Pin index out of range");
}

nts::FalseComponent::FalseComponent() : AComponent(1)
{
    setOutput(1);
}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (isOutput(pin))
        return nts::Tristate::False;
    throw nts::Error("Pin index out of range");
}
