#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class Pawn : public Piece {

public:
	Pawn(PieceColor color);
	const std::string getSymbol() const override;

};
