#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
struct Position;


class Rook : public Piece {

public:
	Rook(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, Position pos) const override;

};
