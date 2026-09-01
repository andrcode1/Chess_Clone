#pragma once

#include "core/Piece.hpp"
#include "core/api/Move.hpp"
#include "core/api/Position.fwd.hpp"
#include <vector>

namespace chessboard
{

bool isPseudoLegalMove(Piece piece, const Move& move, const Position& position);
std::vector<Square> getPseudoLegalMoves(Piece piece, const Square& square);

} // namespace chessboard
