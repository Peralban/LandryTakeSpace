/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class DFlipFlop : public AdvancedComponent {
    public:
        DFlipFlop();
        ~DFlipFlop() = default;
    };

    // 4013 component: 2 DFlipFlop
    class Component4013 : public AdvancedComponent {
    public:
        Component4013();
        ~Component4013() = default;
    };
}