#pragma once

#include <memory>
#include "ChessEnums.h"
class Board;
class GameState;
class PlayerAction;
class Move;


class Player {

public:
    Player(PieceColor color);
    virtual std::shared_ptr<PlayerAction> getAction(const GameState &state) const = 0;
    virtual PieceType getPromotionPiece(const GameState &state, const Move &move) const;

protected:
    const PieceColor color;

};
