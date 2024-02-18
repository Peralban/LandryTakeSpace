/*
** EPITECH PROJECT, 2024
** LandryTakeSpace
** File description:
** No file there , just an epitech header example .
*/

#include "Test_include.hpp"

void redirect_stdin(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
    cr_redirect_stdin();
}
