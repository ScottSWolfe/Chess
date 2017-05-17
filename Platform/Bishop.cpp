#include "Piece.h"
#include "Bishop.h"

Bishop::Bishop(PieceColor color) : Piece(color) {}

std::string Bishop::getSymbol() {
	return "B";
}
