#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class GameState;
class Move;
struct Position;


class Pawn : public Piece {

public:
    Pawn(PieceColor color);
    std::unique_ptr<Piece> getCopy() const override;
    PieceType getType() const override;
    const std::string getSymbol() const override;
    std::vector<Move> getAvailableMoves(const GameState &state, Position start) const override;
    std::vector<Position> getSquaresAttacked(const Board &board, Position start) const override;
    void addMoveEffect(const GameState &state, Move &move) const override;

private:
    void addOneSquareMove(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addTwoSquareMove(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addDiagonalMoves(std::vector<Move> &moves, const GameState &state, Position start) const;
    void addDiagonalMove(std::vector<Move> &moves, const GameState &state, Position start, int delta_x) const;
    void addEnPassantMove(std::vector<Move> &moves, const GameState state, Position start) const;
    bool isEnPassantAvailable(const GameState &state, Position start, int &dst_delta_x) const;
    bool addEnPassantMoveEffect(const GameState &state, Move &move) const;
    bool addPromotionMoveEffect(const GameState &state, Move &move) const;
    Move Pawn::createMoveWithEnPassant(Position start, int delta_x) const;
    int step() const;
    int startRow(int dimension) const;
    int enPassantRow(int dimension) const;
    int promotionRow(int dimension) const;

};
