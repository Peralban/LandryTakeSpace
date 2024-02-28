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

    // 5-STAGE Johnson counter hard defined
    class JohnsonCounterHard : public AComponent {
    public:
        JohnsonCounterHard();
        ~JohnsonCounterHard() = default;
        nts::Tristate compute(std::size_t pin) override;
        void clearStateSet(size_t pin) override;
    private:
        int _data;
    };

    //Decoding Johnson counter
    class JohnsonDecoder : public AdvancedComponent {
    public:
        JohnsonDecoder();
        ~JohnsonDecoder() = default;
    };

    // 4017 component: 10 bits Johnson decade
    class Component4017 : public AdvancedComponent {
    public:
        Component4017();
        ~Component4017() = default;
    };

    // 12 bits binary counter
    class TwelveBitsCounter : public AComponent {
    public:
        TwelveBitsCounter();
        ~TwelveBitsCounter() = default;
        nts::Tristate compute(std::size_t pin) override;
        void clearStateSet(size_t pin) override;
    private:
        int _data;
    };

    // 4040 component: 12 bits binary counter
    class Component4040 : public AdvancedComponent {
    public:
        Component4040();
        ~Component4040() = default;
    };
}