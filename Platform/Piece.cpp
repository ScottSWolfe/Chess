#include "Piece.h"

Piece::Piece(PieceColor color) {
	Piece::color = color;
}

PieceColor Piece::getColor() {
	return Piece::color;
}
