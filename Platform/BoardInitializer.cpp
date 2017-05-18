#include "BoardInitializer.h"
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include <memory>
using namespace std;

unique_ptr<Board> BoardInitializer::initializeStandardGame() {
	unique_ptr<Board> board = make_unique<Board>(8);
	addStandardPieces(board.get());
	return board;
}

void BoardInitializer::addStandardPieces(Board *board) {
	const int dimension = board->getDimension();
	for (int i = 0; i < dimension; ++i) {
		Piece *pawn = new Pawn(PieceColor::WHITE);
		board->addPieceToSquare(i, 1, pawn);
	}
	for (int i = 0; i < dimension; ++i) {
		Piece *pawn = new Pawn(PieceColor::BLACK);
		board->addPieceToSquare(i, 6, pawn);
	}
}
