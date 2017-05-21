#include "Queen.h"


Queen::Queen(PieceColor color) : Piece(color) {}

const std::string Queen::getSymbol() const {
	return QUEEN_SYMBOL;
}
