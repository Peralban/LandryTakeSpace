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
        AndGate(std::size_t inputs = 2);
        ~AndGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class OrGate : public AComponent {
    public:
        OrGate(std::size_t inputs = 2);
        ~OrGate() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class XorGate : public AComponent {
    public:
        XorGate(std::size_t inputs = 2);
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
        NAndGate(std::size_t inputs = 2);
        ~NAndGate() = default;
    };

    class NOrGate : public AdvancedComponent {
    public:
        NOrGate(std::size_t inputs = 2);
        ~NOrGate() = default;
    };

    class XNorGate : public AdvancedComponent {
    public:
        XNorGate(std::size_t inputs = 2);
        ~XNorGate() = default;
    };

    class Splitter : public AComponent {
    public:
        Splitter(std::size_t outputs = 2);
        ~Splitter() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

}

