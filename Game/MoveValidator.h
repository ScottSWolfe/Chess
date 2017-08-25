#pragma once

#include "GameState.h"
#include "Move.h"

namespace chess {

struct Position;


class MoveValidator {

public:
    MoveValidator(const GameState &state, const Move &move);
    bool validateMoveIsSafe() const;
    bool validateMoveIsLegal() const;

private:
    const GameState &state;
    const Move &move;
    bool doSquaresExist() const;
    bool doesSquareExist(Position pos) const;
    bool isPieceAtStart() const;
    bool isPieceCorrectColor() const;
    bool isDestAvailable() const;
    bool isAvailableMove() const;
    bool willKingBeInCheck() const;

};


}
