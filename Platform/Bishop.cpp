#include <string>
#include "Bishop.h"


Bishop::Bishop(PieceColor color) : Piece(color) {}

const std::string Bishop::getSymbol() const {
	return "B";
}
