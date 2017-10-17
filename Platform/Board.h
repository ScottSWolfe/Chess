#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Square.h"

namespace chess {

class GameState;
class MoveEffect;
class Piece;
class PieceIterator;
struct Position;


class Board {

public:
    Board(int board_dimension);
    Board(const Board &other_board);
    std::shared_ptr<Board> getCopy() const;
    bool inBounds(Position pos) const;
    bool hasPieceMoved(Position pos) const;
    void makeMove(const Move &move);
    void addPieceToSquare(Position pos, std::unique_ptr<Piece> &piece);
    std::unique_ptr<Piece> removePieceFromSquare(Position pos);
    bool isPiece(Position pos) const;
    const Piece *getPiece(Position pos) const;
    PieceColor getPieceColor(Position pos) const;
    std::string getPieceSymbol(Position pos) const;
    PieceType getPieceType(Position pos) const;
    bool isOppPieceColor(Position pos, PieceColor color) const;
    void setPiece(Position pos, std::unique_ptr<Piece> &piece);
    bool isKingInCheck(PieceColor king_color) const;
    bool canPieceAttackSquare(Position pos, PieceColor color) const;
    int getDimension() const;
    PieceIterator getPieceIterator(PieceColor color) const;


private:
    const int dimension;
    std::vector<Square> squares;

    Square &getSquare(Position pos);
    const Square &getSquare(Position pos) const;
    int getIndex(Position pos) const;
    Position getPosition(int index) const;
    void applyMoveEffect(const MoveEffect *effect);
    Position getKingPosition(PieceColor king_color) const;

};


}
