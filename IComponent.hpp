/*
** EPITECH PROJECT, 2024
** IComponent.hpp
** File description:
** Interface for components
*/

#pragma once

#include <iostream>

namespace nts
{
    class Error : public std::exception {
    public:
        Error(const std::string &message) : _message(message) {}
        ~Error() = default;
        const char *what() const noexcept override {
                return _message.c_str();
        }
    private:
        std::string _message;
    };
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };
    class IComponent
    {
    public :
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) = 0;
        virtual void setInternLink(std::size_t pin, nts::IComponent *other, std::size_t otherPin) = 0;
        virtual nts::Tristate getLink(std::size_t pin) const = 0;
        virtual nts::Tristate getInternLink(std::size_t pin) const = 0;
        virtual std::size_t getNbPins() const = 0;
        virtual void setInput(std::size_t pin) = 0;
        virtual void setOutput(std::size_t pin) = 0;
        virtual void setUnused(std::size_t pin) = 0;
        virtual bool isInput(std::size_t pin) const = 0;
        virtual bool isOutput(std::size_t pin) const = 0;
        virtual bool isUnused(std::size_t pin) const = 0;
        virtual bool isAdvanced() const = 0;
        virtual bool isLinked(std::size_t pin) const = 0;
        virtual nts::IComponent *linkedTo(std::size_t pin) const = 0;
        virtual void checkInfinityCounter() = 0;
        virtual void resetInfinityCounter() = 0;
    };
}  // namespace nts
