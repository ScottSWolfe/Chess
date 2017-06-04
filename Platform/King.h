#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
struct Position;


class King : public Piece {

public:
    King(PieceColor color);
    std::unique_ptr<const Piece> getCopy() const override;
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};
