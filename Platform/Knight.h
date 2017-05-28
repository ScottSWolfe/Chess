#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"


class Knight : public Piece {

public:
	Knight(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, int x, int y) const override;

};
