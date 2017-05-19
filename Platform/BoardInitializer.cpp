#include "BoardInitializer.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include <memory>
using namespace std;


unique_ptr<Board> BoardInitializer::initializeStandardGame() {
	unique_ptr<Board> board = make_unique<Board>(8);
	addStandardPieces(board.get());
	return board;
}

void BoardInitializer::addStandardPieces(Board *board) {
	addRowOfPawns(board, 1, PieceColor::WHITE);
	addRowOfPawns(board, 6, PieceColor::BLACK);
	addStandardRowOfPieces(board, 0, PieceColor::WHITE);
	addStandardRowOfPieces(board, 7, PieceColor::BLACK);
}

void BoardInitializer::addRowOfPawns(Board *board, const int row, const PieceColor color) {
	int dimension = board->getDimension();
	for (int i = 0; i < dimension; ++i) {
		Piece *pawn = new Pawn(color);
		board->addPieceToSquare(i, row, pawn);
	}
}

void BoardInitializer::addStandardRowOfPieces(Board *board, const int row, const PieceColor color) {
	Piece *rook_a = new Rook(color);
	Piece *rook_b = new Rook(color);
	Piece *knight_a = new Knight(color);
	Piece *knight_b = new Knight(color);
	Piece *bishop_a = new Bishop(color);
	Piece *bishop_b = new Bishop(color);
	Piece *queen = new Queen(color);
	Piece *king = new King(color);

	board->addPieceToSquare(0, row, rook_a);
	board->addPieceToSquare(7, row, rook_b);
	board->addPieceToSquare(1, row, knight_a);
	board->addPieceToSquare(6, row, knight_b);
	board->addPieceToSquare(2, row, bishop_a);
	board->addPieceToSquare(5, row, bishop_b);
	board->addPieceToSquare(3, row, queen);
	board->addPieceToSquare(4, row, king);
}
