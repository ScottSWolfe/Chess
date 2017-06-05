#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class GameState;
class Move;
struct Position;


class Queen : public Piece {

public:
    Queen(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};
