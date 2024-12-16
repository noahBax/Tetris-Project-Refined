// tetris_rules.hpp
#ifndef TETRIS_RULES_HPP
#define TETRIS_RULES_HPP

#include <vector>
#include <array>

constexpr int NUMBER_PIECES = 7;
constexpr auto BLANK_SPACE = 7;

constexpr int BOARD_HEIGHT = 20;
constexpr int BOARD_WIDTH = 10;

using TetrisBoard = std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT>;
using Matrix = std::vector<std::vector<int>>;

#endif // TETRIS_RULES_HPP