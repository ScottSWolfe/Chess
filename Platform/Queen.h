#pragma once

#include <string>
#include "ChessEnums.h"
#include "Piece.h"


class Queen : public Piece {

public:
	Queen(PieceColor color);
	const std::string getSymbol() const override;

};
