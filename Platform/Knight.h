#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class GameState;
struct Position;


class Knight : public Piece {

public:
    Knight(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

};
