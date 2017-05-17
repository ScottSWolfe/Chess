#include "Piece.h"
#include "King.h"

King::King(PieceColor color) : Piece(color) {}

std::string King::getSymbol() {
	return "K";
}
