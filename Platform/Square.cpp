#include <iostream>
#include <string>
#include "ChessDebug.h"
#include "King.h"
#include "Piece.h"
#include "Square.h"
using namespace std;


Square::Square(SquareColor square_color)
    : piece(nullptr), color(square_color)
{}

Square::Square(SquareColor square_color, unique_ptr<Piece> &new_piece)
    : color(square_color), piece(new_piece.release())
{}

Square::Square(const Square &other_square)
    : color(other_square.color), piece(other_square.getCopyOfPiece())
{}

const Piece *Square::getPiece() const {
    return piece.get();
}

void Square::setPiece(unique_ptr<Piece> &new_piece) {
    piece.reset(new_piece.release());
}

unique_ptr<Piece> Square::removePiece() {
    unique_ptr<Piece> copy_of_piece = piece->getCopy();
    piece.reset();
    return copy_of_piece;
}

bool Square::containsKing(PieceColor color) const {
    if (piece == nullptr) {
        return false;
    }
    if (piece->getSymbol() != Piece::KING_SYMBOL) {
        return false;
    }
    if (color != piece->getColor()) {
        return false;
    }
    return true;
}

unique_ptr<Piece> Square::getCopyOfPiece() const {
    return Piece::copyPiece(piece.get());
}

SquareColor Square::getColor() const {
    return color;
}

void Square::throwExceptionIfPieceIsNull(const Piece *piece) const {
    if (piece == nullptr) {
        throw invalid_argument("square does not contain a piece");
    }
}
