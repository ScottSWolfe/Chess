#pragma once

#include <string>
#include "Piece.h"


class Pawn : public Piece {
public:
	Pawn(PieceColor color);
	std::string getSymbol() override;
};
