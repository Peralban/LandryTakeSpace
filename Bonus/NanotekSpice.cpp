/*
** EPITECH PROJECT, 2024
** NanotekSpice.cpp
** File description:
** Created by Alban PERALTA et Landry GIGANT
*/

#include "NanotekSpice.hpp"
#include "SFMLModule.hpp"
#include <thread>
#include <mutex>

static void checkExistence(nts::allInputAndNameInVector Inputs, std::string src)
{
    std::string name = src.substr(0, src.find("="));
    std::string pin = src.substr(src.find("=") + 1);
    size_t i = 0;

    for (; i < Inputs.size(); i++)
        if (name == Inputs[i].second)
            break;
    if (i == Inputs.size())
        throw nts::Error("Error: '" + name + "' does not exist");
    if (pin != "1" && pin != "0" && pin != "U")
        throw nts::Error("Error: invalid value");
    if (Inputs[i].first->isUnused(2)) {
        if (Inputs[i].first->getState(1) == nts::Tristate::True)
            throw nts::Error("Error: '" + name + "' is set to True and cannot be changed");
        if (Inputs[i].first->getState(1) == nts::Tristate::False)
            throw nts::Error("Error: '" + name + "' is set to False and cannot be changed");
    }
}

static std::string getValue(nts::Tristate value)
{
    if (value == nts::Tristate::True)
        return "1";
    if (value == nts::Tristate::False)
        return "0";
    return "U";
}

static void display(nts::allInputAndNameInVector Inputs, nts::allOutputAndNameInVector Outputs, size_t tick)
{
    std::cout << "tick: " << tick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto &input : Inputs)
        std::cout << "  " << input.second << ": " << getValue(input.first->compute(1)) << std::endl;
    std::cout << "output(s):" << std::endl;
    for (auto &output : Outputs)
        std::cout << "  " << output.second << ": " << getValue(output.first->compute(1)) << std::endl;
}

static void simulate(nts::allInputAndNameInVector Inputs, nts::allOutputAndNameInVector Outputs, size_t &tick,
                     std::vector<std::pair<std::string, std::string>> &saveValue)
{
    for (auto &input : Inputs) {
        for (auto &value : saveValue) {
            if (input.second == value.first) {
                if (value.second == "1")
                    if (!input.first->isUnused(5))
                        input.first->compute(3);
                    else
                        input.first->compute(4);
                else if (value.second == "0")
                    if (!input.first->isUnused(5))
                        input.first->compute(4);
                    else
                        input.first->compute(3);
                else
                    input.first->compute(2);
            }
        }
    }
    tick++;
    for (auto &input : Inputs)
        if (!input.first->isUnused(5))
            input.first->compute(5);
    for (auto &output : Outputs) {
        output.first->compute(1);
        output.first->resetInfinityCounter();
    }
    saveValue.clear();
}

static void runSfml(nts::SFMLModule &sfmlModule)
{
    sfmlModule.createWindow();
    while (sfmlModule.getWindow().isOpen()) {
        while (sfmlModule.getWindow().pollEvent(sfmlModule.getEvent())) {
            if (sfmlModule.getEvent().type == sf::Event::Closed) {
                sfmlModule.getWindow().close();
            }
        }
        sfmlModule.getWindow().clear(sf::Color::White);
        sfmlModule.display();
    }
}

void nts::NanotekSpice::execShell(nts::SFMLModule &sfmlModule)
{
    std::string line;
    std::cout << "> ";
    while (getline(std::cin, line)) {
        if (line.empty())
            continue;
        if (line.find("=") != std::string::npos) {
            try {
                checkExistence(_inputs, line);
                _saveValue.push_back(std::make_pair(line.substr(0, line.find("=")),
                                                    line.substr(line.find("=") + 1)));
                std::cout << "> ";
                continue;
            } catch (nts::Error &e) {
                std::cerr << e.what() << std::endl;
                std::cout << "> ";
                continue;
            }
        } if (line == "display") {
            display(_inputs, _outputs, _tick);
        } else if (line == "simulate") {
            try {
                simulate(_inputs, _outputs, _tick, _saveValue);
            } catch (nts::Error &e) {
                std::cerr << e.what() << std::endl;
            }
        } else if (line == "exit") {
            exit(0);
        } else if (line == "sfml") {
            std::thread sfmlthread(&runSfml, std::ref(sfmlModule));
            sfmlthread.detach();
        } else if (line == "exit sfml") {
            sfmlModule.destroyWindow();
        } else {
            std::cerr << "Error: invalid command" << std::endl;
        }
        std::cout << "> ";
    }
}
