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
        void simulate(std::size_t tick) override {(void)tick;};
        void setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) override;
        void setInternLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) override;
        nts::Tristate getLink(std::size_t pin) const override;
        nts::Tristate getInternLink(std::size_t pin) const override;
        std::size_t getNbPins() const override;
        void setInput(std::size_t pin) override;
        void setOutput(std::size_t pin) override;
        bool isInput(std::size_t pin) const override;
        bool isOutput(std::size_t pin) const override;
        bool isAdvanced() const override;
        bool isLinked(std::size_t pin) const override;
        nts::IComponent *linkedTo(std::size_t pin) const override;
    protected:
        bool _advanced;
        std::size_t _nbPins;
        std::vector<bool> _inputPins;
        std::vector<std::pair<std::size_t, nts::IComponent*>> _links;
        std::vector<std::pair<std::size_t, IComponent*>> _internLink;
    };

    class AdvancedComponent : public AComponent {
    public:
        AdvancedComponent(std::size_t nbPins) : AComponent(nbPins, true) {}
        ~AdvancedComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };

    //class NOrGate : public AdvancedComponent {
    //public:
    //    NOrGate(std::size_t nbPins = 3) : AdvancedComponent(nbPins) {
    //        _pinIn = nbPins - 1;
    //        _pinOut = 1;
    //        IComponent *orGate = new OrGate(nbPins - 1);
    //        IComponent *inverterGate = new InverterGate();
    //        for (std::size_t i = 0; i < _pinIn; i++) {
    //            setInternLink(i, orGate, i);
    //        }
    //        setInternLink(_nbPins - 1, inverterGate, 1);
    //        orGate->setLink(orGate->getNbPins() - 1, inverterGate, 0);
    //    }
    //    ~NOrGate() = default;
    //};

}  // namespace nts
