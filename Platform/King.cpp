#include <vector>
#include "ChessDebug.h"
#include "Board.h"
#include "King.h"
#include "Move.h"
#include "Position.h"
using namespace std;


King::King(PieceColor color) : Piece(color) {}

const string King::getSymbol() const {
	return KING_SYMBOL;
}

vector<Move> King::getMoves(const Board &board, Position start) const {
	vector<Move> moves;
	for (int delta_y = -1; delta_y <= 1; delta_y++) {
		for (int delta_x = -1; delta_x <= 1; delta_x++) {
			Position end = start.add(delta_x, delta_y);
			if (board.inBounds(end) &&
				(board.isPiece(end) == false || board.isOppPieceColor(end, color)))
			{
				moves.push_back(Move(start, end));
			}
		}
	}
	return moves;
}
