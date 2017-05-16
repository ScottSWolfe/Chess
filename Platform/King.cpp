#include "Piece.h"
#include "King.h"

King::King(Color color) : Piece(color) {}

std::string King::getSymbol() {
	return "K";
}
