#pragma once

#include <memory>
#include "ChessEnums.h"
class Board;
class GameState;
class Move;


class Player {

public:
    Player(PieceColor color);
    virtual std::shared_ptr<Move> makeMove(const GameState &state) const = 0;

protected:
    const PieceColor color;

};
