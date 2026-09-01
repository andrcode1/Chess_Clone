#pragma once

#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMoveKnight(const Move& move, const Position& position);
std::vector<Square> getPseudoLegalMovesKnight(const Square& square);

} // namespace chessboard
