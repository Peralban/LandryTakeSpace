/*
** EPITECH PROJECT, 2024
** NanotekSpice.hpp
** File description:
** Created by Alban PERALTA et Landry GIGANT
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ParseFile.hpp"

namespace nts {

    static std::vector sfColor = {
        sf::Color::Blue,
        sf::Color::White,
        sf::Color::Red
    };

    enum Type {
        INPUT,
        OUTPUT,
        GATE
    };

    class SFMLGates {
    public:
        SFMLGates(std::string name, Type type, sf::VideoMode _videoMode);
        ~SFMLGates() = default;
        sf::RectangleShape &getRectangle() { return _rectangle; }
        sf::Text &getText() { return _text; }
    private:
        sf::RectangleShape _rectangle;
        sf::Text _text;
        sf::Font _font;
    };

    class SFMLModule {
    public:
        SFMLModule(componentAndNameInVector &component,
                                    allOutputAndNameInVector outputs, allInputAndNameInVector inputs);
        ~SFMLModule() = default;
        void createWindow();
        void destroyWindow() { _window.close(); }
        sf::VideoMode &getVideoMode() { return _videoMode; }
        void createGates(componentAndNameInVector component, Type type);
        void createOutputGates(allOutputAndNameInVector outputs, Type type);
        void createInputGates(allInputAndNameInVector inputs, Type type);
        sf::Event &getEvent() { return _event; }
        sf::RenderWindow &getWindow() { return _window; }
        void display();
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::VideoMode _videoMode;
        std::vector<std::pair<SFMLGates, std::pair<nts::IComponent *, std::string>>> _inputGates;
        std::vector<std::pair<SFMLGates, std::pair<nts::IComponent *, std::string>>> _outputGates;
        std::vector<std::pair<SFMLGates, std::pair<nts::IComponent *, std::string>>> _otherGates;
    };
}