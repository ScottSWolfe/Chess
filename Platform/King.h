#pragma once

#include <string>
#include "Piece.h"


class King : public Piece {

public:
	King(PieceColor color);
	std::string getSymbol() override;

};
