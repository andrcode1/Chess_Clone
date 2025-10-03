#pragma once

#include "chessCore.hpp"

namespace chessboard
{

class Square 
{
private:
    int file_; // 0-7 (a-h)
    int rank_; // 0-7

public:
    Square(int file, int rank) : file_(file), rank_(rank) {}
    
    static Square fromAlgebraic(const std::string& algebraicForm);
    std::string toAlgebraic() const;
    
    int file() const { return file_; }
    int rank() const { return rank_; }
    
    bool operator==(const Square& other) const { 
        return file_ == other.file_ && rank_ == other.rank_; 
    }
    bool operator!=(const Square& other) const { 
        return !(*this == other); 
    }
};

} // namespace chessboard