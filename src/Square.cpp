#include "../include/Square.hpp"

namespace chessboard
{
    Square Square::fromAlgebraic(const std::string& algebraicForm) {
        char fileChar = algebraicForm[0];
        char rankChar = algebraicForm[1];

        int file = fileChar - 'a';
        int rank = rankChar - '1';

        return Square(file, rank);
    }
    std::string Square::toAlgebraic() const {
        static const char files[] = {'a','b','c','d','e','f','g','h'};
        return std::string(1, files[file_]) + std::to_string(rank_ + 1);
    }
}