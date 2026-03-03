#include "chess/game/Game.hpp"
#include "chess/core/Position.hpp"
#include "chess/exceptions/IllegalMoveException.hpp"
#include <iostream>

namespace chessboard
{
    void Game::playMove(const Move& move) {
        if (result_ != GameResult::IN_PROGRESS) {
            return;
        }
        auto& currentPosition = getViewedPosition();
        Position newPosition = currentPosition.makeMove(move);
        if (viewedPositionIndex_ < positionHistory_.size()) {
            positionHistory_.erase(positionHistory_.begin() + viewedPositionIndex_ + 1, positionHistory_.end());
        }
        positionHistory_.push_back(newPosition);
        goForward();

        Color justMoved = currentPosition.getSideToMove();
        Color nextToMove = newPosition.getSideToMove();
        if (newPosition.isCheckmate(nextToMove)) {
            result_ = (justMoved == Color::WHITE) ? GameResult::WHITE_WIN : GameResult::BLACK_WIN;
        } else if (newPosition.isDraw() || isDrawByThreefoldRepetition(newPosition)) {
            result_ = GameResult::DRAW;
        }
    }

    bool Game::isDrawByThreefoldRepetition(Position newPosition) {
        std::string boardOfPosition = newPosition.getBoardFEN();
        if (auto position = positionCounts_.find(boardOfPosition); position != positionCounts_.end()) {
            position->second++;
            if (position->second >= 3) {
                return true;
            }
        } else {
            positionCounts_.insert({boardOfPosition, 1});
        }
        return false;
    }
    void Game::goToMove(int moveIndex) {
        viewedPositionIndex_ = moveIndex + 1;
    }
    void Game::goForward() {
        viewedPositionIndex_++;
    }
    void Game::goBack() {
        viewedPositionIndex_--;
    }
    Position& Game::getViewedPosition() {
        return positionHistory_[viewedPositionIndex_];
    }

    Position& Game::getCurrentPosition() {
        return positionHistory_.back();
    }

} // namespace chessboard