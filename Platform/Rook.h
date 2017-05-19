#pragma once

#include <string>
#include "Piece.h"


class Rook : public Piece {

public:
	Rook(PieceColor color);
	std::string getSymbol() override;

};
