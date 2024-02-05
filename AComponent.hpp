/*
** EPITECH PROJECT, 2024
** AComponent.hpp
** File description:
** Abstract for components
*/

#pragma once

#include <iostream>
#include "IComponent.hpp"
#include <vector>

namespace nts {
    class AComponent : public IComponent {
    public:
        AComponent() = default;
        AComponent(std::size_t nbPins);
        ~AComponent() = default;
        virtual void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override;
        virtual void setLink(std::size_t pin, nts::IComponent& other, std::size_t otherPin) override;
        virtual void getLink(std::size_t pin) const override;
        virtual std::size_t getNbPins() const override;
    private:
        std::size_t _nbPins;
        std::vector<std::pair<std::size_t, IComponent&>> _links;
    };

}  // namespace nts
