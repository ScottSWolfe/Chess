#include "Piece.h"
#include "Pawn.h"

Pawn::Pawn(Color color) : Piece(color) {}

std::string Pawn::getSymbol() {
	return "p";
}
