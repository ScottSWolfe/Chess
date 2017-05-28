#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"


class King : public Piece {

public:
	King(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, int x, int y) const override;

};
