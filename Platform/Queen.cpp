#include "Piece.h"
#include "Queen.h"

Queen::Queen(PieceColor color) : Piece(color) {}

std::string Queen::getSymbol() {
	return "Q";
}
