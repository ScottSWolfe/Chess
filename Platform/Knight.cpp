#include "Piece.h"
#include "Knight.h"

Knight::Knight(PieceColor color) : Piece(color) {}

std::string Knight::getSymbol() {
	return "N";
}
