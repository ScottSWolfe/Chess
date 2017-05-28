#pragma once

#include <string>
#include <vector>
#include "ChessEnums.h"
#include "Piece.h"
class Board;
class Move;


class Pawn : public Piece {

public:
	Pawn(PieceColor color);
	const std::string getSymbol() const override;
	std::vector<Move> getMoves(const Board &board, int x, int y) const override;

private:
	int direction() const;
	int startRow(int dimension) const;

};
