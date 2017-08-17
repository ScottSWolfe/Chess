#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class GameState;
struct Position;

namespace chess {


class Bishop : public Piece {

public:
    Bishop(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    const std::string getSymbol() const override;
    PieceType getType() const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};


}
