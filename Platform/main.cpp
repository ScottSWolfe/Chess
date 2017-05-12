#include <iostream>
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
using namespace std;

int main() {
	cout << "Hello World of Chess!" << endl;

	Rook rook(Color::White);
	cout << (int) rook.getColor() << endl;

	Knight knight(Color::Black);
	cout << (int)knight.getColor() << endl;

	Bishop bishop(Color::White);
	cout << (int)bishop.getColor() << endl;

	King king(Color::Black);
	cout << (int)king.getColor() << endl;

	Queen queen(Color::White);
	cout << (int)queen.getColor() << endl;

	Pawn pawn(Color::Black);
	cout << (int)pawn.getColor() << endl;
	
	int input;
	cin >> input;
}
