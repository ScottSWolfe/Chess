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
    std::unique_ptr<Piece> getCopy() const override;
    const std::string getSymbol() const override;
    PieceType getType() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const override;
    void addAdjacentMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addCastleMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void King::addCastleMove(std::vector<Move> &moves, const GameState &state, Position start, int delta_x) const;
    void addMoveEffect(const GameState &state, Move &move) const override;
    int King::castleColumn(int direction, int dimension) const;

};
