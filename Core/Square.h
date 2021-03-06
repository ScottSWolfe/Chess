#pragma once

#include <memory>
#include "Piece.h"

namespace chess {


class Square {

private:
    std::unique_ptr<Piece> piece;

public:
    Square();
    Square(std::unique_ptr<Piece> &piece);
    Square(const Square &other_square);
    Square& operator = (const Square &other);
    bool isPiece() const;
    const Piece *getPiece() const;
    void setPiece(std::unique_ptr<Piece> &new_piece);
    std::unique_ptr<Piece> removePiece();
    bool containsKing(PieceColor king_color) const;
    PieceType getPieceType() const;

private:
    std::unique_ptr<Piece> getCopyOfPiece() const;
    void throwExceptionIfPieceIsNull() const;

};


}
