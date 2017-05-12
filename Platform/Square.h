#pragma once

class Piece;

class Square {
private:
	Piece *piece;
public:
	Square(Piece *piece);
	Piece *getPiece();
};
