#pragma once

#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMoveQueen(const Move& move, const Position& position);
std::vector<Square> getPseudoLegalMovesQueen(const Square& square);

} // namespace chessboard
