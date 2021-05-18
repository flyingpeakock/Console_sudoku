#pragma once
#include "Solver.h"

class Generator {
    private:
        std::array<std::array<int, 9>, 9> grid;
        Solver solver;

    public:
        Generator();
        Generator(int maxUnknowns);
        Generator(const char *gridString);
        std::array<std::array<int, 9>, 9> getGrid();
        std::array<std::array<int, 9>, 9> getSolution();
};