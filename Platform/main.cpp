#include <iostream>
#include "ChessDebug.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 
#endif
#include "windows.h"
#include "MoveInputParser.h"
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
#include "GameManager.h"
using namespace std;


int main() {
	#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

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
	Board initialized_board = BoardInitializer::initializeStandardSetup();
	presenter.displayBoard(initialized_board);
	cout << endl;


	// Testing removing piece from square and moving to another
	cout << "Moving a Piece" << endl;
	unique_ptr<const Piece> piece_to_move = initialized_board.removePieceFromSquare(0, 1);
	initialized_board.addPieceToSquare(0, 3, piece_to_move);
	presenter.displayBoard(initialized_board);
	cout << endl;


	// Test board copying
	cout << "Copy of Board" << endl;
	Board copy_of_board(initialized_board);
	presenter.displayBoard(copy_of_board);
	cout << endl;

	unique_ptr<const Piece> piece_to_move_on_copied_board = copy_of_board.removePieceFromSquare(3, 6);
	copy_of_board.addPieceToSquare(3, 4, piece_to_move_on_copied_board);

	cout << "Move piece on copied board" << endl;
	presenter.displayBoard(copy_of_board);
	cout << endl;

	cout << "Old board remains the same" << endl;
	presenter.displayBoard(initialized_board);
	cout << endl;


	// test move input parser
	cout << "Move Input Parser Test" << endl;
	MoveInputParser parser;
	shared_ptr<const Move> parsed_move = parser.parseMoveInput("A3 D5");
	cout << "A3: ";
	cout << parsed_move->getStart().x << parsed_move->getStart().y << endl;
	cout << "D5: ";
	cout << parsed_move->getEnd().x << parsed_move->getEnd().y << endl;
	cout << endl;


	// start a new game
	GameManager manager;
	manager.startGame();

	// wait for user to press any key
	system("pause");

	return 0;
}
