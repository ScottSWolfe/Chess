#pragma once

class Piece;

class Square {
private:
	Piece *piece;
public:
	Square();
	Square(Piece *piece);
	Piece *getPiece();
	void setPiece(Piece *new_piece);
	void printToConsole();
};
