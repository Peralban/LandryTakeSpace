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
        void setInternLink(std::size_t pin, nts::IComponent* other, std::size_t otherPin) override;
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
        nts::Tristate compute(std::size_t pin) override;
    };

    //class AndGate : public AComponent {
    //public:
    //    AndGate(std::size_t nbPins = 3) : AComponent(nbPins) { _pinIn = nbPins - 1; _pinOut = 1; }
    //    ~AndGate() = default;
    //    nts::Tristate compute(std::size_t pin) override {
    //        if (isOutput(pin)) {
    //            bool hasUndefined = false;
    //            for (std::size_t i = 0; i < _nbPins - 1; i++) {
    //                nts::Tristate buff = getLink(i);
    //                if (buff == nts::Tristate::False)
    //                    return nts::Tristate::False;
    //                if (buff == nts::Tristate::Undefined)
    //                    hasUndefined = true;
    //            }
    //            if (hasUndefined)
    //                return nts::Tristate::Undefined;
    //            return nts::Tristate::True;
    //        }
    //        if (isInput(pin))
    //            return getLink(pin);
    //        throw nts::Error("Pin index out of range");
    //    }
    //};
//
    //class OrGate : public AComponent {
    //public:
    //    OrGate(std::size_t nbPins = 3) : AComponent(nbPins) { _pinIn = nbPins - 1; _pinOut = 1; }
    //    ~OrGate() = default;
    //    nts::Tristate compute(std::size_t pin) override {
    //        if (isOutput(pin)) {
    //            bool hasUndefined = false;
    //            for (std::size_t i = 0; i < _nbPins - 1; i++) {
    //                nts::Tristate buff = getLink(i);
    //                if (buff == nts::Tristate::True)
    //                    return nts::Tristate::True;
    //                if (buff == nts::Tristate::Undefined)
    //                    hasUndefined = true;
    //            }
    //            if (hasUndefined)
    //                return nts::Tristate::Undefined;
    //            return nts::Tristate::False;
    //        }
    //        if (isInput(pin))
    //            return getLink(pin);
    //        throw nts::Error("Pin index out of range");
    //    }
    //};
//
    //class XorGate : public AComponent {
    //public:
    //    XorGate(std::size_t nbPins = 3) : AComponent(nbPins) { _pinIn = nbPins - 1; _pinOut = 1; }
    //    ~XorGate() = default;
    //    nts::Tristate compute(std::size_t pin) override {
    //        if (isOutput(pin)) {
    //            size_t nbTrue = 0;
    //            for (std::size_t i = 0; i < _nbPins - 1; i++) {
    //                nts::Tristate buff = getLink(i);
    //                if (buff == nts::Tristate::Undefined)
    //                    return nts::Tristate::Undefined;
    //                if (buff == nts::Tristate::True)
    //                    nbTrue++;
    //            }
    //            return nbTrue % 2 ? nts::Tristate::True : nts::Tristate::False;
    //        }
    //        if (isInput(pin))
    //            return getLink(pin);
    //        throw nts::Error("Pin index out of range");
    //    }
    //};
//
    //class NotGate : public AComponent {
    //public:
    //    NotGate() : AComponent(2) { _pinIn = 1; _pinOut = 1; }
    //    ~NotGate() = default;
    //    nts::Tristate compute(std::size_t pin) override {
    //        if (isOutput(pin)) {
    //            nts::Tristate buff = getLink(0);
    //            if (buff == nts::Tristate::Undefined)
    //                return nts::Tristate::Undefined;
    //            return buff == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True;
    //        }
    //        if (isInput(pin))
    //            return getLink(pin);
    //        throw nts::Error("Pin index out of range");
    //    }
    //};
//
    //class NAndGate : public AdvancedComponent {
    //public:
    //    NAndGate(std::size_t nbPins = 3) : AdvancedComponent(nbPins) {
    //        _pinIn = nbPins - 1;
    //        _pinOut = 1;
    //        IComponent *andGate = new AndGate(nbPins - 1);
    //        IComponent *notGate = new NotGate();
    //        for (std::size_t i = 0; i < _pinIn; i++) {
    //            setInternLink(i, andGate, i);
    //        }
    //        setInternLink(_nbPins - 1, notGate, 1);
    //        andGate->setLink(andGate->getNbPins() - 1, notGate, 0);
    //    }
    //    ~NAndGate() = default;
    //};

}  // namespace nts
