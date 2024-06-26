/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "Test_include.hpp"
#include "../ParseFile.hpp"


//.chipsets:
//input in_1
//input in_2
//output out
//and gate
//
//.links:
//in_1:1 gate:1
//in_2:1 gate:2
//out:1 gate:3
//Templates/and.nts

Test(Parsing, Parsing)
{
    nts::ParseFile parsing;
    int ac = 2;
    try {
        parsing.setFileName("Test/Templates/waouh.nts");
        parsing.fileInVector();
    } catch (nts::Error &e) {
        ac = 0;
    }
    cr_assert_eq(ac, 0);
}

Test(Parsing, Parsing2)
{
    nts::ParseFile parsing;
    int ac = 2;
    try {
        parsing.setFileName("Test/Templates/and.nts");
        parsing.fileInVector();
    } catch (nts::Error &e) {
        ac = 0;
    }
    cr_assert_eq(ac, 2);
}

Test(Parsing, Parsing3)
{
    nts::ParseFile parsing;
    int ac = 2;
    try {
        parsing.setFileName("Test/Templates/and.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac = 0;
    }
    ac = parsing.getNbInput() + parsing.getNbOutput();
    cr_assert_eq(ac, 3);
}

Test(Parsing, Parsing4)
{
    nts::ParseFile parsing;
    int ac = 2;
    try {
        parsing.setFileName("Test/Templates/and.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac = 0;
    }
    if ((parsing.getComponents())[0].second == "input")
        ac++;
    if ((parsing.getComponents())[1].second == "input")
        ac++;
    if ((parsing.getComponents())[2].second == "output")
        ac++;
    if ((parsing.getComponents())[3].second == "and")
        ac++;
    cr_assert_eq(ac, 2);
}

//.chipsets:
//input in_1
//input in_2
//xor gate
//
//.links:
//in_1:1 gate:1
//in_2:1 gate:2
//gate:3 in_1:1
// Templates/exemple6.nts (error no output)

Test(Parsing, Parsing5)
{
    nts::ParseFile parsing;
    std::string ac = "No output found";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/exemple6.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

//.chipsets:
//xor gate
//
//.links:
//in_1:1 gate:1
//in_2:1 gate:2
// Templates/exemple7.nts (error no input and output)

Test(Parsing, Parsing6)
{
    nts::ParseFile parsing;
    std::string ac = "No input and output found";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/exemple7.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

//.chipsets:
//input in_1
//input in_2
//output out
//
//.links:
//in_1o:1 gate:1
//in_2:1 gate:2
//out:1 gate:3
// Templates/exemple8.nts (unknown component in_1o)

Test(Parsing, Parsing7)
{
    nts::ParseFile parsing;
    std::string ac = "Unknow component name 'in_1o'";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/exemple8.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

Test(Parsing, Parsing8)
{
    nts::ParseFile parsing;
    nts::IComponent *Acomponent;
    nts::IComponent *Bcomponent;
    int ac = 1;
    try {
        parsing.setFileName("Test/Templates/and.nts");
        parsing.fileInVector();
        parsing.parseData();
        parsing.linkComponents();
    } catch (nts::Error &e) {
        ac = 0;
    }
    Acomponent = (parsing.getComponents())[0].first;
    Bcomponent = (parsing.getComponents())[3].first;
    if (Acomponent->linkedTo(1) == Bcomponent && Bcomponent->linkedTo(1) == Acomponent)
        ac++;
    cr_assert_eq(ac, 2);
}

Test(Parsing, Parsing9)
{
    nts::ParseFile parsing;
    std::string ac = "Other pin index out of range";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/xor.nts");
        parsing.fileInVector();
        parsing.parseData();
        parsing.linkComponents();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_eq(ac, ac2);
}
Test(Parsing, Parsing10)
{
    nts::ParseFile parsing;
    std::string ac = "Pin index out of range";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/not.nts");
        parsing.fileInVector();
        parsing.parseData();
        parsing.linkComponents();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_eq(ac, ac2);
}

Test(Parsing, Parsing11)
{
    nts::ParseFile parsing;
    std::string ac = "Unknow component name 'ouioui'";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/clock.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

Test(Parsing, Parsing12)
{
    nts::ParseFile parsing;
    std::string ac = "Invalid line";
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/false.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

Test(Parsing, allcomp)
{
    nts::ParseFile parsing;
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/all.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    int ac3 = parsing.getNbComponents();
    cr_assert_eq(ac3, 34);
}

Test(Parsing, allcomp2)
{
    nts::ParseFile parsing;
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/wtf.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    std::string ac = "Invalid line";
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

Test(Parsing, allcomp3)
{
    nts::ParseFile parsing;
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/wtf2.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    std::string ac = "Invalid line";
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}

Test(Parsing, allcomp4)
{
    nts::ParseFile parsing;
    std::string ac2;
    try {
        parsing.setFileName("Test/Templates/wtf3.nts");
        parsing.fileInVector();
        parsing.parseData();
    } catch (nts::Error &e) {
        ac2 = e.what();
    }
    std::string ac = "Name already use";
    cr_assert_str_eq(ac.c_str(), ac2.c_str());
}