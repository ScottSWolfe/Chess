#include "Piece.h"
#include "Square.h"
#include <iostream>
#include <string>
using namespace std;

Square::Square() : piece(nullptr) {}

Square::Square(Piece *new_piece) : piece(new_piece) {}

Piece *Square::getPiece() {
	return piece;
}

void Square::setPiece(Piece *new_piece) {
	piece = new_piece;
}

void Square::printToConsole() {
	string symbol;
	if (piece == nullptr) {
		symbol = " ";
	}
	else {
		symbol = piece->getSymbol();
	}
	cout << " ";
	cout << symbol;
	cout << " ";
}
