/*
** EPITECH PROJECT, 2024
** ParseFike.hpp
** File description:
** Abstract for components
*/

#pragma once

#include <iostream>

namespace nts
{
    enum ComponentType {
        INPUT = 0,
        OUTPUT,
        CLOCK,
        TRUE,
        FALSE,
        C4001,
        C4011,
        C4030,
        C4069,
        C4071,
        C4081,
        C4008,
        C4013,
        C4017,
        C4040,
        C4094,
        C4512,
        C4514,
        C4801,
        C2716
    };
    enum ParseState {
        CHIPSETS,
        LINKS,
        NONE
    };


}  // namespace nts
