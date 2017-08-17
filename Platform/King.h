#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class GameState;
struct Position;

namespace chess {


class King : public Piece {

public:
    King(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override; 
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position start) const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

private:
    std::vector<Position> getAdjacentSquaresAttacked(const Board &board, Position start) const;
    void addAdjacentMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addCastleMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addCastleMove(std::vector<Move> &moves, const GameState &state, Position start, int delta_x) const;
    Move createMoveWithCastleEffect(Position king_start, Position king_end, Position rook_start, int delta_x) const;
    bool canCastle(const GameState &state, Position start, int delta_x, Position &rook_position) const;
    int castleColumn(int direction, int dimension) const;
    int castleDirection(int start, int end) const;

};


}
