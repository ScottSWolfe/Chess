#include "Pawn.h"


Pawn::Pawn(PieceColor color) : Piece(color) {}

const std::string Pawn::getSymbol() const {
	return PAWN_SYMBOL;
}
