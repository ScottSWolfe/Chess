#include "Piece.h"

Piece::Piece(Color color) {
	Piece::color = color;
}

Color Piece::getColor() {
	return Piece::color;
}
