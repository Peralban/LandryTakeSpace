/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "AdvancedComponents.hpp"
#include "BasicGates.hpp"
#include "SpecialComponents.hpp"

/*-----------------D FLIP FLOP-----------------*/

nts::DFlipFlop::DFlipFlop() : AdvancedComponent(6)
{
    setInput(1); // SET
    setInput(2); // DATA
    setInput(3); // CLOCK
    setInput(4); // RESET
    setOutput(5); // Q
    setOutput(6); // Q_NOT

    std::vector<IComponent *> nandGates(6);
    for (std::size_t i = 0; i < 6; i++)
        nandGates[i] = new NAndGate(3);
    std::vector<IComponent *> splitter(10);
    for (std::size_t i = 0; i < 10; i++)
        splitter[i] = new Splitter(3);

    // SET
    setInternLink(1, splitter[0], 1);
    // DATA
    setInternLink(2, splitter[1], 1);
    // CLOCK
    setInternLink(3, splitter[2], 1);
    // RESET
    setInternLink(4, splitter[3], 1);
    // Q
    setInternLink(5, splitter[9], 2);
    // Q_NOT
    setInternLink(6, splitter[8], 2);
    // all internal links are set

    for (std::size_t i = 0; i < 6; i++)
        nandGates[i]->setLink(4, splitter[i + 4], 1);
    // all nand gates outputs are linked to the splitter inputs

    // SET
    splitter[0]->setLink(2, nandGates[4], 1);
    splitter[0]->setLink(3, nandGates[0], 1);
    splitter[0]->setUnused(4);

    // DATA
    splitter[1]->setLink(2, nandGates[3], 2);
    splitter[1]->setUnused(3);
    splitter[1]->setUnused(4);

    // CLOCK
    splitter[2]->setLink(2, nandGates[1], 2);
    splitter[2]->setLink(3, nandGates[2], 2);
    splitter[2]->setUnused(4);

    // RESET
    splitter[3]->setLink(2, nandGates[1], 3);
    splitter[3]->setLink(3, nandGates[3], 3);
    splitter[3]->setLink(4, nandGates[5], 3);

    // NAndGate 0
    splitter[4]->setLink(2, nandGates[1], 1);
    splitter[4]->setUnused(3);
    splitter[4]->setUnused(4);

    // NAndGate 1
    splitter[5]->setLink(2, nandGates[0], 3);
    splitter[5]->setLink(3, nandGates[4], 2);
    splitter[5]->setLink(4, nandGates[2], 1);

    // NAndGate 2
    splitter[6]->setLink(2, nandGates[5], 2);
    splitter[6]->setLink(3, nandGates[3], 1);
    splitter[6]->setUnused(4);

    // NAndGate 3
    splitter[7]->setLink(2, nandGates[0], 2);
    splitter[7]->setLink(3, nandGates[2], 3);
    splitter[7]->setUnused(4);

    // NAndGate 4 (Q)
    // pin 2 is already used
    splitter[8]->setLink(3, nandGates[5], 1);
    splitter[8]->setUnused(4);

    // NAndGate 5 (Q_NOT)
    // pin 2 is already used
    splitter[9]->setLink(3, nandGates[4], 3);
    splitter[9]->setUnused(4);
}

/*-----------------4013-----------------*/

nts::Component4013::Component4013() : AdvancedComponent(14)
{
    setOutput(1);
    setOutput(2);
    setInput(3);
    setInput(4);
    setInput(5);
    setInput(6);
    setUnused(7);
    setInput(8);
    setInput(9);
    setInput(10);
    setInput(11);
    setOutput(12);
    setOutput(13);
    setUnused(14);

    std::vector < IComponent * > components(2);
    components[0] = new DFlipFlop();
    components[1] = new DFlipFlop();

    setInternLink(1, components[0], 5);
    setInternLink(2, components[0], 6);
    setInternLink(3, components[0], 3);
    setInternLink(4, components[0], 4);
    setInternLink(5, components[0], 2);
    setInternLink(6, components[0], 1);
    setInternLink(13, components[1], 5);
    setInternLink(12, components[1], 6);
    setInternLink(11, components[1], 3);
    setInternLink(10, components[1], 4);
    setInternLink(9, components[1], 2);
    setInternLink(8, components[1], 1);
}

/*------------------SUM COMPONENT------------------*/

nts::SumComponent::SumComponent() : AdvancedComponent(7)
{
    setInput(1);
    setInput(2);
    setOutput(3);
    setOutput(4);
    setInput(5);
    setOutput(6);
    setOutput(7);

    std::vector<IComponent *> orGates(3);
    for (std::size_t i = 0; i < 3; i++)
        orGates[i] = new OrGate();
    std::vector<IComponent *> andGates(2);
    for (std::size_t i = 0; i < 2; i++)
        andGates[i] = new AndGate();
    IComponent *notGate = new NotGate();
    IComponent *xnorGate = new XNorGate();
    std::vector<IComponent *> splitter(5);
    for (std::size_t i = 0; i < 5; i++)
        splitter[i] = new Splitter(3);

    setInternLink(1, splitter[0], 1);
    setInternLink(2, splitter[1], 1);
    setInternLink(3, splitter[2], 2);
    setInternLink(4, splitter[3], 2);
    setInternLink(5, splitter[4], 1);
    setInternLink(6, xnorGate, 3);
    setInternLink(7, orGates[1], 3);
    // all internal links are set

    // splitter[0] pin 1 is already used
    splitter[0]->setLink(2, orGates[0], 1);
    splitter[0]->setLink(3, andGates[0], 1);
    splitter[0]->setUnused(4);

    // splitter[1] pin 1 is already used
    splitter[1]->setLink(2, orGates[0], 2);
    splitter[1]->setLink(3, andGates[0], 2);
    splitter[1]->setUnused(4);

    splitter[2]->setLink(1, andGates[0], 3);
    // splitter[2] pin 2 is already used
    splitter[2]->setLink(3, orGates[1], 2);
    splitter[2]->setLink(4, orGates[2], 2);

    splitter[3]->setLink(1, orGates[0], 3);
    // splitter[3] pin 2 is already used
    splitter[3]->setLink(3, andGates[1], 2);
    splitter[3]->setLink(4, notGate, 1);

    // splitter[4] pin 1 is already used
    splitter[4]->setLink(2, andGates[1], 1);
    splitter[4]->setLink(3, xnorGate, 1);
    splitter[4]->setUnused(4);

    // andGates[0] all pins are already used

    // andGates[1] pin 1 is already used
    // andGates[1] pin 2 is already used
    andGates[1]->setLink(3, orGates[1], 1);

    // orGates[0] all pins are already used

    // orGates[1] all pins are already used

    orGates[2]->setLink(1, notGate, 2);
    // orGates[2] pin 2 is already used
    orGates[2]->setLink(3, xnorGate, 2);

    // notGates all pins are already used

    // xnorGate all pins are already used
}

/*-----------------High Speed Par Carry-----------------*/

nts::HighSpeedParCarry::HighSpeedParCarry() : AdvancedComponent(10)
{
    for (std::size_t i = 1; i <= 9; i++)
        setInput(i);
    setOutput(10);

    std::vector<IComponent *> andGates(5);
    andGates[0] = new AndGate(4);
    andGates[1] = new AndGate(2);
    andGates[2] = new AndGate(3);
    andGates[3] = new AndGate(4);
    andGates[4] = new AndGate(2);

    std::vector<IComponent *> orGates(2);
    orGates[0] = new OrGate(4);
    orGates[1] = new OrGate(2);

    std::vector<IComponent *> splitter(3);
    for (std::size_t i = 0; i < 3; i++)
        splitter[i] = new Splitter(4 - i);

    setInternLink(1, orGates[0], 1);
    setInternLink(2, splitter[0], 1);
    setInternLink(3, andGates[1], 2);
    setInternLink(4, splitter[1], 1);
    setInternLink(5, andGates[2], 3);
    setInternLink(6, splitter[2], 1);
    setInternLink(7, andGates[3], 4);
    setInternLink(8, andGates[0], 4);
    setInternLink(9, andGates[4], 1);
    setInternLink(10, orGates[1], 3);
    // all internal links are set

    // splitter[0] pin 1 is already used
    splitter[0]->setLink(2, andGates[0], 1);
    splitter[0]->setLink(3, andGates[1], 1);
    splitter[0]->setLink(4, andGates[2], 1);
    splitter[0]->setLink(5, andGates[3], 1);

    // splitter[1] pin 1 is already used
    splitter[1]->setLink(2, andGates[0], 2);
    splitter[1]->setLink(3, andGates[2], 2);
    splitter[1]->setLink(4, andGates[3], 2);

    // splitter[2] pin 1 is already used
    splitter[2]->setLink(2, andGates[0], 3);
    splitter[2]->setLink(3, andGates[3], 3);

    // andGates[0] all inputs are already used
    andGates[0]->setLink(5, andGates[4], 2);

    // andGates[1] all inputs are already used
    andGates[1]->setLink(3, orGates[0], 2);

    // andGates[2] all inputs are already used
    andGates[2]->setLink(4, orGates[0], 3);

    // andGates[3] all inputs are already used
    andGates[3]->setLink(5, orGates[0], 4);

    // andGates[4] all inputs are already used
    andGates[4]->setLink(3, orGates[1], 1);

    // orGates[0] all inputs are already used
    orGates[0]->setLink(5, orGates[1], 2);

    // orGates[1] all pins are already used
}

/*-----------------4008-----------------*/

nts::Component4008::Component4008() : AdvancedComponent(16)
{
    for (std::size_t i = 1; i <= 9; i++)
        setInput(i);
    setUnused(8);
    for (std::size_t i = 10; i <= 14; i++)
        setOutput(i);
    setInput(15);
    setUnused(16);

    std::vector<IComponent *> sumComponents(4);
    for (std::size_t i = 0; i < 4; i++)
        sumComponents[i] = new SumComponent();
    IComponent *highSpeedParCarry = new HighSpeedParCarry();
    IComponent *splitter = new Splitter(2);

    setInternLink(15, sumComponents[3], 1);
    setInternLink(1, sumComponents[3], 2);
    setInternLink(2, sumComponents[2], 1);
    setInternLink(3, sumComponents[2], 2);
    setInternLink(4, sumComponents[1], 1);
    setInternLink(5, sumComponents[1], 2);
    setInternLink(6, sumComponents[0], 1);
    setInternLink(7, sumComponents[0], 2);
    setInternLink(9, splitter, 1);
    setInternLink(10, sumComponents[0], 6);
    setInternLink(11, sumComponents[1], 6);
    setInternLink(12, sumComponents[2], 6);
    setInternLink(13, sumComponents[3], 6);
    setInternLink(14, highSpeedParCarry, 10);
    // all internal links are set

    splitter->setLink(2, highSpeedParCarry, 9);
    splitter->setLink(3, sumComponents[0], 5);

    // sumComponents[0] pin 1 is already used
    // sumComponents[0] pin 2 is already used
    sumComponents[0]->setLink(3, highSpeedParCarry, 7);
    sumComponents[0]->setLink(4, highSpeedParCarry, 8);
    // sumComponents[0] pin 5 is already used
    // sumComponents[0] pin 6 is already used
    sumComponents[0]->setLink(7, sumComponents[1], 5);

    // sumComponents[1] pin 1 is already used
    // sumComponents[1] pin 2 is already used
    sumComponents[1]->setLink(3, highSpeedParCarry, 5);
    sumComponents[1]->setLink(4, highSpeedParCarry, 6);
    // sumComponents[1] pin 5 is already used
    // sumComponents[1] pin 6 is already used
    sumComponents[1]->setLink(7, sumComponents[2], 5);

    // sumComponents[2] pin 1 is already used
    // sumComponents[2] pin 2 is already used
    sumComponents[2]->setLink(3, highSpeedParCarry, 3);
    sumComponents[2]->setLink(4, highSpeedParCarry, 4);
    // sumComponents[2] pin 5 is already used
    // sumComponents[2] pin 6 is already used
    sumComponents[2]->setLink(7, sumComponents[3], 5);

    // sumComponents[3] pin 1 is already used
    // sumComponents[3] pin 2 is already used
    sumComponents[3]->setLink(3, highSpeedParCarry, 1);
    sumComponents[3]->setLink(4, highSpeedParCarry, 2);
    // sumComponents[3] pin 5 is already used
    // sumComponents[3] pin 6 is already used
    sumComponents[3]->setUnused(7);

    // highSpeedParCarry all pins are already used
}

/*---------------Johnson Counter---------------*/

nts::JohnsonCounterHard::JohnsonCounterHard() : AComponent(7)
{
    for (std::size_t i = 1; i <= 5; i++)
        setOutput(i);
    for (std::size_t i = 6; i <= 7; i++)
        setInput(i);
    _data = 0;
}

nts::Tristate nts::JohnsonCounterHard::compute(std::size_t pin)
{
    int outputData = 0b000001111100000;
    if (isInput(pin)) {
        return getLink(pin);
    }
    if (isOutput(pin)) {
        nts::Tristate buff = getLink(6);
        if (buff == nts::Tristate::True && _stateSet[6] == 0 && getLink(7) == nts::False) {
            _data++;
            _stateSet[6] = 1;
            _state[6] = buff;
            if (_data == 10)
                _data = 0;
        }
        buff = getLink(7);
        if (buff == nts::Tristate::True) {
            _data = 0;
            _stateSet[7] = 1;
            _state[7] = buff;
            for (int i = 1; i <= 5; i++) {
                _state[i] = 0;
                _stateSet[i] = 1;
            }
        }
        if (buff == nts::Tristate::False) {
            _stateSet[7] = 1;
            _state[7] = buff;
            for (int i = 1; i <= 5; i++) {
                _state[i] = (outputData >> (_data + 5 - i)) & 1;
                _stateSet[i] = 1;
            }
        }
        if (buff == nts::Undefined) {
            for (int i = 1; i <= 5; i++) {
                _state[i] = nts::Tristate::Undefined;
                _stateSet[i] = 1;
            }
        }
        return (nts::Tristate)_state[pin];
    }
    throw nts::Error("Pin index out of range");
}

void nts::JohnsonCounterHard::clearStateSet(std::size_t pin)
{
    if (isInput(pin)) {
        _stateSet[6] = 0;
        _stateSet[7] = 0;
        for (std::size_t i = 1; i <= 5; i++) {
            clearStateSet(i);
            compute(i);
        }
    }
    if (isOutput(pin)) {
        _stateSet[pin] = 0;
        IComponent *linked = linkedTo(pin);
        if (linked == nullptr)
            return;
        linked->clearStateSet(getOtherPin(pin));
    }
}

/*-----------------Jhonson Decoder-----------------*/

nts::JohnsonDecoder::JohnsonDecoder() : AdvancedComponent(16)
{
    for (std::size_t i = 1; i <= 5; i++)
        setInput(i);
    for (std::size_t i = 6; i <= 16; i++)
        setOutput(i);

    std::vector<IComponent *> inSplitter(5);
    std::vector<IComponent *> inNotGates(5);
    for (std::size_t i = 0; i < 5; i++) {
        inSplitter[i] = new Splitter(2);
        inNotGates[i] = new NotGate();
        inSplitter[i]->setLink(3, inNotGates[i], 1);
        setInternLink(i + 1, inSplitter[i], 1);
    }

    std::vector<IComponent *> splitter(9);
    for (std::size_t i = 0; i < 9; i++)
        splitter[i] = new Splitter(2);
    splitter[0]->setLink(1, inSplitter[4], 2);
    splitter[1]->setLink(1, inNotGates[0], 2);
    splitter[2]->setLink(1, inSplitter[0], 2);
    splitter[3]->setLink(1, inNotGates[1], 2);
    splitter[4]->setLink(1, inSplitter[1], 2);
    splitter[5]->setLink(1, inNotGates[2], 2);
    splitter[6]->setLink(1, inSplitter[2], 2);
    splitter[7]->setLink(1, inNotGates[3], 2);
    splitter[8]->setLink(1, inSplitter[3], 2);
    IComponent *carrySplitter = new Splitter(3);
    carrySplitter->setLink(1, inNotGates[4], 2);

    std::vector<IComponent *> norGates(10);
    for (std::size_t i = 0; i < 10; i++) {
        norGates[i] = new NOrGate(2);
        setInternLink(i + 6, norGates[i], 3);
    }

    norGates[0]->setLink(1, splitter[0], 2);
    norGates[0]->setLink(2, splitter[2], 2);

    norGates[1]->setLink(1, splitter[4], 2);
    norGates[1]->setLink(2, splitter[1], 2);

    norGates[2]->setLink(1, splitter[3], 2);
    norGates[2]->setLink(2, splitter[6], 2);

    norGates[3]->setLink(1, splitter[8], 2);
    norGates[3]->setLink(2, splitter[5], 2);

    norGates[4]->setLink(1, splitter[0], 3);
    norGates[4]->setLink(2, splitter[7], 2);

    norGates[5]->setLink(1, splitter[1], 3);
    norGates[5]->setLink(2, carrySplitter, 2);

    norGates[6]->setLink(1, splitter[2], 3);
    norGates[6]->setLink(2, splitter[3], 3);

    norGates[7]->setLink(1, splitter[4], 3);
    norGates[7]->setLink(2, splitter[5], 3);

    norGates[8]->setLink(1, splitter[7], 3);
    norGates[8]->setLink(2, splitter[6], 3);

    norGates[9]->setLink(1, splitter[8], 3);
    norGates[9]->setLink(2, carrySplitter, 3);

    setInternLink(16, carrySplitter, 4);
}

/*-----------------4017-----------------*/

#define JDPIN(n) (n + 6)

nts::Component4017::Component4017() : AdvancedComponent(16)
{
    for (std::size_t i = 1; i <= 12; i++)
        setOutput(i);
    for (std::size_t i = 13; i <= 16; i++)
        setInput(i);
    setUnused(8);
    setUnused(16);

    IComponent *notClock = new NotGate();
    IComponent *andClock = new AndGate(2);

    setInternLink(14, andClock, 1); // CP0: Clock -> x
    setInternLink(13, notClock, 1); // CP1: EN/ -> x
    notClock->setLink(2, andClock, 2);

    IComponent *jhonsonCounter = new JohnsonCounterHard();

    andClock->setLink(3, jhonsonCounter, 6); // x -> CP
    setInternLink(15, jhonsonCounter, 7); //MR -> MR

    IComponent *jhonsonDecoder = new JohnsonDecoder();

    for (std::size_t i = 1; i <= 5; i++) {
        jhonsonCounter->setLink(i, jhonsonDecoder, i);
    }
    setInternLink(1, jhonsonDecoder, JDPIN(5));
    setInternLink(2, jhonsonDecoder, JDPIN(1));
    setInternLink(3, jhonsonDecoder, JDPIN(0));
    setInternLink(4, jhonsonDecoder, JDPIN(2));
    setInternLink(5, jhonsonDecoder, JDPIN(6));
    setInternLink(6, jhonsonDecoder, JDPIN(7));
    setInternLink(7, jhonsonDecoder, JDPIN(3));
    //pin 8 is unused
    setInternLink(9, jhonsonDecoder, JDPIN(8));
    setInternLink(10, jhonsonDecoder, JDPIN(4));
    setInternLink(11, jhonsonDecoder, JDPIN(9));
    setInternLink(12, jhonsonDecoder, JDPIN(10));
}

void nts::Component4017::clearStateSet(std::size_t pin)
{
    if (isInput(pin)) {
        if (internLinkedTo(pin) != nullptr)
            internLinkedTo(pin)->clearStateSet(getOtherInternPin(pin));
        for (std::size_t i = 1; i <= getNbPins(); i++) {
            if (isOutput(i))
                clearStateSet(i);
        }
    }
    if (isOutput(pin)) {
        _stateSet[pin] = 0;
        IComponent *linked = linkedTo(pin);
        if (linked == nullptr)
            return;
        linked->clearStateSet(getOtherPin(pin));
    }
}
