/*
** EPITECH PROJECT, 2024
** NanotekSpice.hpp
** File description:
** Created by Alban PERALTA et Landry GIGANT
*/

#pragma once

#include "ParseFile.hpp"
#include "SFMLModule.hpp"

namespace nts {
    enum CMDTYPE {
        KNOWN,
        UNKOWN
    };

    class NanotekSpice {
    public:
        NanotekSpice(nts::allInputAndNameInVector Inputs,
                     nts::allOutputAndNameInVector Outputs, nts::componentAndNameInVector Components) :
                _inputs(Inputs), _outputs(Outputs), _components(Components), _tick(0) {}
        ~NanotekSpice() = default;
        void execShell(nts::SFMLModule &sfmlModule);
        void resetAllInfinitCounter();
    private:
        std::vector<std::pair<std::string, std::string>> _saveValue;
        nts::allInputAndNameInVector _inputs;
        nts::allOutputAndNameInVector _outputs;
        nts::componentAndNameInVector _components;
        size_t _tick;
    };
}