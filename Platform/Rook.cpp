#include "Piece.h"
#include "Rook.h"

Rook::Rook(Color color) : Piece(color) {}

std::string Rook::getSymbol() {
	return "R";
}
