/*
** EPITECH PROJECT, 2024
** ParseFike.hpp
** File description:
** Abstract for components
*/

#pragma once

#include <iostream>
#include <vector>

namespace nts
{
    std::vector<std::string> type = {
        "input",
        "output",
        "clock",
        "true",
        "false",
        "and",
        "or",
        "xor",
        "not",
        "4001",
        "4008",
        "4011",
        "4013",
        "4017",
        "4030",
        "4040",
        "4069",
        "4071",
        "4081",
        "4094",
        "4514",
        "4801",
        "end"
    };
    enum ParseState {
        CHIPSETS,
        LINKS,
        NONE
    };


}  // namespace nts
