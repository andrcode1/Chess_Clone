#pragma once

#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMoveBishop(const Move& move, const Position& position);
std::vector<Square> getPseudoLegalMovesBishop(const Square& square);

} // namespace chessboard
