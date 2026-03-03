#include <vector>
#include <unordered_map>
#include "chess/core/Position.hpp"
#include "chess/core/Move.hpp"
#include "chess/core/Enums.hpp"

namespace chessboard
{

class Game {
private:
    std::vector<Position> positionHistory_;
    std::unordered_map<std::string, int> positionCounts_;
    std::vector<Move> moveHistory_;
    int viewedPositionIndex_;
    GameResult result_;

public:
    Game(const Position& startingPosition)
        : viewedPositionIndex_(0), result_(GameResult::IN_PROGRESS)
    {
        positionHistory_.push_back(startingPosition);
    }

    void playMove(const Move& move);
    bool isDrawByThreefoldRepetition(Position newPosition);
    void goToMove(int moveIndex);
    void goForward();
    void goBack();
    Position& getViewedPosition();
    Position& getCurrentPosition();
    GameResult getResult() const { return result_; }
    bool isOver() const { return result_ != GameResult::IN_PROGRESS; }
};

} // namespace chessboard