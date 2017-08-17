#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ChessEnums.h"
class Board;
class GameState;
class Move;
struct Position;

namespace chess {


class Piece {

public:
    Piece(PieceColor color);
    virtual std::unique_ptr<Piece> getCopy() const = 0;
    PieceColor getColor() const;
    virtual PieceType getType() const = 0;
    virtual const std::string getSymbol() const = 0;
    virtual std::vector<Move> getAvailableMoves(const GameState &state, Position pos) const;
    virtual std::vector<Position> getSquaresAttacked(const Board &board, Position pos) const = 0;
    bool canPieceMakeMove(const GameState &state, Position pos) const;
    virtual void addMoveEffect(const GameState &state, Move &move) const = 0;
    void setHasMoved(bool has_moved);
    bool hasMoved() const;

    static std::unique_ptr<Piece> createPiece(PieceType type, PieceColor color);
    static std::unique_ptr<Piece> copyPiece(const Piece *piece);
    static const std::string getPieceSymbol(const Piece *piece);
    static PieceColor getPieceColor(const Piece *piece);

    static const std::string PAWN_SYMBOL;
    static const std::string ROOK_SYMBOL;
    static const std::string BISHOP_SYMBOL;
    static const std::string KNIGHT_SYMBOL;
    static const std::string QUEEN_SYMBOL;
    static const std::string KING_SYMBOL;

protected:
    const PieceColor color;
    bool has_moved;

    void getStraightSquaresAttacked(std::vector<Position> &positions, const Board &board, Position start) const;
    void getDiagonalSquaresAttacked(std::vector<Position> &positions, const Board &board, Position start) const;
    void getSquaresAttackedInLine(std::vector<Position> &positions, const Board &board, Position start, int delta_x, int delta_y) const;

};


}
