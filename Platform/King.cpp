#include "King.h"


King::King(PieceColor color) : Piece(color) {}

const std::string King::getSymbol() const {
	return "K";
}
