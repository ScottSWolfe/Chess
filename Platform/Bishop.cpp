#include "Piece.h"
#include "Bishop.h"

Bishop::Bishop(Color color) : Piece(color) {}

std::string Bishop::getSymbol() {
	return "B";
}
