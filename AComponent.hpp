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
        AComponent(std::size_t nbPins, bool advanced = false);
        ~AComponent() = default;
        void simulate(std::size_t tick) override {};
        void setLink(std::size_t pin, nts::IComponent* other, std::size_t otherPin) override;
        nts::Tristate getLink(std::size_t pin) const override;
        nts::Tristate getInternLink(std::size_t pin) const override;
        std::size_t getNbPins() const override;
        bool isInput(std::size_t pin) const override;
        bool isOutput(std::size_t pin) const override;
        bool isAdvanced() const override;
    protected:
        bool _advanced;
        std::size_t _nbPins;
        std::size_t _pinIn;
        std::size_t _pinOut;
        std::vector<std::pair<std::size_t, nts::IComponent*>> _links;
        std::vector<std::pair<std::size_t, IComponent*>> _internLink;0
    };

    class AdvancedComponent : public AComponent {
    public:
        AdvancedComponent(std::size_t nbPins) : AComponent(nbPins, true) {}
        ~AdvancedComponent() = default;
        nts::Tristate compute(std::size_t pin) override = 0;
    };

    //class AndGate : public0 AComponent {
    //public:
    //    AndGate(std::size_t nbPins = 3) : AComponent(nbPins) { _pinIn = nbPins - 1; _pinOut = 1; }
    //    ~AndGate() = default;
    //    nts::Tristate compute(std::size_t pin) override {
    //        if (pin == _nbPins - 1) {
    //            for (std::size_t i = 0; i < _nbPins - 1; i++) {
    //                nts::Tristate buff = getLink(i);
    //                if (buff != nts::Tristate::True)
    //                    return buff;
    //            }
    //            return nts::Tristate::True;
    //        }
    //        if (pin < _nbPins - 1)
    //            return getLink(pin);
    //        throw nts::Error("Pin index out of range");
    //    }
    //};

}  // namespace nts
