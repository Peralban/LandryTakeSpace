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
    size_t allSize = component.size() + outputs.size() + inputs.size();
    createInputGates(inputs, INPUT, allSize);
    createGates(component, GATE, allSize);
    createOutputGates(outputs, OUTPUT, allSize);
}

void nts::SFMLModule::createWindow()
{
    _window.create(_videoMode, "NanotekSpice", sf::Style::Default, sf::ContextSettings(0, 0, 8));
}

void nts::SFMLModule::createGates(componentAndNameInVector component, Type type, size_t allSize)
{
    int index = 0;
    for (auto &comp : component) {
        SFMLGates gate(comp.second, type, _videoMode, component.size(), index, allSize);
        _otherGates.push_back(std::make_pair(gate, comp));
        index++;
    }
}

void nts::SFMLModule::createOutputGates(allOutputAndNameInVector outputs, Type type, size_t allSize)
{
    int index = 0;
    for (auto &output : outputs) {
        SFMLGates gate(output.second, type, _videoMode, outputs.size(), index, allSize);
        _outputGates.push_back(std::make_pair(gate, output));
        index++;
    }
}

void nts::SFMLModule::createInputGates(allInputAndNameInVector inputs, Type type, size_t allSize)
{
    int index = 0;
    for (auto &input : inputs) {
        SFMLGates gate(input.second, type, _videoMode, inputs.size(), index, allSize);
        _inputGates.push_back(std::make_pair(gate, input));
        index++;
    }
}

void nts::SFMLModule::displayAll()
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
        /////////////////////////////////////////////////////////////////////// draw text
        std::string name = input.first.getText().getString().toAnsiString();
        sf::Font font;
        if (!font.loadFromFile("Fonts/Montserrat-Regular.ttf"))
            throw std::runtime_error("Error: Font not found");
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(input.first.getRectangle().getSize().x / 2);
        text.setPosition(input.first.getRectangle().getPosition().x + input.first.getRectangle().getSize().x / 2 - text.getGlobalBounds().width / 2,
                         input.first.getRectangle().getPosition().y + input.first.getRectangle().getSize().y / 2 - text.getGlobalBounds().height / 2);
        /////////////////////////////////////////////////////////////////////// draw link
        bool isLinked = false;
        for (size_t i = 1; i < input.second.first->getNbPins(); i++) {
            isLinked = false;
            nts::IComponent *linked = input.second.first->linkedTo(i);
            for (auto &output : _outputGates) {
                if (linked == output.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(input.first.getRectangle().getPosition().x + input.first.getRectangle().getSize().x,
                                                 input.first.getRectangle().getPosition().y + input.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(output.first.getRectangle().getPosition().x,
                                                 output.first.getRectangle().getPosition().y + output.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
            for (auto &gate : _otherGates) {
                if (linked == gate.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(input.first.getRectangle().getPosition().x + input.first.getRectangle().getSize().x,
                                                 input.first.getRectangle().getPosition().y + input.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(gate.first.getRectangle().getPosition().x,
                                                 gate.first.getRectangle().getPosition().y + gate.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
        }
        _window.draw(text);
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
        /////////////////////////////////////////////////////////////////////// draw text
        std::string name = output.first.getText().getString().toAnsiString();
        sf::Font font;
        if (!font.loadFromFile("Fonts/Montserrat-Regular.ttf"))
            throw std::runtime_error("Error: Font not found");
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(output.first.getRectangle().getSize().x / 2);
        text.setPosition(output.first.getRectangle().getPosition().x + output.first.getRectangle().getSize().x / 2 - text.getGlobalBounds().width / 2,
                         output.first.getRectangle().getPosition().y + output.first.getRectangle().getSize().y / 2 - text.getGlobalBounds().height / 2);
        _window.draw(text);
        /////////////////////////////////////////////////////////////////////// draw link
        bool isLinked = false;
        for (size_t i = 1; i < output.second.first->getNbPins(); i++) {
            isLinked = false;
            nts::IComponent *linked = output.second.first->linkedTo(i);
            for (auto &input : _inputGates) {
                if (linked == input.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(output.first.getRectangle().getPosition().x,
                                                 output.first.getRectangle().getPosition().y + output.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(input.first.getRectangle().getPosition().x + input.first.getRectangle().getSize().x,
                                                 input.first.getRectangle().getPosition().y + input.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
            for (auto &gate : _otherGates) {
                if (linked == gate.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(output.first.getRectangle().getPosition().x,
                                                 output.first.getRectangle().getPosition().y + output.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(gate.first.getRectangle().getPosition().x + gate.first.getRectangle().getSize().x,
                                                 gate.first.getRectangle().getPosition().y + gate.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
        }
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
        /////////////////////////////////////////////////////////////////////// draw text
        std::string name = gate.first.getText().getString().toAnsiString();
        sf::Font font;
        if (!font.loadFromFile("Fonts/Montserrat-Regular.ttf"))
            throw std::runtime_error("Error: Font not found");
        sf::Text text;
        text.setFont(font);
        text.setString(name);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(gate.first.getRectangle().getSize().x / 2);
        text.setPosition(gate.first.getRectangle().getPosition().x + gate.first.getRectangle().getSize().x / 2 - text.getGlobalBounds().width / 2,
                         gate.first.getRectangle().getPosition().y + gate.first.getRectangle().getSize().y / 2 - text.getGlobalBounds().height / 2);
        _window.draw(text);
        /////////////////////////////////////////////////////////////////////// draw link
        bool isLinked = false;
        for (size_t i = 1; i < gate.second.first->getNbPins(); i++) {
            isLinked = false;
            nts::IComponent *linked = gate.second.first->linkedTo(i);
            for (auto &input : _inputGates) {
                if (linked == input.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(gate.first.getRectangle().getPosition().x,
                                                 gate.first.getRectangle().getPosition().y + gate.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(input.first.getRectangle().getPosition().x + input.first.getRectangle().getSize().x,
                                                 input.first.getRectangle().getPosition().y + input.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
            for (auto &output : _outputGates) {
                if (linked == output.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(gate.first.getRectangle().getPosition().x,
                                                 gate.first.getRectangle().getPosition().y + gate.first.getRectangle().getSize().y / 2)),
                        sf::Vertex(sf::Vector2f(output.first.getRectangle().getPosition().x + output.first.getRectangle().getSize().x,
                                                 output.first.getRectangle().getPosition().y + output.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
            for (auto &gate2 : _otherGates) {
                if (linked == gate2.second.first) {
                    isLinked = true;
                    sf::Vertex line[] = {
                            sf::Vertex(sf::Vector2f(gate.first.getRectangle().getPosition().x,
                                                    gate.first.getRectangle().getPosition().y +
                                                    gate.first.getRectangle().getSize().y / 2)),
                            sf::Vertex(sf::Vector2f(
                                    gate2.first.getRectangle().getPosition().x + gate2.first.getRectangle().getSize().x,
                                    gate2.first.getRectangle().getPosition().y +
                                    gate2.first.getRectangle().getSize().y / 2))
                    };
                    line[0].color = sf::Color::Black;
                    line[1].color = sf::Color::Black;
                    _window.draw(line, 2, sf::Lines, sf::RenderStates::Default);
                    break;
                }
            }
            if (isLinked)
                continue;
        }
    }
    _window.display();
}

//////////////////////////////////////////////////////////////////////////////////

nts::SFMLGates::SFMLGates(std::string name, Type type, sf::VideoMode _videoMode, size_t size, int index, size_t allSize)
{
    int x = 0;
    int y = 10;
    this->_text = sf::Text();
    if (!_font.loadFromFile("Fonts/Montserrat-Regular.ttf")) // "Fonts/Montserrat-Regular.ttf"
        throw std::runtime_error("Error: Font not found");
    _rectangle.setSize(sf::Vector2f(((_videoMode.height / allSize) - ((_videoMode.height / allSize) / 5) - 10),
                                    ((_videoMode.height / size) - ((_videoMode.height / size) / 5)) - 10));
    if (type == INPUT) {
        x = 100;
        y += ((_videoMode.height / size) * index);
    } else if (type == GATE) {
        x = _videoMode.width / 2 - _rectangle.getSize().x / 2;
        y += (_videoMode.height / size) * index;
    } else if (type == OUTPUT) {
        x = (_videoMode.width - (_rectangle.getSize().x + 100));
        y += (_videoMode.height / size) * index;
    }
    _rectangle.setFillColor(sf::Color::White);
    _rectangle.setOutlineColor(sf::Color::Black);
    _rectangle.setOutlineThickness(2);
    _rectangle.setPosition(x, y);
    _text.setFont(_font);
    _text.setString(name);
    _text.setFillColor(sf::Color::Black);
    _text.setPosition(x + 25, y + 25);
}