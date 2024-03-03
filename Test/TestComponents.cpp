/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../GatesComponents.hpp"
#include "../SpecialComponents.hpp"
#include "../AdvancedComponents.hpp"
#include <fstream>
#include <bitset>
#include <sstream>
#include <cstdio>

Test(component4001, NOR_gate)
{
    nts::IComponent *component = new nts::Component4001();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(1, inputs[1], 1);
    component->setLink(2, inputs[2], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(8, inputs[8], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(12, inputs[12], 1);
    component->setLink(13, inputs[13], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::True);
    cr_assert_eq(component->compute(4), nts::Tristate::True);
    cr_assert_eq(component->compute(10), nts::Tristate::True);
    cr_assert_eq(component->compute(11), nts::Tristate::True);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2 + 1]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);
}

Test(component4011, NAND_gate)
{
    nts::IComponent *component = new nts::Component4011();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(1, inputs[1], 1);
    component->setLink(2, inputs[2], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(8, inputs[8], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(12, inputs[12], 1);
    component->setLink(13, inputs[13], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::True);
    cr_assert_eq(component->compute(4), nts::Tristate::True);
    cr_assert_eq(component->compute(10), nts::Tristate::True);
    cr_assert_eq(component->compute(11), nts::Tristate::True);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::True);
    cr_assert_eq(component->compute(4), nts::Tristate::True);
    cr_assert_eq(component->compute(10), nts::Tristate::True);
    cr_assert_eq(component->compute(11), nts::Tristate::True);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2 + 1]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::True);
    cr_assert_eq(component->compute(4), nts::Tristate::True);
    cr_assert_eq(component->compute(10), nts::Tristate::True);
    cr_assert_eq(component->compute(11), nts::Tristate::True);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);
}

Test(component4030, XOR_gate)
{
    nts::IComponent *component = new nts::Component4030();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(1, inputs[1], 1);
    component->setLink(2, inputs[2], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(8, inputs[8], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(12, inputs[12], 1);
    component->setLink(13, inputs[13], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::False);
    cr_assert_eq(component->compute(4), nts::Tristate::False);
    cr_assert_eq(component->compute(10), nts::Tristate::False);
    cr_assert_eq(component->compute(11), nts::Tristate::False);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(3);

    cr_assert_eq(component->compute(3), nts::Tristate::True);
    cr_assert_eq(component->compute(4), nts::Tristate::True);
    cr_assert_eq(component->compute(10), nts::Tristate::True);
    cr_assert_eq(component->compute(11), nts::Tristate::True);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2 + 1]->compute(2);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);

    for (int i = 0; i < 100; i++)
        inputs[i - i % 2]->compute(4);

    cr_assert_eq(component->compute(3), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(4), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(10), nts::Tristate::Undefined);
    cr_assert_eq(component->compute(11), nts::Tristate::Undefined);
}

Test(component4008, four_bits_adder)
{
    nts::IComponent *component = new nts::Component4008();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(1, inputs[1], 1);
    component->setLink(2, inputs[2], 1);
    component->setLink(3, inputs[3], 1);
    component->setLink(4, inputs[4], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(7, inputs[7], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(15, inputs[15], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);

    cr_assert(1);
}

Test(component4013, dual_flip_flop)
{
    nts::IComponent *component = new nts::Component4013();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(3, inputs[3], 1);
    component->setLink(4, inputs[4], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(8, inputs[8], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(10, inputs[10], 1);
    component->setLink(11, inputs[11], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);

    cr_assert(1);
}

Test(component4017, ten_bits_jhonson_counter)
{
    nts::IComponent *component = new nts::Component4017();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(13, inputs[13], 1);
    component->setLink(14, inputs[14], 1);
    component->setLink(15, inputs[15], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);

    inputs[13]->compute(4);
    inputs[14]->compute(4);

    cr_assert_eq(component->compute(1), nts::Tristate::False);
    cr_assert_eq(component->compute(2), nts::Tristate::False);
    cr_assert_eq(component->compute(3), nts::Tristate::True);
}

Test(component4040, twelve_bits_counter)
{
    nts::IComponent *component = new nts::Component4040();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(10, inputs[10], 1);
    component->setLink(11, inputs[11], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);

    inputs[10]->compute(4);

    cr_assert_eq(component->compute(1), nts::Tristate::False);
    cr_assert_eq(component->compute(9), nts::Tristate::True);

    inputs[10]->compute(3);
    inputs[10]->compute(4);
    component->resetInfinityCounter();

    cr_assert_eq(component->compute(1), nts::Tristate::False);
    cr_assert_eq(component->compute(9), nts::Tristate::False);

    inputs[11]->compute(4);

    cr_assert_eq(component->compute(1), nts::Tristate::False);
    cr_assert_eq(component->compute(9), nts::Tristate::False);
}

Test(component4512, eight_bits_selector)
{
    nts::IComponent *component = new nts::Component4512();
    std::vector<nts::IComponent *> inputs(100);
    for (int i = 0; i < 100; i++)
        inputs[i] = new nts::InputComponent;
    component->setLink(1, inputs[1], 1);
    component->setLink(2, inputs[2], 1);
    component->setLink(3, inputs[3], 1);
    component->setLink(4, inputs[4], 1);
    component->setLink(5, inputs[5], 1);
    component->setLink(6, inputs[6], 1);
    component->setLink(7, inputs[7], 1);
    component->setLink(9, inputs[9], 1);
    component->setLink(10, inputs[10], 1);
    component->setLink(11, inputs[11], 1);
    component->setLink(12, inputs[12], 1);
    component->setLink(13, inputs[13], 1);

    for (int i = 0; i < 100; i++)
        inputs[i]->compute(2);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(4);
    for (int i = 0; i < 100; i++)
        inputs[i]->compute(3);
}

Test(Logger, logger)
{
    nts::IComponent *component = new nts::Logger();
    std::vector<nts::IComponent *> True(6);
    std::vector<nts::IComponent *> False(4);
    for (int i = 0; i < 6; i++)
        True[i] = new nts::TrueComponent;
    for (int i = 0; i < 4; i++)
        False[i] = new nts::FalseComponent;
    component->setLink(1, True[0], 1);
    component->setLink(2, True[1], 1);
    component->setLink(3, True[2], 1);
    component->setLink(4, True[3], 1);
    component->setLink(5, False[0], 1);
    component->setLink(6, True[4], 1);
    component->setLink(7, False[1], 1);
    component->setLink(8, False[2], 1);
    component->setLink(9, True[5], 1);
    component->setLink(10, False[3], 1);

    component->compute(696969);
    std::ifstream file("log.bin");
    if (!file.is_open())
        cr_assert(0);
    std::string line;
    std::getline(file, line);

    std::bitset<8> bitset("00101111");
    char c = (char) bitset.to_ulong();
    std::string str(1, c);
    cr_assert_str_eq(line.c_str(), str.c_str());
    if (remove("log.bin") != 0)
        std::cout << "Error deleting file" << std::endl;
    else
        std::cout << "File successfully deleted" << std::endl;
}