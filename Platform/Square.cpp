#include <iostream>
#include <string>
#include "ChessDebug.h"
#include "Pawn.h"
#include "Piece.h"
#include "Square.h"
using namespace std;


Square::Square(SquareColor square_color)
	: piece(nullptr), color(square_color)
{}

Square::Square(SquareColor square_color, unique_ptr<const Piece> &new_piece)
	: color(square_color), piece(new_piece.release())
{}

Square::Square(const Square &other_square)
	: color(other_square.color), piece(Piece::copyPieceFactory(other_square.getPiece()))
{}

const Piece *Square::getPiece() const {
	return piece.get();
}

void Square::setPiece(unique_ptr<const Piece> &new_piece) {
	piece.reset(new_piece.release());
}

unique_ptr<const Piece> Square::removePiece() {
	unique_ptr<const Piece> copy_of_piece = Piece::copyPieceFactory(piece.get());
	checkIfPieceIsNull(copy_of_piece.get());
	piece.reset();
	return copy_of_piece;
}

SquareColor Square::getColor() const {
	return color;
}

void Square::checkIfPieceIsNull(const Piece *piece) const {
	if (piece == nullptr) {
		throw invalid_argument("square does not contain a piece");
	}
}
