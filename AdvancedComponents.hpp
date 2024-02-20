/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    // DFlipFlop
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

    // Sum Component
    class SumComponent : public AdvancedComponent {
    public:
        SumComponent();
        ~SumComponent() = default;
    };

    // High Speed Par Carry
    class HighSpeedParCarry : public AdvancedComponent {
    public:
        HighSpeedParCarry();
        ~HighSpeedParCarry() = default;
    };

    // 4008 component: 4-bit adder
    class Component4008 : public AdvancedComponent {
    public:
        Component4008();
        ~Component4008() = default;
    };
}