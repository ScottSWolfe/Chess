#include "Board.h"
#include "BoardInitializer.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
using namespace std;


Board BoardInitializer::initializeStandardSetup() {
	Board board(8);
	addStandardPieces(board);
	return board;
}

void BoardInitializer::addStandardPieces(Board &board) {
	addRowOfPawns(board, 1, PieceColor::WHITE);
	addRowOfPawns(board, 6, PieceColor::BLACK);
	addStandardRowOfPieces(board, 0, PieceColor::WHITE);
	addStandardRowOfPieces(board, 7, PieceColor::BLACK);
}

void BoardInitializer::addRowOfPawns(Board &board, int row, PieceColor color) {
	int dimension = board.getDimension();
	for (int i = 0; i < dimension; ++i) {
		unique_ptr<const Piece> pawn = make_unique<Pawn>(color);
		board.addPieceToSquare(i, row, pawn);
	}
}

void BoardInitializer::addStandardRowOfPieces(Board &board, int row, PieceColor color) {
	unique_ptr<const Piece> rook_a = make_unique<Rook>(color);
	unique_ptr<const Piece> rook_b = make_unique<Rook>(color);
	unique_ptr<const Piece> knight_a = make_unique<Knight>(color);
	unique_ptr<const Piece> knight_b = make_unique<Knight>(color);
	unique_ptr<const Piece> bishop_a = make_unique<Bishop>(color);
	unique_ptr<const Piece> bishop_b = make_unique<Bishop>(color);
	unique_ptr<const Piece> queen = make_unique<Queen>(color);
	unique_ptr<const Piece> king = make_unique<King>(color);

	board.addPieceToSquare(0, row, rook_a);
	board.addPieceToSquare(7, row, rook_b);
	board.addPieceToSquare(1, row, knight_a);
	board.addPieceToSquare(6, row, knight_b);
	board.addPieceToSquare(2, row, bishop_a);
	board.addPieceToSquare(5, row, bishop_b);
	board.addPieceToSquare(3, row, queen);
	board.addPieceToSquare(4, row, king);
}
