#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class King : public Piece {

public:
	King(PieceColor color);
	const std::string getSymbol() const override;

};
