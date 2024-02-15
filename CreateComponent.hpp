/*
** EPITECH PROJECT, 2024
** CreateComponent.hpp
** File description:
** Interface for components
*/

#pragma once

#include "BasicGates.hpp"
#include "SpecialComponents.hpp"
#include "GatesComponents.hpp"
#include <memory>

namespace nts {
    std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
}
