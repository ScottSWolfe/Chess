#pragma once

#include <string>


enum class PieceColor { WHITE, BLACK };

class Piece {

public:
	Piece(PieceColor color);
	virtual PieceColor getColor();
	virtual std::string getSymbol() = 0;

private:
	PieceColor color;
};

std::string getPieceSymbol(Piece *piece);
PieceColor getPieceColor(Piece *piece);
