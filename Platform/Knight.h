#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class Knight : public Piece {

public:
	Knight(PieceColor color);
	const std::string getSymbol() const override;

};
