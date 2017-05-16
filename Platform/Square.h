#pragma once
class Piece;

enum class SquareColor { LIGHT, DARK };

class Square {
private:
	const SquareColor color;
	Piece *piece;
public:
	Square(SquareColor color);
	Square(SquareColor color, Piece *piece);
	Piece *getPiece();
	void setPiece(Piece *new_piece);
	SquareColor getColor();
};
