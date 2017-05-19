#pragma once
#include <string>

#include "Piece.h"


class Bishop : public Piece {
public:
	Bishop(PieceColor color);
	std::string getSymbol() override;
};
