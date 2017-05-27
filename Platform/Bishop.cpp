#include <string>
#include "ChessDebug.h"
#include "Bishop.h"


Bishop::Bishop(PieceColor color) : Piece(color) {}

const std::string Bishop::getSymbol() const {
	return BISHOP_SYMBOL;
}
