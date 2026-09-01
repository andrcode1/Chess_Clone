#pragma once

#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMoveRook(const Move& move, const Position& position);
std::vector<Square> getPseudoLegalMovesRook(const Square& square);

} // namespace chessboard
