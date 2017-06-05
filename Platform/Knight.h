#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
struct Position;


class Knight : public Piece {

public:
    Knight(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};
