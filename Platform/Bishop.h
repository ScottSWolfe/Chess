#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class Bishop : public Piece {

public:
	Bishop(PieceColor color);
	const std::string getSymbol() const override;

};
