#include "ChessDebug.h"
#include "Knight.h"


Knight::Knight(PieceColor color) : Piece(color) {}

const std::string Knight::getSymbol() const {
	return KNIGHT_SYMBOL;
}
