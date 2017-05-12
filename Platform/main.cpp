#include <iostream>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Square.h"
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

	// letting user close the application
	cout << "Type an int and press enter to finish" << endl;
	int input;
	cin >> input;
}
