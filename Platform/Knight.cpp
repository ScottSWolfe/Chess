#include "Piece.h"
#include "Knight.h"

Knight::Knight(Color color) : Piece(color) {}

std::string Knight::getSymbol() {
	return "N";
}
