#include "Piece.h"
#include "Queen.h"

Queen::Queen(Color color) : Piece(color) {}

std::string Queen::getSymbol() {
	return "Q";
}
