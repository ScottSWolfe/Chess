#pragma once

#include <map>
#include "Piece.h"

namespace chess {

class GameState;


class PositionRanker {

public:
    static int scorePosition(const GameState &state);
    static int rankPosition(const GameState &state);
    static int getRelativePieceValueChange(const GameState &state, const Move &move);

private:
    static int sumPieceValues(const GameState &state, PieceColor color);
    static std::map<PieceType, int> pieceValues;

};


}
