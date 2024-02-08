/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class AndGate : public AComponent {
    public:
        AndGate(std::size_t nbPins = 3);
        ~AndGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class OrGate : public AComponent {
    public:
        OrGate(std::size_t nbPins = 3);
        ~OrGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class XorGate : public AComponent {
    public:
        XorGate(std::size_t nbPins = 3);
        ~XorGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class NotGate : public AComponent {
    public:
        NotGate();
        ~NotGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class NAndGate : public AdvancedComponent {
    public:
        NAndGate(std::size_t nbPins = 3);
        ~NAndGate() = default;
    };
}

