#include "Piece.h"
#include <string>

Piece::Piece(PieceColor color) {
	Piece::color = color;
}

PieceColor Piece::getColor() {
	return Piece::color;
}

std::string getPieceSymbol(Piece *piece) {
	if (piece == nullptr) {
		return " ";
	}
	else {
		return piece->getSymbol();
	}
}

PieceColor getPieceColor(Piece *piece) {
	if (piece == nullptr) {
		return PieceColor::WHITE;
	}
	else {
		return piece->getColor();
	}
}
