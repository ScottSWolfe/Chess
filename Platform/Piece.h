#pragma once
#include <string>

enum class PieceColor { WHITE, BLACK };

class Piece {
private:
	PieceColor color;
public:
	Piece(PieceColor color);
	virtual PieceColor getColor();
	virtual std::string getSymbol() = 0;
};
