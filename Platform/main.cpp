#include <iostream>
#include "ChessEnums.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "BoardInitializer.h"
#include "windows.h"
using namespace std;


int main() {
	cout << "Hello World of Chess!" << endl;
	cout << endl;

	// Testing Pieces
	cout << "Pieces" << endl;
	unique_ptr<const Piece> rook = make_unique<Rook>(PieceColor::WHITE);
	cout << static_cast<int>(rook->getColor()) << endl;

	unique_ptr<const Piece> knight(new Knight(PieceColor::BLACK));
	cout << static_cast<int>(knight->getColor()) << endl;

	unique_ptr<const Piece> bishop(new Bishop(PieceColor::WHITE));
	cout << static_cast<int>(bishop->getColor()) << endl;

	unique_ptr<const Piece> king(new King(PieceColor::BLACK));
	cout << static_cast<int>(king->getColor()) << endl;

	unique_ptr<const Piece> queen(new Queen(PieceColor::WHITE));
	cout << static_cast<int>(queen->getColor()) << endl;

	unique_ptr<const Piece> pawn(new Pawn(PieceColor::BLACK));
	cout << static_cast<int>(pawn->getColor()) << endl;
	cout << endl;

	// Testing Squares
	cout << "Squares" << endl;

	Square square1(SquareColor::DARK, rook);
	cout << (int) square1.getPiece()->getColor() << endl;

	Square square2(SquareColor::LIGHT, knight);
	cout << (int) square2.getPiece()->getColor() << endl;

	Square square3(SquareColor::DARK);
	if (square3.getPiece()) {
		cout << (int) square3.getPiece()->getColor() << endl;
	}
	else {
		cout << "No piece" << endl;
	}
	cout << endl;

	// Testing Board
	cout << "Board" << endl;
	int board_dimension(8);
	Board board(board_dimension);
	
	board.addPieceToSquare(1, 0, rook);
	board.addPieceToSquare(1, 7, knight);
	board.addPieceToSquare(3, 3, bishop);
	board.addPieceToSquare(3, 0, queen);
	board.addPieceToSquare(4, 0, king);
	board.addPieceToSquare(0, 1, pawn);
	
	ConsoleBoardPresenter presenter;
	presenter.displayBoard(board);
	cout << endl;

	// Testing BoardInitialization
	cout << "Board Initialization" << endl;
	unique_ptr<Board> new_board = BoardInitializer::initializeStandardSetup();
	presenter.displayBoard(*new_board);
	cout << endl;
	
	system("pause");

	return 0;
}
