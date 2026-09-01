#pragma once

#include "core/Piece.hpp"
#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMovePawn(const Move& move, const Position& position, Color color);
std::vector<Square> getPseudoLegalMovesPawn(const Square& square, Color color);

} // namespace chessboard
