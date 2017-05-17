#include "Piece.h"
#include "Pawn.h"

Pawn::Pawn(PieceColor color) : Piece(color) {}

std::string Pawn::getSymbol() {
	return "p";
}
