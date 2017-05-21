#include "Rook.h"


Rook::Rook(PieceColor color) : Piece(color) {}

const std::string Rook::getSymbol() const {
	return "R";
}
