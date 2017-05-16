#include <iostream>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Square.h"
#include "Board.h"
using namespace std;

int main() {
	cout << "Hello World of Chess!" << endl;
	cout << endl;

	// Testing Pieces
	cout << "Pieces" << endl;
	Rook rook(Color::White);
	cout << (int) rook.getColor() << endl;

	Knight knight(Color::Black);
	cout << (int) knight.getColor() << endl;

	Bishop bishop(Color::White);
	cout << (int) bishop.getColor() << endl;

	King king(Color::Black);
	cout << (int) king.getColor() << endl;

	Queen queen(Color::White);
	cout << (int) queen.getColor() << endl;

	Pawn pawn(Color::Black);
	cout << (int) pawn.getColor() << endl;
	cout << endl;

	// Testing Squares
	cout << "Squares" << endl;

	Square square1(&rook);
	cout << (int) square1.getPiece()->getColor() << endl;

	Square square2(&knight);
	cout << (int) square2.getPiece()->getColor() << endl;

	Square square3;
	if (square3.getPiece()) {
		cout << (int)square2.getPiece()->getColor() << endl;
	}
	else {
		cout << "No piece" << endl;
	}
	cout << endl;

	// Testing Board
	cout << "Board" << endl;
	int board_dimension(8);
	Board board(board_dimension);

	board.addPieceToSquare(0, 0, &rook);
	board.addPieceToSquare(1, 7, &knight);
	board.addPieceToSquare(3, 3, &bishop);
	board.addPieceToSquare(3, 0, &queen);
	board.addPieceToSquare(4, 0, &king);
	board.addPieceToSquare(0, 1, &pawn);

	board.printToConsole();
	cout << endl;

	// letting user close the application
	cout << "Type an int and press enter to finish" << endl;
	int input;
	cin >> input;
}
