#pragma once

#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"

namespace chess {

class GameState;
class Move;
struct Position;


class Queen : public Piece {

public:
    Queen(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};


}
