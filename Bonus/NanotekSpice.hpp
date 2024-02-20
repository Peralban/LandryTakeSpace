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
    class NanotekSpice {
    public:
        NanotekSpice(nts::allInputAndNameInVector Inputs, nts::allOutputAndNameInVector Outputs) :
            _inputs(Inputs), _outputs(Outputs), _tick(0) {}
        ~NanotekSpice() = default;
        void execShell(nts::SFMLModule &sfmlModule);
    private:
        std::vector<std::pair<std::string, std::string>> _saveValue;
        nts::allInputAndNameInVector _inputs;
        nts::allOutputAndNameInVector _outputs;
        size_t _tick;
    };
}