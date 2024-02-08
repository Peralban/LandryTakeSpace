/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
    public:
        TrueComponent();
        ~TrueComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    class FalseComponent : public AComponent {
    public:
        FalseComponent();
        ~FalseComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };
}