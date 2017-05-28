#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"


class Queen : public Piece {

public:
	Queen(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, int x, int y) const override;

};
