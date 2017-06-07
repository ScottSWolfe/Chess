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
    PieceType getType() const override; 
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

private:
    void addAdjacentMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addCastleMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addCastleMove(std::vector<Move> &moves, const GameState &state, Position start, int delta_x) const;
    std::unique_ptr<const MoveEffect> King::createCastleEffect(Position king_end, Position rook_start, int delta_x) const;
    bool canCastle(const GameState &state, Position start, int delta_x, Position &rook_position) const;
    int castleColumn(int direction, int dimension) const;

};
