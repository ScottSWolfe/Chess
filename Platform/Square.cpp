#include "Piece.h"
#include "Square.h"
#include <iostream>
#include <string>
using namespace std;

Square::Square(const SquareColor square_color) : 
	piece(nullptr), color(square_color)
{}

Square::Square(const SquareColor square_color, Piece *new_piece) :
	color(square_color), piece(new_piece)
{}

Piece *Square::getPiece() {
	return piece;
}

void Square::setPiece(Piece *new_piece) {
	piece = new_piece;
}

SquareColor Square::getColor() {
	return color;
}
