#include <vector>
#include "ChessDebug.h"
#include "Bishop.h"
#include "Move.h"
using namespace std;


Bishop::Bishop(PieceColor color) : Piece(color) {}

const string Bishop::getSymbol() const {
	return BISHOP_SYMBOL;
}

vector<Move> Bishop::getMoves(const Board &board, int x, int y) const {
	vector<Move> moves;
	return moves;
}
