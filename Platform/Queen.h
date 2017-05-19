#pragma once

#include <string>
#include "Piece.h"


class Queen : public Piece {
public:
	Queen(PieceColor color);
	std::string getSymbol() override;
};
