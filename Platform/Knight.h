#pragma once

#include <string>
#include "Piece.h"


class Knight : public Piece {
public:
	Knight(PieceColor color);
	std::string getSymbol() override;
};
