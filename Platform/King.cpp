#include <vector>
#include "ChessDebug.h"
#include "King.h"
#include "Move.h"
#include "Position.h"
using namespace std;


King::King(PieceColor color) : Piece(color) {}

const string King::getSymbol() const {
	return KING_SYMBOL;
}

vector<Move> King::getMoves(const Board &board, Position pos) const {
	vector<Move> moves;
	return moves;
}
