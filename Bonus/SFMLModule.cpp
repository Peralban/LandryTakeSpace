/*
** EPITECH PROJECT, 2024
** NanotekSpice.hpp
** File description:
** Created by Alban PERALTA et Landry GIGANT
*/

#include "SFMLModule.hpp"
#include "ParseFile.hpp"

nts::SFMLModule::SFMLModule(componentAndNameInVector &component,
                       allOutputAndNameInVector outputs, allInputAndNameInVector inputs)

{
    _videoMode = sf::VideoMode(1920, 1080);
    _window.setFramerateLimit(60);
    for (size_t i = 0; i < component.size(); i++) {
        for (size_t j = 0; j < outputs.size(); j++) {
            if (component[i].second == outputs[j].second) {
                component.erase(component.begin() + i);
                i--;
                break;
            }
        }
        for (size_t j = 0; j < inputs.size(); j++) {
            if (component[i].second == inputs[j].second) {
                component.erase(component.begin() + i);
                i--;
                break;
            }
        }
    }
    createInputGates(inputs, INPUT);
    createOutputGates(outputs, OUTPUT);
    createGates(component, GATE);
}

void nts::SFMLModule::createWindow()
{
    _window.create(_videoMode, "NanotekSpice", sf::Style::Default, sf::ContextSettings(0, 0, 8));
}

void nts::SFMLModule::createGates(componentAndNameInVector component, Type type)
{
    for (auto &comp : component) {
        SFMLGates gate(comp.second, type, _videoMode);
        _otherGates.push_back(std::make_pair(gate, comp));
    }
}

void nts::SFMLModule::createOutputGates(allOutputAndNameInVector outputs, Type type)
{
    for (auto &output : outputs) {
        SFMLGates gate(output.second, type, _videoMode);
        _outputGates.push_back(std::make_pair(gate, output));
    }
}

void nts::SFMLModule::createInputGates(allInputAndNameInVector inputs, Type type)
{
    for (auto &input : inputs) {
        SFMLGates gate(input.second, type, _videoMode);
        _inputGates.push_back(std::make_pair(gate, input));
    }
}
void nts::SFMLModule::display()
{
    _window.clear(sf::Color::White);
    for (auto &input : _inputGates) {
        nts::Tristate state = input.second.first->compute(1);
        if (state == 1)
            input.first.getRectangle().setFillColor(sf::Color::Green);
        else if (state == 0)
            input.first.getRectangle().setFillColor(sf::Color::Red);
        else
            input.first.getRectangle().setFillColor(sf::Color(128, 128, 128, 255));
        input.second.first->resetInfinityCounter();
        _window.draw(input.first.getRectangle());
        _window.draw(input.first.getText());
    }
    for (auto &output : _outputGates) {
        nts::Tristate state = output.second.first->compute(1);
        if (state == 1)
            output.first.getRectangle().setFillColor(sf::Color::Green);
        else if (state == 0)
            output.first.getRectangle().setFillColor(sf::Color::Red);
        else
            output.first.getRectangle().setFillColor(sf::Color(128, 128, 128, 255));
        output.second.first->resetInfinityCounter();
        _window.draw(output.first.getRectangle());
        _window.draw(output.first.getText());
    }
    for (auto &gate : _otherGates) {
        nts::Tristate state = gate.second.first->compute(1);
        if (state == 1)
            gate.first.getRectangle().setFillColor(sf::Color::Green);
        else if (state == 0)
            gate.first.getRectangle().setFillColor(sf::Color::Red);
        else
            gate.first.getRectangle().setFillColor(sf::Color(128, 128, 128, 255));
        gate.second.first->resetInfinityCounter();
        _window.draw(gate.first.getRectangle());
        _window.draw(gate.first.getText());
    }
    _window.display();
}

//////////////////////////////////////////////////////////////////////////////////

nts::SFMLGates::SFMLGates(std::string name, Type type, sf::VideoMode _videoMode)
{
    static int x = 0;
    static int y = 0;
    static int stape = 0;
    // if it's an input the gate has to be on the left side of the window
    if (type == INPUT) {
        x = 0;
        y += 125;
    } else if (type == OUTPUT) {
        if (stape == 0) {
            x = 1700;
            y = 0;
            stape = 1;
        } else {
            x = 1700;
            y += 125;
        }
    } else {
        if (stape == 0) {
            x = (1920 / 2);
            y = 0;
            stape = 1;
        } else {
            x = (1920 / 2);
            y += 125;
        }
    }
    _rectangle.setSize(sf::Vector2f(100, 100));
    _rectangle.setFillColor(sf::Color::White);
    _rectangle.setOutlineColor(sf::Color::Black);
    _rectangle.setOutlineThickness(2);
    _rectangle.setPosition(x, y);
    _text.setString(name);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::Black);
    _text.setPosition(_rectangle.getPosition().x + 25, _rectangle.getPosition().y + 25);
}