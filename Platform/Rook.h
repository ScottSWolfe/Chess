#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class Rook : public Piece {

public:
	Rook(PieceColor color);
	const std::string getSymbol() const override;

};
