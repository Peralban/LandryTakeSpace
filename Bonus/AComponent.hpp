/*
** EPITECH PROJECT, 2024
** AComponent.hpp
** File description:
** Abstract for components
*/

#pragma once

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
        void setUnused(std::size_t pin) override;
        bool isInput(std::size_t pin) const override;
        bool isOutput(std::size_t pin) const override;
        bool isUnused(std::size_t pin) const override;
        bool isAdvanced() const override;
        bool isLinked(std::size_t pin) const override;
        bool isInternLinked(std::size_t pin) const override;
        nts::IComponent *linkedTo(std::size_t pin) const override;
        nts::IComponent *internLinkedTo(std::size_t pin) const override;
        void checkInfinityCounter() override;
        void resetInfinityCounter() override;
        void clearStateSet(size_t pin) override;
        int getState(std::size_t pin) const override;
        void setState(std::size_t pin, nts::Tristate state) override;
        void setState(std::size_t pin, int state) override;
        int getStateSet(std::size_t pin) const override;
        void setStateSet(std::size_t pin, int state) override;
        std::size_t getOtherPin(std::size_t pin) const override;
        std::size_t getOtherInternPin(std::size_t pin) const override;
    protected:
        bool _advanced; // Advanced components have internal links to internal components
        std::size_t _nbPins;
        std::vector<nts::Tristate> _inputPins; // True = Input, False = Output, Undefined = Unused
        std::vector<std::pair<std::size_t, nts::IComponent*>> _links;
        std::vector<std::pair<std::size_t, IComponent*>> _internLink;
        std::size_t _counter;
        std::vector<int> _state;
        std::vector<int> _stateSet;
    };

    class AdvancedComponent : public AComponent {
    public:
        AdvancedComponent(std::size_t nbPins) : AComponent(nbPins, true) {}
        ~AdvancedComponent() = default;
        nts::Tristate compute(std::size_t pin) override;
    };
}  // namespace nts
