#include <memory>
#include <string>
#include "ChessDebug.h"
#include "Bishop.h"
#include "Board.h"
#include "Knight.h"
#include "King.h"
#include "Move.h"
#include "Pawn.h"
#include "Position.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
using namespace std;


Piece::Piece(PieceColor piece_color) : color(piece_color) {}

PieceColor Piece::getColor() const {
	return Piece::color;
}

const std::string Piece::getPieceSymbol(const Piece *piece) {
	if (piece == nullptr) {
		return " ";
	}
	else {
		return piece->getSymbol();
	}
}

PieceColor Piece::getPieceColor(const Piece *piece) {
	if (piece == nullptr) {
		return PieceColor::NO_PIECE;
	}
	else {
		return piece->getColor();
	}
}

unique_ptr<const Piece> Piece::copyPieceFactory(const Piece *piece) {
	if (!piece) {
		return nullptr;
	}
	if (dynamic_cast<const Pawn*>(piece)) {
		return make_unique<const Pawn>(piece->getColor());
	}
	if (dynamic_cast<const Bishop*>(piece)) {
		return make_unique<const Bishop>(piece->getColor());
	}
	if (dynamic_cast<const Knight*>(piece)) {
		return make_unique<const Knight>(piece->getColor());
	}
	if (dynamic_cast<const Rook*>(piece)) {
		return make_unique<const Rook>(piece->getColor());
	}
	if (dynamic_cast<const Queen*>(piece)) {
		return make_unique<const Queen>(piece->getColor());
	}
	if (dynamic_cast<const King*>(piece)) {
		return make_unique<const King>(piece->getColor());
	}
	return nullptr;
}

void Piece::getStraightMoves(vector<Move> &moves, const Board &board, Position start) const {
	getMovesInLine(moves, board, start,  1,  0);
	getMovesInLine(moves, board, start, -1,  0);
	getMovesInLine(moves, board, start,  0,  1);
	getMovesInLine(moves, board, start,  0, -1);
}

void Piece::getDiagonalMoves(vector<Move> &moves, const Board &board, Position start) const {
	getMovesInLine(moves, board, start,  1,  1);
	getMovesInLine(moves, board, start,  1, -1);
	getMovesInLine(moves, board, start, -1,  1);
	getMovesInLine(moves, board, start, -1, -1);
}

void Piece::getMovesInLine(vector<Move> &moves, const Board &board, Position start, int delta_x, int delta_y) const {
	Position end = start.add(delta_x, delta_y);
	while (board.inBounds(end) && board.isPiece(end) == false) {
		moves.push_back(Move(start, end));
		end = end.add(delta_x, delta_y);
	}
	if (board.inBounds(end) && board.isOppPieceColor(end, color)) {
		moves.push_back(Move(start, end));
	}
}
