#include <iostream>
#include <string>
#include "ChessDebug.h"
#include "King.h"
#include "Piece.h"
#include "Square.h"

namespace chess {


Square::Square()
    : piece(nullptr)
{}

Square::Square(std::unique_ptr<Piece> &piece)
    : piece(std::move(piece))
{}

Square::Square(const Square &other_square)
    : piece(other_square.getCopyOfPiece())
{}

Square& Square::operator=(const Square &other) {
    return Square(other);
}

const Piece *Square::getPiece() const {
    return piece.get();
}

void Square::setPiece(std::unique_ptr<Piece> &new_piece) {
    piece = std::move(new_piece);
}

std::unique_ptr<Piece> Square::removePiece() {
    throwExceptionIfPieceIsNull();
    return std::move(piece);
}

bool Square::isPiece() const {
    if (piece == nullptr) {
        return false;
    }
    return true;
}

bool Square::containsKing(PieceColor king_color) const {
    if (piece == nullptr) {
        return false;
    }
    if (piece->getType() != PieceType::KING) {
        return false;
    }
    if (king_color != piece->getColor()) {
        return false;
    }
    return true;
}

bool Square::hasPieceMoved() const {
    if (piece == nullptr) {
        return false;
    }
    return piece->hasMoved();
}

std::unique_ptr<Piece> Square::getCopyOfPiece() const {
    return Piece::copyPiece(piece.get());
}

PieceType Square::getPieceType() const {
    throwExceptionIfPieceIsNull();
    return piece->getType();
}

void Square::throwExceptionIfPieceIsNull() const {
    if (piece == nullptr) {
        throw std::runtime_error("square does not contain a piece");
    }
}


}
