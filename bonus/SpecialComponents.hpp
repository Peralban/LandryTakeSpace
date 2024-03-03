/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class SpecialComponent : public AComponent {
    public:
        SpecialComponent(nts::Tristate state = nts::Tristate::Undefined);
        ~SpecialComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class TrueComponent : public SpecialComponent {
    public:
        TrueComponent();
        ~TrueComponent() = default;
    };

    class FalseComponent : public SpecialComponent {
    public:
        FalseComponent();
        ~FalseComponent() = default;
    };

    class ClockComponent : public SpecialComponent {
    public:
        ClockComponent();
        ~ClockComponent() = default;
    };

    class InputComponent : public SpecialComponent {
    public:
        InputComponent();
        ~InputComponent() = default;
    };

    class OutputComponent : public AComponent {
    public:
        OutputComponent();
        ~OutputComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };
}