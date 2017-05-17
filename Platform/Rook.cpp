#include "Piece.h"
#include "Rook.h"

Rook::Rook(PieceColor color) : Piece(color) {}

std::string Rook::getSymbol() {
	return "R";
}
