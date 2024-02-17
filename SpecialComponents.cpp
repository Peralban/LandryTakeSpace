/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "SpecialComponents.hpp"

nts::SpecialComponent::SpecialComponent(nts::Tristate state) : AComponent(5)
{
    setOutput(1);
    for (std::size_t i = 2; i <= 5; i++)
        setInput(i);
    _state[1] = state;
}

nts::Tristate nts::SpecialComponent::compute(std::size_t pin)
{
    if (isOutput(pin))
        return (nts::Tristate)_state[1];
    if (isInput(pin)) {
        _stateSet[1] = 1;
        IComponent *linked = linkedTo(1);
        if  (pin == 2 && _state[1] != nts::Tristate::Undefined) {
            _state[1] = nts::Tristate::Undefined;
        }
        else if (pin == 3 && _state[1] != nts::Tristate::False) {
            _state[1] = nts::Tristate::False;
        }
        else if (pin == 4 && _state[1] != nts::Tristate::True) {
            _state[1] = nts::Tristate::True;
        }
        else if (pin == 5 && _state[1] != nts::Tristate::Undefined) {
            _state[1] = _state[1] == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True;
        }
        if (linked != nullptr)
            linked->clearStateSet(getOtherPin(1));
        return (nts::Tristate)_state[1];
    }
    throw nts::Error("Pin index out of range");
}

/*-----------------CONSTANT INPUT COMPONENT-----------------*/

nts::TrueComponent::TrueComponent() : SpecialComponent(nts::Tristate::True)
{
    for (std::size_t i = 2; i <= 5; i++)
        setUnused(i);
}

nts::FalseComponent::FalseComponent() : SpecialComponent(nts::Tristate::False)
{
    for (std::size_t i = 2; i <= 5; i++)
        setUnused(i);
}

/*-----------------CLOCK COMPONENT-----------------*/

nts::ClockComponent::ClockComponent() : SpecialComponent(nts::Tristate::Undefined) {}

/*-----------------INPUT COMPONENT-----------------*/

nts::InputComponent::InputComponent() : SpecialComponent(nts::Tristate::Undefined)
{
    setUnused(5);
}

/*-----------------OUTPUT COMPONENT-----------------*/

nts::OutputComponent::OutputComponent() : AComponent(2)
{
    setInput(1);
    setOutput(2);
}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (isOutput(pin) || isInput(pin))
        return getLink(1);
    throw nts::Error("Pin index out of range");
}
