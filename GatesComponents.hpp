/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "AComponent.hpp"

namespace nts {
    class FourGates : public AdvancedComponent {
    public:
        FourGates(std::string gateType);
        ~FourGates() = default;
    };

    // 4081 component: 4 AND gates
    class Component4081 : public FourGates {
    public:
        Component4081() : FourGates("and") {}
        ~Component4081() = default;
    };

    // 4071 component: 4 OR gates
    class Component4071 : public FourGates {
    public:
        Component4071() : FourGates("or") {}
        ~Component4071() = default;
    };

    // 4030 component: 4 XOR gates
    class Component4030 : public FourGates {
    public:
        Component4030() : FourGates("xor") {}
        ~Component4030() = default;
    };

    // 4069 component: 6 NOT gates

    // 4011 component: 4 NAND gates
    class Component4011 : public FourGates {
    public:
        Component4011() : FourGates("nand") {}
        ~Component4011() = default;
    };

    // 4001 component: 4 NOR gates
    class Component4001 : public FourGates {
    public:
        Component4001() : FourGates("nor") {}
        ~Component4001() = default;
    };

    // 4077 component: 4 NXOR gates
    class Component4077 : public FourGates {
    public:
        Component4077() : FourGates("nxor") {}
        ~Component4077() = default;
    };
}