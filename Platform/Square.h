#pragma once

#include <memory>
#include "ChessEnums.h"
#include "Piece.h"


class Square {

public:
    Square(SquareColor color);
    Square(SquareColor color, std::unique_ptr<Piece> &piece);
    Square(const Square &other_square);
    const Piece *getPiece() const;
    void setPiece(std::unique_ptr<Piece> &new_piece);
    std::unique_ptr<Piece> removePiece();
    bool containsKing(PieceColor color) const;
    SquareColor getColor() const;

private:
    const SquareColor color;
    std::unique_ptr<Piece> piece;
    std::unique_ptr<Piece> getCopyOfPiece() const;
    void throwExceptionIfPieceIsNull(const Piece *piece) const;

};
