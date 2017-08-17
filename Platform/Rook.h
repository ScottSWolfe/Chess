#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
class Move;
struct Position;


namespace chess {


class Rook : public Piece {

public:
    Rook(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};


}
