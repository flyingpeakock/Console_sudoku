#include "Board.h"

Board::Board(Generator gen): playGrid(gen.getGrid()), startGrid(playGrid), solutionGrid(gen.getSolution()) {
    for (auto &array : pencilMarks) {
        for (auto &vec : array) {
            for (auto i = 0; i < 3; i++) {
                vec.push_back(' ');
            }
        }
    }

    for (auto i = 1; i <= 9; i++) {
        count.insert({i, 0});
    }
    for (auto i = 0; i < 9; i++) {
        for (auto j = 0; j < 9; j++) {
            int val = startGrid[i][j];
            if (val != 0) {
                count[val]++;
            }
        }
    }
}

void Board::startPlaying() {
    playing = true;
}

void Board::stopPlaying() {
    playing = false;
}

bool Board::isPlaying() {
    return playing;
}

bool Board::isWon() {
    if (playGrid == solutionGrid) {
        playing = false;
        return true;
    }
    return false;
}

std::array<std::array<std::vector<char>, 9>, 9> &Board::getPencilMarks() {
    return pencilMarks;
}

std::array<std::array<int, 9>, 9> &Board::getPlayGrid() {
    return playGrid;
}

std::array<std::array<int, 9>, 9> &Board::getStartGrid() {
    return startGrid;
}

std::array<std::array<int, 9>, 9> &Board::getSolution() {
    return solutionGrid;
}

void Board::insert(char val, int row, int col) {
    if (startGrid[row][col] != 0) {
        // Trying to change a correct checked square
        return;
    }

    if (val == ' ' || val == '0') {
        if (playGrid[row][col] != 0) {
            count[playGrid[row][col]]--;
            playGrid[row][col] = 0;
        }
        return;
    }

    if (val > '0' && val <= '9') {
        if (playGrid[row][col] != 0)
            count[playGrid[row][col]]--;
        count[val - '0']++;
        playGrid[row][col] = val - '0';
    }

    if (playGrid[row][col] == solutionGrid[row][col]) {
        removeMarks(val, row, col);
    }
}

void Board::pencil(char val, int row, int col) {
    auto &marks = pencilMarks[row][col];
    if (val == ' ') {
        if (marks[0] != ' ') {
            marks.erase(marks.begin());
        }
        return;
    }

    // Check if mark exists, if visible delete
    // else move to front
    int idx = 0;
    for (auto &m : marks) {
        if (m == val) {
            if (idx > 2) {
                marks.erase(marks.begin() + idx);
                marks.insert(marks.begin(), val);
            }
            else {
                marks.erase(marks.begin() + idx);
            }
            return;
        }
        idx++;
    }

    if (val > '0' && val <= '9') {
        marks.insert(marks.begin(), val);
    }
}

void Board::removeMarks(char val, int row, int col) {
    for (auto i = 0; i < 9; i++) {
        for (auto j = 0; j < pencilMarks[row][i].size(); j++) {
            auto &mark = pencilMarks[row][i];
            if (val == mark[j] && mark[j] != ' ') {
                mark.erase(mark.begin() + j);
                break;
            }
        }
        for (auto j = 0; j < pencilMarks[i][col].size(); j++) {
            auto &mark = pencilMarks[i][col];
            if (val == mark[j] && mark[j] != ' ') {
                mark.erase(mark.begin() + j);
                break;
            }
        }
    }

    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (auto i = boxRow; i < boxRow + 3; i++) {
        for (auto j = boxCol; j < boxCol + 3; j++) {
            auto &mark = pencilMarks[i][j];
            for (auto k = 0; k < mark.size(); k++) {
                if (val == mark[k] && mark[k] != ' ') {
                    mark.erase(mark.begin() + k);
                    break;
                }
            }
        }
    }
}

bool Board::isRemaining(int val) {
    if (val == 0)
        return true;
    return count[val] < 9;
}