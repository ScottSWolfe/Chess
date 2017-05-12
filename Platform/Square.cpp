#include "Square.h"

Square::Square() : piece(nullptr) {}

Square::Square(Piece *new_piece) : piece(new_piece) {}

Piece *Square::getPiece() {
	return piece;
}
